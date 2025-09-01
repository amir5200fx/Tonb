//
// Created by amir on 8/31/25.
//
#include <tonb/geometry/field/mesh_interpolator_2d.hxx>

#include <vector>
#include <array>
#include <random>
#include <cmath>
#include <iostream>
#include <cassert>

using namespace tonb::geometry::field;
using namespace tonb::base;

// -------- Synthetic ground truth -----
// Precent field p(x,y): a smooth Gaussian bump (fraction form)
// True absolute field: v = B * (1 + p)

static real percent_truth(const real x, const real y) {
    constexpr real cx = 0.5;
    constexpr real cy = 0.5;
    constexpr real sigma2 = 0.02;
    const real dx = x - cx, dy = y - cy;
    return 0.2 * std::exp(-(dx*dx + dy*dy) / sigma2);  // up to +20%
}

real absolute_truth(const real x, const real y, const real base) {
    return base * (1.0 + percent_truth(x, y));
}

// Build a regular triangulated grid over [0,1]x[0,1]
void build_unit_square_mesh(const index_t nx, const index_t ny, std::vector<std::array<real, 2>>& V, std::vector<std::array<int, 3>>& F) {
    assert(nx >= 2 && ny >= 2);
    V.clear(); F.clear();
    V.reserve(nx*ny);
    const real hx = 1.0 / (nx - 1);
    const real hy = 1.0 / (ny - 1);

    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            V.push_back({i*hx, j*hy});
        }
    }

    auto vid = [nx](const int i, const int j) {return j*nx + i;};

    F.reserve(static_cast<size_t>(2*(nx-1)*(ny-1))); // NOLINT(*-misplaced-widening-cast)
    for (int j=0; j<ny-1; ++j) {
        for (int i=0; i<nx-1; ++i) {
            const int v00 = vid(i,  j);
            const int v10 = vid(i+1,j);
            const int v01 = vid(i,  j+1);
            const int v11 = vid(i+1,j+1);
            // two triangles per cell: (v00,v10,v11) and (v00,v11,v01)
            F.push_back({v00, v10, v11});
            F.push_back({v00, v11, v01});
        }
    }
}

// Sample random points inside [0,1]^2
std::vector<MeshInterpolator2d::Sample>
make_random_percent_samples(const int n, const real percent_scale, const unsigned seed = 123) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<real> U(0, 1);
    std::vector<MeshInterpolator2d::Sample> samples;
    samples.reserve(n);
    for (int k = 0; k < n; ++k) {
        const real x = U(rng);
        const real y = U(rng);
        const real p = percent_truth(x, y); // fraction (e.g. 0.10 = +10%)
        const real stored = (percent_scale == 1.0) ? p : (p / percent_scale); // store either
        samples.push_back({{x, y}, stored, 1.0});
    }
    return samples;
}

real rmse(const std::vector<real>& truth, const std::vector<real>& pred) {
    assert(truth.size() == pred.size());
    real s = 0.0;
    for (size_t i = 0; i < truth.size(); ++i) {
        const real d = truth[i] - pred[i];
        s += d * d;
    }
    return std::sqrt(s / static_cast<real>(std::max<std::size_t>(1, truth.size())));
}

int main() {
    // 1) Build mesh
    std::vector<std::array<real, 2>> V;
    std::vector<std::array<int, 3>> F;
    constexpr int nx = 60, ny = 60;         // ~7200 vertices, ~2*(nx-1)*(ny-1) faces
    build_unit_square_mesh(nx, ny, V, F);

    MeshInterpolator2d::TriMesh M;
    M.set_vertices(V);
    M.set_faces(F);
    M.build_adjacency();

    std::cout << "Mesh: " << M.vertex_count() << " vertices, " << M.face_count() << " faces\n";

    if (!M.write_obj("/home/amir/dev/Tonb/build/tmp/mesh_interpolator_2d_mesh.obj")) {
        std::cerr << "Error writing mesh.obj\n";
    }

    // 2) Interpolator
    const MeshInterpolator2d interp(M /*, grid cells auto*/);

    // 3) Prepare percent samples
    constexpr real base = 100.0;            // base size/value at all vertices
    constexpr real percent_scale = 1.0;     // samples are stored as faction (0.10 = +10%).
                                        // Use 0.01 if you prefer 10 meaning +10%.
    const auto samples = make_random_percent_samples(1500, percent_scale);

    // 4) Solve (percentage-over-base)
    MeshInterpolator2d::SolveOptions sopt;
    sopt.alpha = 0;                      // tune based on mesh scale (here in [0,1]^2)
    sopt.biharmonic = false;

    MeshInterpolator2d::RobustOptions ropt;
    ropt.iters = 0;                         // a few robustification passes
    ropt.huber_k = 2.0;

    const auto vertex_values = interp.interplate_percent_with_base_scalar(samples, base, percent_scale, sopt, ropt);

    std::cout<<" Max value = "<<std::ranges::max(vertex_values)<<"\n";

    if (!M.write_mesh_csv("/home/amir/dev/Tonb/build/tmp/interpolator_2d_mesh", &vertex_values)) {
        std::cerr << "Error writing csv files\n";
    }

    // 5) Validate against ground truth at vertices
    std::vector<real> truth(vertex_values.size());
    for (std::size_t i = 0; i < vertex_values.size(); ++i) {
        real x = V[i][0], y = V[i][1];
        truth[i] = absolute_truth(x, y, base);
    }
    const real e = rmse(truth, vertex_values);
    std::cout << "RMSE vs truth on vertices: " << e << "\n";

    // 6) Spot-check at a few query points
    const std::array<std::array<real, 2>, 7> queries {
        {
            {0.1, 0.1},
            {0.5, 0.5},
            {0.45, 0.6},
            {0.42, 0.59},
            {0.75, 0.75},
            {0.25, 0.75},
            {0.9, 0.9}
        }};
    for (auto& q : queries) {
        const real vq = interp.evaluate(vertex_values, q);
        const real tq = absolute_truth(q[0], q[1], base);
        std::cout << "query (" << q[0] << "," << q[1] << ")  pred=" << vq << "  truth=" << tq
                  << "  abs.err=" << std::abs(vq - tq) << "\n";
    }
    return 0;



    // 7) (Optional) Compare absolute mode by converting samples to absolute values
    const bool test_absolute_mode = true;
    if (test_absolute_mode) {
        std::vector<MeshInterpolator2d::Sample> abs_samples;
        abs_samples.reserve(samples.size());
        for (const auto& s : samples) {
            double p = (percent_scale == 1.0) ? s.value : (s.value * percent_scale);
            double v = absolute_truth(s.x[0], s.x[1], base); // base*(1+p)
            abs_samples.push_back({s.x, v, s.weight});
        }
        auto v_abs = interp.interpolate(abs_samples, sopt, ropt); // absolute directly
        std::cout << "Absolute-mode RMSE: " << rmse(truth, v_abs) << "\n";

        for (auto& q : queries) {
            const real vq = interp.evaluate(v_abs, q);
            const real tq = absolute_truth(q[0], q[1], base);
            std::cout << "query (" << q[0] << "," << q[1] << ")  pred=" << vq << "  truth=" << tq
                      << "  abs.err=" << std::abs(vq - tq) << "\n";
        }
    }
    std::cout << "Program Done!\n";
    return 0;
}
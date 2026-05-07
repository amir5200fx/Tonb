//
// Created by amir on 9/1/25.
//
#include <tonb/geometry/field/mesh_interpolator_2d.hxx>

#include <vector>
#include <array>
#include <random>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <numbers>

using namespace tonb::base;
using namespace tonb::geometry;

struct Stats {
    double rmse = 0;
    double mae = 0;
    double max_abs = 0;
    int n = 0;
};

static Stats stats_vec(const std::vector<double>& a, const std::vector<double>& b) {
    assert(a.size() == b.size());
    Stats s; s.n = static_cast<int>(a.size());
    double se = 0, sa = 0, m = 0;
    for (size_t i = 0; i < a.size(); i++) {
        const double d = a[i] - b[i];
        se = se + d * d;
        sa += std::abs(d);
        m = std::max(m, std::abs(d));
    }
    s.rmse = std::sqrt(se/ std::max<int>(1, s.n));
    s.mae = sa / std::max<int>(1, s.n);
    s.max_abs = m;
    return s;
}

static double f_analytic(const double x, const double y) {
    // smooth test function
    return 2.0 + std::sin(2 * std::numbers::pi * x) * std::cos(2 * std::numbers::pi * y) + 0.25 * std::exp(
               -(std::pow(x - 0.5, 2) + std::pow(y - 0.5, 2)) / 0.01);
}

static void build_unit_square_mesh(const int nx, const int ny,
                                   std::vector<std::array<double,2>>& V,
                                   std::vector<std::array<int,3>>& F)
{
    assert(nx>=2 && ny>=2);
    V.clear(); F.clear();
    V.reserve(static_cast<size_t>(nx)*ny);
    const double hx = 1.0/(nx-1), hy = 1.0/(ny-1);
    for (int j = 0; j < ny; ++j)
        for (int i = 0; i < nx; ++i)
            V.push_back({i*hx, j*hy});
    auto vid=[nx](const int i, const int j){return j*nx+i;};
    F.reserve(static_cast<size_t>(2)*(nx-1)*(ny-1));
    for (int j = 0; j < ny - 1; ++j) {
        for (int i = 0; i < nx - 1; ++i) {
            const int v00 = vid(i,j), v10 = vid(i + 1, j), v01 = vid(i, j + 1), v11 = vid(i + 1, j + 1);
            F.push_back({v00, v10, v11});
            F.push_back({v00, v11, v01});
        }
    }
}

// Evaluate piecewise-linear field (vertex values) at arbitrary points using interpolator
static std::vector<double> eval_at(const field::MeshInterpolator2d& interp,
                                   const std::vector<double>& vertex_values,
                                   const std::vector<std::array<double,2>>& Q)
{
    std::vector<double> out; out.reserve(Q.size());
    for (auto& q : Q) out.push_back(interp.evaluate(vertex_values, q));
    return out;
}

// Build random points in [0,1]^2
static std::vector<std::array<double,2>> random_points(const size_t n, const unsigned seed=42) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> U(0.0,1.0);
    std::vector<std::array<double,2>> P; P.reserve(n);
    for (size_t i=0;i<n;++i) P.push_back({U(rng), U(rng)});
    return P;
}

// ---------- Benchmark 1: Exact reproduction (no smoothing) ----------
static bool bench_exact_reproduction(const int nx, const int ny)
{
    std::cout << "\n[Bench 1] Exact reproduction (no smoothing)\n";
    std::vector<std::array<double,2>> V; std::vector<std::array<int,3>> F;
    build_unit_square_mesh(nx,ny,V,F);

    field::MeshInterpolator2d::TriMesh M; M.set_vertices(V); M.set_faces(F); M.build_adjacency();
    const field::MeshInterpolator2d interp(M);

    // Construct a ground-truth vertex field (piecewise-linear by construction)
    std::vector<double> v_gt(V.size());
    for (size_t i=0;i<V.size();++i) {
        // choose any pattern at vertices
        const double x=V[i][0], y=V[i][1];
        v_gt[i] = 1.0 + 0.5*x + 0.25*y + 0.1*std::sin(4*std::numbers::pi*x)*std::sin(2*std::numbers::pi*y);
    }

    // Create samples from the SAME piecewise-linear field
    const auto Spts = random_points(8000, 123);
    std::vector<field::MeshInterpolator2d::Sample> S; S.reserve(Spts.size());
    for (auto& p : Spts) {
        const double s = interp.evaluate(v_gt, p); // exact PL eval
        S.push_back({p, s, 1.0});
    }

    // Solve (absolute mode), alpha=0, robust=0
    field::MeshInterpolator2d::SolveOptions sopt; sopt.alpha = 0.0; sopt.biharmonic = false;
    field::MeshInterpolator2d::RobustOptions ropt; ropt.iters = 0;
    const auto v_hat = interp.interpolate(S, sopt, ropt);

    if (!M.write_mesh_csv( "/home/amir/dev/Tonb/build/tmp/bench_test_1a", &v_gt)) {
        std::cerr << "Error writing mesh csv\n";
    }

    const auto S_pred = eval_at(interp, v_hat, Spts);
    std::vector<double> S_truth(Spts.size());
    for (size_t i=0;i<Spts.size();++i) S_truth[i]=S[i].value;

    const Stats sS = stats_vec(S_pred, S_truth);
    const Stats sV = stats_vec(v_hat, v_gt);

    std::cout << "  samples: RMSE=" << sS.rmse << "  max|.|=" << sS.max_abs << "\n";
    std::cout << "  vertices: RMSE=" << sV.rmse << "  max|.|=" << sV.max_abs << "\n";

    const bool pass = (sS.rmse < 1e-8 && sS.max_abs < 1e-7 && sV.rmse < 1e-8 && sV.max_abs < 1e-7);
    std::cout << "  -> " << (pass ? "PASS" : "FAIL") << "\n";
    return pass;
}

// ---------- Benchmark 2: Analytic function fit ----------
static bool bench_analytic_fit(const int nx, const int ny, const double alpha, const bool biharmonic)
{
    std::cout << "\n[Bench 2] Analytic fit (alpha="<<alpha<<", biharmonic="<<biharmonic<<")\n";
    std::vector<std::array<double,2>> V; std::vector<std::array<int,3>> F;
    build_unit_square_mesh(nx,ny,V,F);

    field::MeshInterpolator2d::TriMesh M; M.set_vertices(V); M.set_faces(F); M.build_adjacency();
    const field::MeshInterpolator2d interp(M);

    // Ground truth at vertices (for later vertex RMSE)
    std::vector<double> v_truth(V.size());
    for (size_t i=0;i<V.size();++i) v_truth[i]=f_analytic(V[i][0], V[i][1]);

    // Samples at random points from analytic function
    const auto Spts = random_points(3000, 321);
    std::vector<field::MeshInterpolator2d::Sample> S; S.reserve(Spts.size());
    for (auto& p : Spts) S.push_back({p, f_analytic(p[0],p[1]), 1.0});

    // Solve (absolute)
    field::MeshInterpolator2d::SolveOptions sopt; sopt.alpha = alpha; sopt.biharmonic = biharmonic;
    field::MeshInterpolator2d::RobustOptions ropt; ropt.iters = 0;
    const auto v_hat = interp.interpolate(S, sopt, ropt);

    // Evaluate error on an independent test set
    const auto Tpts = random_points(4000, 999);
    const auto T_pred = eval_at(interp, v_hat, Tpts);
    std::vector<double> T_truth; T_truth.reserve(Tpts.size());
    for (auto& p : Tpts) T_truth.push_back(f_analytic(p[0],p[1]));
    const Stats sT = stats_vec(T_pred, T_truth);

    // Vertex error vs analytic truth (not PL!)
    const Stats sV = stats_vec(v_hat, v_truth);

    std::cout << "  test points: RMSE=" << sT.rmse << "  MAE=" << sT.mae << "  max|.|=" << sT.max_abs << "\n";
    std::cout << "  vertices   : RMSE=" << sV.rmse << "  MAE=" << sV.mae  << "  max|.|=" << sV.max_abs << "\n";

    // Loose acceptance: errors should be small and decrease as nx,ny grow
    const bool pass = (sT.rmse < 0.03 && sT.max_abs < 0.15);
    std::cout << "  -> " << (pass ? "PASS" : "WARN (tune alpha / increase samples)") << "\n";
    return pass;
}

// ---------- Benchmark 3: Impulse response ----------
static bool bench_impulse(const int nx, const int ny, const double alpha, const bool biharmonic)
{
    std::cout << "\n[Bench 3] Impulse (single strong sample)\n";
    std::vector<std::array<double,2>> V; std::vector<std::array<int,3>> F;
    build_unit_square_mesh(nx,ny,V,F);

    field::MeshInterpolator2d::TriMesh M; M.set_vertices(V); M.set_faces(F); M.build_adjacency();
    const field::MeshInterpolator2d interp(M);

    // Base 100, percent +20% at center (0.5,0.5) with very large weight
    const double base = 100.0;
    field::MeshInterpolator2d::Sample s; s.x = {0.5,0.5}; s.value = 0.20; s.weight = 1e6;
    const std::vector<field::MeshInterpolator2d::Sample> S = {s};

    field::MeshInterpolator2d::SolveOptions sopt; sopt.alpha = alpha; sopt.biharmonic = biharmonic;
    field::MeshInterpolator2d::RobustOptions ropt; ropt.iters = 0;
    auto v = interp.interplate_percent_with_base_scalar(S, base, /*percent_scale=*/1.0, sopt, ropt);

    // Probe a small ring around the center to check for overshoot
    const auto ring = [&]{
        std::vector<std::array<double,2>> Q;
        for (int k=0;k<64;++k){
            const double ang = (2*std::numbers::pi*k)/64.0, r = 0.05;
            Q.push_back({0.5 + r*std::cos(ang), 0.5 + r*std::sin(ang)});
        }
        return Q;
    }();
    auto ring_vals = eval_at(interp, v, ring);

    const double vmax = *std::ranges::max_element(v);
    const double vmin = *std::ranges::min_element(v);
    const double ring_max = *std::ranges::max_element(ring_vals);
    const double center_pred = interp.evaluate(v, {0.5,0.5});

    std::cout << "  center pred=" << center_pred << " (expect ~120)\n";
    std::cout << "  global max=" << vmax << "  min=" << vmin << "  ring max=" << ring_max << "\n";

    // Acceptance: center near 120, ring_max not much above center (<= +2%)
    const bool pass = (std::abs(center_pred - 120.0) < 0.5) && (ring_max <= 1.02 * center_pred);
    std::cout << "  -> " << (pass ? "PASS" : "WARN (reduce overshoot: use biharmonic / raise alpha)") << "\n";
    return pass;
}

int main(const int argc, char** argv)
{
    int nx = 60, ny = 60;
    if (argc >= 3) { nx = std::max(2, std::atoi(argv[1])); ny = std::max(2, std::atoi(argv[2])); }

    // 1) Exact reproduction (should pass with very tight tolerance)
    const bool ok1 = bench_exact_reproduction(nx, ny);

    // 2) Analytic fit: try a couple of α values with biharmonic on
    const bool ok2a = bench_analytic_fit(nx, ny, 3e-7, true);
    const bool ok2b = bench_analytic_fit(nx, ny, 1e-6, true);

    // 3) Impulse response
    const bool ok3a = bench_impulse(nx, ny, 3e-7, true);
    const bool ok3b = bench_impulse(nx, ny, 1e-6, true);

    std::cout << "\nSummary: "
              << (ok1 ? "[1 OK] " : "[1 FAIL] ")
              << (ok2a ? "[2a OK] " : "[2a WARN] ")
              << (ok2b ? "[2b OK] " : "[2b WARN] ")
              << (ok3a ? "[3a OK] " : "[3a WARN] ")
              << (ok3b ? "[3b OK]"  : "[3b WARN]") << "\n";

    return (ok1 ? 0 : 1);
}

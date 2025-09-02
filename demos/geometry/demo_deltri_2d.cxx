/**
 * @file geo2d_deltri_demo.cxx
 * @brief Demo for tonb::geo2d::Delaunay2D
 *
 * Build: add this file to your demos folder and link Tonb::Geo2dDelTri.
 * Run: it will create "triangulation.obj" in the working directory.
 */

#include <tonb/geometry/triangulation/delaunay_2d.hxx>
#include <tonb/geometry/pnt_2d.hxx>

#include <vector>
#include <random>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <numbers>

using namespace tonb;
using namespace tonb::geometry;

// Write a simple OBJ: z=0, 1-based face indices
static bool write_obj(const std::string& path,
                      const triangulation::Delaunay2d::TriMesh& m) {
    std::ofstream os(path, std::ios::binary);
    if (!os) return false;

    os << "# Triangulation OBJ\n";
    for (const auto& p : m.points)
        os << "v " << p.x() << " " << p.y() << " 0\n";

    // ensure CCW faces in XY so tools see the correct normal
    for (const auto& f : m.tris) {
        os << "f " << (f[0] + 1) << " " << (f[1] + 1) << " " << (f[2] + 1) << "\n";
    }
    return true;
}

// Build a small synthetic point set: circle + random jitter + a grid patch
static std::vector<Pnt2d> make_points() {
    std::vector<Pnt2d> pts;
    pts.reserve(200);

    // deterministic RNG for reproducibility
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> uni(-0.02, 0.02);

    // circle
    const int nCircle = 64;
    for (int i = 0; i < nCircle; ++i) {
        const double t = (2.0 * std::numbers::pi * i) / nCircle;
        double x = std::cos(t) + uni(rng);
        double y = std::sin(t) + uni(rng);
        pts.emplace_back(x, y);
    }

    // random interior
    std::uniform_real_distribution<double> uni01(0.0, 1.0);
    for (int i = 0; i < 80; ++i) {
        const double r = 0.8 * std::sqrt(uni01(rng));     // pull points inward
        const double t = 2.0 * std::numbers::pi * uni01(rng);
        pts.emplace_back(r * std::cos(t), r * std::sin(t));
    }

    // small grid patch
    for (int iy = 0; iy < 6; ++iy)
        for (int ix = 0; ix < 6; ++ix)
            pts.emplace_back(-1.5 + 0.1 * ix, -1.0 + 0.1 * iy);

    return pts;
}

// Simple quality check: count boundary edges using a map of undirected edges
static int count_boundary_edges(const triangulation::Delaunay2d::TriMesh& m) {
    struct Edge { int a, b; };
    struct Hash {
        size_t operator()(const Edge& e) const noexcept {
            return (static_cast<size_t>(e.a) << 32) ^ static_cast<size_t>(e.b);
        }
    };
    struct Eq {
        bool operator()(const Edge& x, const Edge& y) const noexcept {
            return x.a == y.a && x.b == y.b;
        }
    };

    std::unordered_map<Edge, int, Hash, Eq> counts;
    counts.reserve(m.tris.size() * 3);

    auto add_edge = [&](int i, int j) {
        if (i > j) std::swap(i, j);
        const Edge e{i, j};
        counts[e] += 1;
    };

    for (const auto& f : m.tris) {
        add_edge(f[0], f[1]);
        add_edge(f[1], f[2]);
        add_edge(f[2], f[0]);
    }

    int boundary = 0;
    for (const auto& kv : counts)
        if (kv.second == 1) boundary++;

    return boundary;
}

int main() {
    using triangulation::Delaunay2d;
    using Options = triangulation::Delaunay2dOptions;

    // 1) Build input points
    auto pts = make_points();
    //std::vector<Pnt2d> pts = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};


    // 2) Triangulate
    Options opt;
    opt.build_neighbors = true;
    opt.robust_predicates = true;
    const auto mesh = Delaunay2d::triangulate(pts, opt);

    // 3) Report
    std::cout << "Points:     " << mesh.points.size() << "\n";
    std::cout << "Triangles:  " << mesh.tris.size()   << "\n";
    if (!mesh.neigh.empty())
        std::cout << "Neighbours: " << mesh.neigh.size() << " sets\n";

    // Optional sanity checks
    const int boundaryEdges = count_boundary_edges(mesh);
    std::cout << "Boundary edges (count=1): " << boundaryEdges << "\n";

    // 4) Export to OBJ
    const std::string outPath = "/home/amir/dev/Tonb/build/tmp/triangulation.obj";
    if (write_obj(outPath, mesh))
        std::cout << "Wrote " << outPath << "\n";
    else
        std::cerr << "Failed to write " << outPath << "\n";

    return 0;
}

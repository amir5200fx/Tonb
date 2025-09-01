//
// Created by amir on 8/31/25.
//
#include <iomanip>
#include <tonb/geometry/spatial/grid_2d.hxx>
#include <tonb/geometry/pnt_2d.hxx>

#include <random>
#include <iostream>

using namespace tonb;
using namespace tonb::geometry;

//------ Policies for Grid2d<Pnt2d, ...> ------------

// Extract (x, y) from Pnt2d
struct GetPnt2dXY {
    std::pair<real, real> operator()(const Pnt2d& p) const noexcept {
        return {p[0], p[1]};
    }
};

// Merge policy: arithmetic mean of coordinates (customise to your needs)
struct AvgMergePnt2d {
    void operator()(Pnt2d& a, const Pnt2d& b) const noexcept {
        a[0] = 0.5 * (a[0] + b[0]); a[1] = 0.5 * (a[1] + b[1]);
    }
};

int main() {

    // Cell size - merge radius (keep neighbour scans small)
    constexpr real cell = 0.1;
    constexpr real merge_r = 0.08;

    spatial::Grid2d<Pnt2d, GetPnt2dXY, AvgMergePnt2d> grid(cell);

    // Seed deterministic points: uniform cloud + a tight cluster
    std::mt19937_64 rng(42);
    std::uniform_real_distribution<real> uni(-1.0, 1.0);
    std::normal_distribution<real> cx(0.25, 0.03), cy(-0.35, 0.03);

    // Insert 300 uniform points
    for (int i = 0; i < 300; ++i) {
        grid.insert_or_merge(Pnt2d{uni(rng), uni(rng)}, merge_r);
    }
    // Insert 100 clustered points (will heavily merge)
    for (int i = 0; i < 100; ++i) {
        grid.insert_or_merge(Pnt2d{cx(rng), cy(rng)}, merge_r);
    }

    std::cout << "Items after merges: "<<grid.size() << std::endl;

    // AABB query around the cluster area
    std::vector<std::size_t> ids;
    grid.query_aabb(0.15, -0.45, 0.35, -0.25, std::back_inserter(ids));
    std::cout << "AABB hits near cluster: " << ids.size() << std::endl;

    // Radius query around the cluster center
    ids.clear();
    grid.query_radius(0.25, -0.35, 0.1, std::back_inserter(ids));
    std::cout << "Radius hits near cluster: " << ids.size() << std::endl;

    // Show first few items
    std::cout << std::fixed << std::setprecision(4);
    for (std::size_t k = 0; k < std::min<std::size_t>(grid.size(), 8); ++k) {
        const auto& p = grid.items()[k];
        std::cout << "  pt[" << k << "] = (" << p.x() << ", " << p.y() << ")\n";
    }
    return 0;
}
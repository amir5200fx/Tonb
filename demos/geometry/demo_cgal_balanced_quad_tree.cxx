//
// Created by amir on 8/31/25.
//
#include <tonb/config.hxx>
#include <tonb/geometry/spatial/cgal/balanced_quad_tree.hxx>

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace tonb::geometry::spatial::cgal;
using namespace tonb::geometry;

int main() {
    std::cout << "TONB_WITH_CGAL = " << TONB_HAS_CGAL << "\n";

    BalancedQuadTree tree;
    tree.set_max_depth(10);
    tree.set_max_leaf_size(2);

    // 1) Seed some points (uniform square + a tight cluster)
    std::mt19937_64 rng(42);
    std::uniform_real_distribution<double> uni(-1.0, 1.0);
    std::normal_distribution<double> cluster_x(0.2, 0.05);
    std::normal_distribution<double> cluster_y(-0.3, 0.05);

    std::vector<Pnt2d> pts;
    pts.reserve(400);

    // Uniform cloud
    for (int i = 0; i < 300; ++i) {
        pts.emplace_back(uni(rng), uni(rng));
    }
    // Cluster
    for (int i = 0; i < 100; ++i) {
        pts.emplace_back(cluster_x(rng), cluster_y(rng));
    }

    tree.insert_points(pts);

    // 2) Build/refile/grade (no-op if CGAL is OFF)
    tree.rebuild();

    std::cout << "Point count: " << tree.point_count() << "\n";

    // 3) Retrieve all leaf AABBs
    auto boxes = tree.leaf_boxes();
    std::cout << "Leaf boxes: " << boxes.size() << "\n";

    // 4) Print first few boxes
    std::cout << std::fixed << std::setprecision(4);
    const std::size_t show = std::min<std::size_t>(boxes.size(), 10);
    for (std::size_t i = 0; i < show; ++i) {
        const auto& b = boxes[i];
        std::cout << " [" << b.xmin << ", " << b.ymin
                  << "] - [" << b.xmax << ", " << b.ymax << "]\n";
    }

#if TONB_WITH_CGAL
    if (boxes.empty()) {
        std::cout << "(Unexpected: CGAL is ON but no boxes returned)\n";
    } else {
        std::cout << "BalancedQuadTree demo completed.\n";
    }
#else
    std::cout << "CGAL is OFF; this is a stub run (no boxes).\n";
#endif
    return 0;
}
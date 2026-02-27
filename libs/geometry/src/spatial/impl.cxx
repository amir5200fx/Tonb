//
// Created by amir on 8/30/25.
//
//#include <tonb/geometry/spatial/adaptive_tree.hxx>
//#include <tonb/geometry/spatial/balanced_quad_tree.hxx>
#include <tonb/geometry/spatial/grid_2d.hxx>
#include <tonb/geometry/spatial/ad_tree.hxx>
#include <tonb/geometry/spatial/hash_grid_2d.hxx>

using namespace tonb;
using namespace tonb::geometry;
using namespace tonb::geometry::spatial;
namespace {
    struct Node {
        Pnt2d coord;
        using ptType = Pnt2d;
    };

    AdTree<Node> ad_tree;
    void ff() {
        ad_tree.insert(Node{{0, 0}});

        AdTree<Node>::box_type b;
        auto r = b.range(static_cast<Direction>(1));
        std::vector<Node> items;
        ad_tree.search_in_radius(1.0, {0, 0}, items);
    }
}
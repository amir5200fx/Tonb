//
// Created by amir on 8/30/25.
//
#include <tonb/config.hxx>
#if defined(TONB_HAS_CGAL)
#include <tonb/geometry/spatial/cgal/balanced_quad_tree.hxx>

// CGAL
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Quadtree.h>
#include <CGAL/version.h>
#if CGAL_VERSION_NR >= 1060000000
#include <CGAL/Orthtree_traits.h>
#else
#include <CGAL/Orthtree.h>
#include <CGAL/Orthtree_traits_2.h>
#endif

#include <optional>

namespace tonb::geometry::spatial::cgal {

    struct BalancedQuadTree::Impl {
        using Kernel = CGAL::Simple_cartesian<real>;
        using Point_2 = Kernel::Point_2;
        using Points = std::vector<Point_2>;
        using Quadtree = CGAL::Quadtree<Kernel, Points>;

        Points points;
        std::optional<Quadtree> qt;
        int max_depth = 10;
        int max_leaf_size = 8;
        bool dirty = false;

        void rebuild_tree() {
            qt.emplace(points);
            qt->refine(max_depth, max_leaf_size);
            qt->grade(); // enforce 2:1 balance
            dirty = false;
        }
    };

    BalancedQuadTree::BalancedQuadTree()
        : impl_(std::make_unique<Impl>()) {}

    BalancedQuadTree::~BalancedQuadTree() noexcept = default;
    BalancedQuadTree::BalancedQuadTree(BalancedQuadTree &&rhs) noexcept = default;
    BalancedQuadTree &BalancedQuadTree::operator=(BalancedQuadTree &&rhs) noexcept  = default;


    BalancedQuadTree BalancedQuadTree::clone() const {
        BalancedQuadTree c;
        c.impl_->max_depth = impl_->max_depth;
        c.impl_->max_leaf_size = impl_->max_leaf_size;
        c.impl_->points = impl_->points;
        c.impl_->dirty = impl_->dirty;
        if (impl_->qt && !impl_->dirty) c.impl_->rebuild_tree();
        return c;
    }

    void BalancedQuadTree::set_max_depth(int d) noexcept {
        impl_->max_depth = d;
    }
    void BalancedQuadTree::set_max_leaf_size(int s) noexcept {
        impl_->max_leaf_size = s;
    }
    int BalancedQuadTree::max_depth() const noexcept {
        return impl_->max_depth;
    }
    int BalancedQuadTree::max_leaf_size() const noexcept {
        return impl_->max_leaf_size;
    }

    void BalancedQuadTree::insert_point(real x, real y) noexcept {
        impl_->points.emplace_back(x, y);
        impl_->dirty = true;
    }
    void BalancedQuadTree::insert_points(const std::vector<Pnt2d> &pts) {
        impl_->points.reserve(impl_->points.size() + pts.size());
        for (const Pnt2d &pt : pts) {
            impl_->points.emplace_back(pt[0], pt[1]);
        }
        impl_->dirty = true;
    }

    void BalancedQuadTree::clear() {
        impl_->points.clear();
        impl_->qt.reset();
        impl_->dirty = true;
    }

    void BalancedQuadTree::rebuild() {
        if (impl_->dirty) impl_->rebuild_tree();
    }

    void BalancedQuadTree::refine_and_grade() {
        if (!impl_->qt) impl_->rebuild_tree();
        else {
            impl_->qt->refine(impl_->max_depth, impl_->max_leaf_size);
            impl_->qt->grade();
        }
    }

    std::size_t BalancedQuadTree::point_count() const noexcept {
        return impl_->points.size();
    }
    std::vector<BalancedQuadTree::Box> BalancedQuadTree::leaf_boxes() const {
        std::vector<Box> out;
        if (!impl_->qt) return out;

#if CGAL_VERSION_NR >= 1060000000
      auto leaves = impl_->qt->traverse(CGAL::Orthtrees::Leaves_traversal<QT>(*impl_->qt));
        using QT = Impl::Quadtree;
      #else
        const auto leaves = impl_->qt->traverse(CGAL::Orthtrees::Leaves_traversal());
#endif
      for (const auto node : leaves) {
        const auto b = impl_->qt->bbox(node);
        out.push_back(Box{b.xmax(), b.ymin(), b.xmax(), b.ymax()});
      }
      return out;
    }

}

#else

#endif


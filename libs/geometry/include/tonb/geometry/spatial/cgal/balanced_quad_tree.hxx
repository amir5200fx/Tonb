//
// Created by amir on 8/31/25.
//
#pragma once
#ifndef TONB_GEOMETRY_SPATIAL_CGAL_BALANCED_QUAD_TREE_HXX
#define TONB_GEOMETRY_SPATIAL_CGAL_BALANCED_QUAD_TREE_HXX
#include <tonb/geometry/pnt_2d.hxx>
#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <vector>
#include <cstddef>
#include <memory>

namespace tonb::geometry::spatial::cgal {

    class BalancedQuadTree {
    public:
        struct Box {
            real xmin, ymin, xmax, ymax;
        };

        // Constructors
        TNBGEOM_EXPORT BalancedQuadTree();

        // No copies (use clone() if you need a deep copy)
        explicit BalancedQuadTree(const Box& box) = delete;
        BalancedQuadTree& operator = (const BalancedQuadTree& rhs) = delete;

        // Move-only
        TNBGEOM_EXPORT BalancedQuadTree(BalancedQuadTree&& rhs) noexcept;
        TNBGEOM_EXPORT BalancedQuadTree& operator = (BalancedQuadTree&& rhs) noexcept;

        TNBGEOM_EXPORT ~BalancedQuadTree() noexcept;

        // Optional: deep copy without exposing internals
        TNB_NODISCARD BalancedQuadTree clone() const;

        // Public functions and operators

        TNBGEOM_EXPORT void set_max_depth(int d) noexcept;
        TNBGEOM_EXPORT void set_max_leaf_size(int n) noexcept;

        TNBGEOM_ND_EXPORT int max_depth() const noexcept;
        TNBGEOM_ND_EXPORT int max_leaf_size() const noexcept;

        TNBGEOM_EXPORT void insert_point(real x, real y) noexcept;
        TNBGEOM_EXPORT void insert_points(const std::vector<Pnt2d>& pts);

        TNBGEOM_EXPORT void clear();
        TNBGEOM_EXPORT void rebuild();
        TNBGEOM_EXPORT void refine_and_grade();

        TNBGEOM_ND_EXPORT std::size_t point_count() const noexcept;
        TNBGEOM_ND_EXPORT std::vector<Box> leaf_boxes() const;

    private:

        /*Private Data*/

        struct Impl;            // Forward-declare
        std::unique_ptr<Impl> impl_;
    };
}
#endif //TONB_GEOMETRY_SPATIAL_CGAL_BALANCED_QUAD_TREE_HXX
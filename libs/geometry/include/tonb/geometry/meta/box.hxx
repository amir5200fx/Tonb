//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_BOX_HXX
#define TONB_GEOMETRY_META_BOX_HXX

/**
 * @file
 * @brief Axis-Aligned 2D/3D bounding box for geometry utilities.
 *
 * This class represents an axis-aligned bounding box (AABB) in 2D/3D and is used
 * across the geometry and CAD layers for fast spatial queries., culling, and coarse
 * intersection checks. A default-constructed box is **empty/void** and becomes valid
 * once at least one point or box is added.
 *
 * ## Semantics
 * - The box may represent an empy set. In that state, queries like @ref min()
 * and @ref max() are unspecified unless noted otherwise (returning zeros is
 * acceptable).
 * - Once populated, invariants hold: min[i] <= max[i] for i = 0..3.
 * - All coordinates are in **model space** using project units (e.g. metres).
 *
 * ## Typical usage
 * @code
 * auto b = tonb::geometry::meta::Box<tonb::geometry::Pnt3d>::from_min_max({0,0,0}, {1, 1, 1});
 * b.add({5, 0, 0});    // expand to include a point
 * auto c = tonb::geometry::meta::Box<tonb::geometry::Pnt3d>::from_min_max({-1, -1, -1}, {0, 0, 0});
 * b.add(c);            // union with another box
 * if (!b.empty()) {
 *  auto mn = b.min();
 *  auto mx = b.max();
 *  }
 *  @endcode
 *
 *
 */

#include <tonb/geometry/cartesian_direction.hxx>
#include <tonb/geometry/module.hxx>
#include <tonb/base/traits/traits.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/base/range.hxx>

#include <array>

namespace tonb::geometry::meta {
    template<class Point>
    class Box {
    public:
        using Array = std::array<Point, 2>;

        template<bool cond, typename U>
        using EnableIf = std::enable_if_t<cond, U>;
        template<bool B, class T = void>
        using EnableIf_t = std::enable_if_t<B, T>;

        template<int Dim>
        using is_two_dimension = base::traits::is_two_dimension<Dim>;
        template<int Dim>
        using is_three_dimension = base::traits::is_three_dimension<Dim>;

        using Range = base::Range<real>;

        struct Utility;

    private:
        /*Private Data*/

        Array corners_{};
    public:

        // default constructor

        Box() noexcept = default;

        // constructors

        explicit Box(Array corners) noexcept : corners_(std::move(corners)) {}
        Box(Point corner1, Point corner2) noexcept : corners_({std::move(corner1), std::move(corner2)}) {}
        Box(const Box&) noexcept = default;
        Box(Box&& other) noexcept = default;

        static Box from_vector(const std::vector<Point>&);
        /**
         * @brief Create a box from explicit min/max corners.
         * @param mn Minimum corner {xmin, ymin, zmin}.
         * @param mx Maximum corner {xmax, ymax, zmax}.
         * @return A valid box with the given extents.
         */
        static Box from_min_max(const Point& mn, const Point& mx) noexcept;

        // Public functions and operators

        Box& operator=(Box&& other) noexcept = default;
        Box& operator=(Box const& other) noexcept = default;

        // Access
        const auto& corners() const noexcept { return corners_; }
        const auto& corner1() const noexcept { return corners_[0]; }
        const auto& corner2() const noexcept { return corners_[1]; }

        /** *
         * @brief Get the minimum corner (xmin, ymin, zmin).
         * @warning Undefined for empty boxed unless specified by implementation.
         */
        TNB_NODISCARD const auto& min() const noexcept {return corner1();}

        /**
         * @brief Get the maximum corner (xmax, ymax, zmax).
         * @warning Undefined for empty boxed unless specified by implementation.
         */
        TNB_NODISCARD const auto& max() const noexcept {return corner2();}

        TNB_NODISCARD auto size() const noexcept { return corners_.size(); }
        const auto& at(size_t i) const {return corners_.at(i);}

        void set_corners(Array corners) noexcept {corners_ = std::move(corners);}
        void set_corners(Point corner1, Point corner2) noexcept;

        template<class Corner>
        Point corner(Corner c) const;

        // geometrical operations

        /** *
         * @brief True if the box is empty/void (contains no points).
         */
        //TNB_DEPRECATED bool empty() const noexcept;

        /// Reset to the empty/void state.
        //void clear() noexcept;

        TNB_NODISCARD real diameter() const noexcept;
        TNB_NODISCARD real diameter_squared() const noexcept;

        /**
         * @brief Check whether a point lies inside (inclusive).
         * @return true if @p p is within [min, max] on all axes.
         */
        bool contains(const Point& p) const noexcept;

        /**
         * @brief Check whether this box intersects another.
         * @return true if the intersection is non-empty.
         */
        bool intersects(const Box& other) const noexcept;
        Point center() const noexcept;

        /**
         * @brief Volume of the box.
         * @return Non-negative volume; 0 for empy boxes.
         */
        real volume() const noexcept;

        template<class U = void>
        inline EnableIf_t< is_two_dimension< static_cast<int>(Point::dim) >::value, U >
        extend(const real dx, const real dy) {extend(dx, dy); return U{};}
        template<class U = Box>
        EnableIf_t<is_two_dimension<static_cast<int>(Point::dim)>::value, U>
        extended(real dx, real dy) const {return extended({dx, dy});}

        template<class U = void>
        EnableIf_t<is_three_dimension<static_cast<int>(Point::dim)>::value, U>
        extend(real dx, real dy, real dz) {
            extend({dx, dy, dz});
            return U{};
        }

        template<class U = Box>
        EnableIf_t<is_three_dimension<static_cast<int>(Point::dim)>::value, U>
        extended(real dx, real dy, real dz) const {return extended({dx, dy, dz});}

        Box extended(const std::array<real, Point::dim>& components) const;
        void extend(const std::array<real, Point::dim>& components);

        template<class Sub>
        Box subdivide(Sub s) const;

        std::array<real, Point::dim> length() const noexcept;

        TNB_NODISCARD Range range(Direction d) const;
        void range(Direction d, Range& r) const;

        /**
         * @brief Expand the box to include a point.
         */
        void add(const Point&);
        /**
         * @brief Expand the box to include another box (union).
         * @param other Box to merge into this one.
         */
        void add(const Box& other);

        void normalize() noexcept;

        // io functions
        void print(std::ostream& os) const;
    };
}
#include <tonb/geometry/meta/box_i.hxx>
#endif //TONB_GEOMETRY_META_BOX_HXX
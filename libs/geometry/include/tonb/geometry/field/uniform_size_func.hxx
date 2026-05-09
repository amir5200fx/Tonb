//
// Created by amir on 11/8/25.
//
#pragma once
#ifndef TONB_GEOMETRY_FIELD_UNIFORM_SIZE_FUNC_HXX
#define TONB_GEOMETRY_FIELD_UNIFORM_SIZE_FUNC_HXX
#include <tonb/geometry/field/size_func.hxx>
#include <tonb/system/module.hxx>
#include <cassert>
namespace tonb::geometry::field {
    /**
     * @class UniformSizeFunc
     * @brief Concrete sizing function that returns a constant size everywhere
     *
     * @tparam Point A point type compatible with SizeFunc (e.g., Pnt2d, Pnt3d).
     */
    template<class Point>
    class UniformSizeFunc final : public SizeFunc<Point> {
    public:
        /// Construct a uniform sizing function with constant value \p h.
        explicit UniformSizeFunc(const real h) : h_(h) {assert(h > real{0});}

        /// Evaluate the size at ta point (always returns the same value).
        real at(const Point& p) const noexcept override { return h_; }

        /// Get the current constant size value
        TNB_NODISCARD real value() const {return h_;}

        /// Set a new constant size value (must be positive).
        void set_value(const real h) {assert(h > real{0}); h_ = h;}
    private:
        real h_;
    };

}
#endif //TONB_GEOMETRY_FIELD_UNIFORM_SIZE_FUNC_HXX
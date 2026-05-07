//
// Created by amir on 11/8/25.
//
#pragma once
#ifndef TONB_GEOMETRY_FIELD_SIZE_FUNC_HXX
#define TONB_GEOMETRY_FIELD_SIZE_FUNC_HXX
#include <tonb/base/precision.hxx>
namespace tonb::geometry::field {
    /**
     * @class SizeFunc
     * @brief Abstract base class defining a scalar sizing function over space.
     *
     * The `SizeFunc` class provides an interface for evaluating a local target size
     * (for example, an element edge length or mesh spacing) at a given spatial point.
     * It serves as the fundamental abstraction for adaptive meshing, sampling, and
     * geometric refinement processes within the Tonb geometry framework.
     *
     * ### Overview
     * A `SizeFunc` defines a scalar field:
     * \f[
     *      h = f(\mathbf{x})
     * \f]
     * where `h` is a characteristic size value (e.g., local element size) and
     * \f$\mathbf{x}\f$ is a spatial coordinate (2D or 3D). The value returned by
     * `at(const Point&)` is typically used to control mesh density or
     * interpolation resolution.
     *
     * ### Design
     * - The class is **templated** on the `Point` type, which can represent a
     *   2D or 3D coordinate (for example, `std::array<real, 2>` or `std::array<real, 3>`).
     * - It exposes a single pure virtual method `at(const Point&) const`,
     *   which derived classes must implement to provide size evaluation logic.
     * - Construction is **protected** to enforce usage through subclassing.
     *
     * @tparam Point The point type representing a spatial coordinate (e.g., 2D or 3D vector).
     *
     * @note `SizeFunc` is designed to be lightweight and dependency-free, allowing
     *       it to be used seamlessly across Tonb's geometry, triangulation, and spatial modules.
     */
    template<class Point>
    class SizeFunc {
    protected:

        SizeFunc() = default;

    public:
        virtual ~SizeFunc() = default;
        virtual real at(const Point&) const = 0;
    };
}
#endif //TONB_GEOMETRY_FIELD_SIZE_FUNC_HXX
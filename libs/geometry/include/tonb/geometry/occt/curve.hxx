/**
* @file
 * @brief Kernel-agnostic geometric curve wrapper.
 *
 * `tonb::geometry::Curve` wraps a backend curve (OCCT Geom_Curve when
 * TONB_WITH_OCCT=ON). The header is OCCT-free; implementation lives in .cxx.
 *
 * Default-constructed curves are invalid. Methods that query geometry assume
 * `is_valid()==true`.
 *
 * Two projection interfaces are provided:
 *  - project(): simple API, returns MinDistanceProjected and throws on errors.
 *  - try_project_point(): safer API, returns std::expected with optional
 *    ProjectionResult and never throws.
 */
#pragma once
#ifndef TONB_GEOMETRY_OCCT_CURVE_HXX
#define TONB_GEOMETRY_OCCT_CURVE_HXX

#include <memory>
#include <optional>
#include <array>
#include <vector>
#include <expected>
#include <string>

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/geometry/occt/point.hxx>

namespace tonb::geometry::occt {
    namespace core {
        struct occt_curve_access;
    }
    class Curve {
    public:

        // default constructor
        Curve() noexcept = default;

        // Value semantics
        Curve(Curve const&) noexcept = default;
        Curve(Curve&&) noexcept = default;
        Curve& operator=(Curve const&) noexcept = default;
        Curve& operator=(Curve&&) noexcept = default;

        // Public functions and operators

        /// True if this handle references a real backend curve.
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;

        /// Is the curve closed (end points coincide)?
        TNBGEOM_ND_EXPORT bool is_closed() const noexcept;

        /// Is the curve periodic?
        TNBGEOM_ND_EXPORT bool is_periodic() const noexcept;

        /// Polynomial/spline degree if known; otherwise returns -1.
        TNBGEOM_ND_EXPORT int degree() const noexcept;

        TNBGEOM_ND_EXPORT bool is_bspline() const noexcept;
        TNBGEOM_ND_EXPORT int nb_poles() const noexcept;
        TNBGEOM_ND_EXPORT std::vector<Point> poles() const noexcept;
        TNBGEOM_ND_EXPORT Point pole(int index) const noexcept;

        TNBGEOM_ND_EXPORT bool is_nurbs() const noexcept;
        TNBGEOM_ND_EXPORT std::vector<real> weights() const noexcept;
        TNBGEOM_ND_EXPORT real weight(int index) const;

        /// Parameter range if the curve is bounded. std::nullopt if unbounded.
        TNBGEOM_ND_EXPORT std::optional<std::pair<real, real>> parameter_range() const noexcept;

        /// Evaluate point at parameter u
        TNBGEOM_ND_EXPORT std::array<real, 3> value(double u) const;

        /// Evaluate point and first derivative at u.
        struct D1{std::array<real, 3> p{}; std::array<real, 3> q{};};
        TNBGEOM_ND_EXPORT D1 d1(double u) const;

        /// Returns a trimmed sub-curve [u0, u1]. If not supported, returns invalid.
        TNBGEOM_ND_EXPORT Curve trimmed(double u0, double u1) const;

        TNBGEOM_ND_EXPORT Curve reversed() const;
        TNBGEOM_ND_EXPORT Curve bspline() const;
        TNBGEOM_EXPORT void reverse() const;

        /**
         * @struct MinDistanceProjected
         * @brief Simplified result of projecting a point onto a curve.
         *
         * Provides the closest point on the curve and the corresponding
         * curve parameter. This is a lightweight alternative to
         * ProjectionResult without distance information.
         */
        struct MinDistanceProjected {Point point; real parameter;};
        /**
         * @brief Projects a point onto this curve (minimal distance).
         *
         * Computes the closest point on the curve to the given pont and
         * returns it along with the corresponding curve parameter.
         *
         * Unlike try_project_point(), this method does not return distance
         * information and signals failure by throwing if the backend curve
         * is invalid. It is a lightweight wrapper around the underlying OCCT
         * projection functionality.
         *
         * @param p The point to project.
         * @return MinDistanceProjected containing the nearest point and curve parameter.
         * @throes std::runtime_error if the curve handle is invalid or the backend projection fails.
         * @see MinDistanceProjected, try_project_point()
         */
        TNBGEOM_ND_EXPORT MinDistanceProjected project(const Point& p) const;

        /**
         * @enum ProjectionErrc
         * @brief Error codes for point projection onto a curve.
         */
        enum class ProjectionErrc {
            null_curve,
            occt_failure
        };
        /**
         * @struct ProjectionError
         * @brief Error information returned when a projection fails.
         *
         * Wraps an error code and an optional message from the backend.
         */
        struct ProjectionError {
            ProjectionErrc code;        ///< Error category.
            std::string message;        ///< Descriptive message (maybe empty).
        };
        /**
         * @struct ProjectionResult
         * @brief Result of projecting a point onto a curve.
         *
         * Contains the nearest point on the curve, the curve parameter
         * at that location, and the minimal distance to the input point.
         */
        struct ProjectionResult {
            std::array<double, 3> point;
            real parameter;
            real distance;
        };
        /**
         * @brief Projects a point onto this curve with minimal distance.
         *
         * Attempts to find the closest point on the curve to the given 3D point.
         * - If the curve handle is invalid, returns an error (`ProjectionError` with
         *   code `ProjectionErrc::null_curve`).
         * - If the backend OCCT operation fails unexpectedly, returns an error with
         *   code `ProjectionErrc::occt_failure`.
         * - If the projection is valid but no solution exists (e.g. curve cannot be
         *   projected onto), the function returns an empy `std::optional`.
         * - Otherwise, returns a populated `ProjectionResult` containing the
         *   projected point, the curve parameter at the closest location, and the
         *   distance to the input point.
         *
         * This method never throws: all failure cases are communicated via the
         * `std::expected` result.
         *
         * @param p The 3D point in array form {x, y, z}.
         * @return
         *      -`std::expected` with:
         *          - `std::optional<ProjectionResult>` if successful.
         *              - Empty `optional` means no solution found.
         *              - Populated `optional` contains projection details.
         *          - `ProjectionError` if the input is invalid or the OCCT
         *             projection fails.
         */
        TNBGEOM_ND_EXPORT std::expected<std::optional<ProjectionResult>, ProjectionError>
        try_project_point(const std::array<double, 3>& p) const noexcept;

        TNBGEOM_ND_EXPORT double calc_length() const;
    private:

        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Curve(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        friend struct core::occt_curve_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_CURVE_HXX
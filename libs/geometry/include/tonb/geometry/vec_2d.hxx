//
// Created by amir on 8/23/25.
//

#ifndef TONB_GEOMETRY_VEC_2D_HXX
#define TONB_GEOMETRY_VEC_2D_HXX
/**
 * @file
 * @brief 2D vector type (x, y) for geometry math.
 *
 * `tonb::geometry::Vec2d` represents a 2-component vector with double
 * precision and value semantics. It is intended for lightweight geometric
 * computations (offsets, directions, tangents) and interoperates with other
 * tonb geometry types (e.g., `Pnt2d`, `Box2d`).
 *
 * ## Semantics
 * - Components are ordered `(x, y)` in a right-handed XY plane.
 * - Arithmetic is element-wise unless stated otherwise.
 * - Zero vector `(0,0)` is allowed; normalisation of a near-zero vector
 *   returns a zero vector (or leaves the vector unchanged) depending on the
 *   implementation.
 *
 * ## Typical usage
 * @code
 * using tonb::geometry::Vec2d;
 *
 * Vec2d u{1.0, 2.0};
 * Vec2d v{3.0, -1.0};
 *
 * auto s  = u + v;            // (4, 1)
 * auto d  = u - v;            // (-2, 3)
 * auto k  = u * 2.0;          // (2, 4)   (scalar scale)
 * auto n  = u.normalized();   // unit direction of u (or (0,0) if u ~ 0)
 * auto dp = u.dot(v);         // 1*3 + 2*(-1) = 1
 * auto cz = u.cross(v);       // 2D pseudo-cross (scalar): x1*y2 - y1*x2
 * @endcode
 *
 * ## API sketch (align names to the implementation)
 * - **Constructors**
 *   - `Vec2d()` → (0,0)
 *   - `Vec2d(double x, double y)`
 * - **Accessors**
 *   - `double x() const noexcept;` / `double y() const noexcept;`
 *   - `Vec2d& set_x(double);` / `Vec2d& set_y(double);`
 *   - `std::array<double,2> to_array() const noexcept;`
 * - **Queries**
 *   - `double squared_norm() const noexcept;`
 *   - `double norm() const noexcept;`
 *   - `bool is_zero(double eps=1e-15) const noexcept;`
 *   - `bool is_finite() const noexcept;`
 *   - `bool almost_equal(const Vec2d&, double tol=1e-9) const noexcept;`
 * - **Algebra**
 *   - `Vec2d normalized(double eps=1e-15) const noexcept;`
 *   - `Vec2d scaled(double s) const noexcept;`
 *   - `double dot(const Vec2d&) const noexcept;`
 *   - `double cross(const Vec2d&) const noexcept; // z-component (scalar)`
 *   - `Vec2d perp_cw() const noexcept;  // ( y, -x )`
 *   - `Vec2d perp_ccw() const noexcept; // (-y,  x )`
 *   - `static Vec2d lerp(const Vec2d& a, const Vec2d& b, double t) noexcept;`
 * - **Operators (if provided)**
 *   - `+`, `-` (vector), unary `-`
 *   - `*`, `/` by scalar
 *   - `==`, `!=`
 *
 * ## Numerical notes
 * - Prefer `squared_norm()` for comparisons to avoid the cost of `sqrt()`.
 * - When normalising, treat `norm() <= eps` as zero to avoid overflow/NaN.
 *
 */

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

namespace tonb::geometry {
    // Forward Declarations
    class Pnt2d;

    class Vec2d {
    public:
        using Array = std::array<real, 2>;
    private:

        /*Private Data*/
        Array components_{};
    public:

        static TNBGEOM_EXPORT const int nb_cmpts;

        // default constructor
        TNBGEOM_EXPORT Vec2d() noexcept;

        // constructors
        Vec2d(const real x, const real y) noexcept : components_{x, y} {}
        explicit Vec2d(const Array& components) noexcept : components_{components} {}

        Vec2d(const Vec2d& other) noexcept = default;
        Vec2d(Vec2d&& other) noexcept = default;

        // Public functions and operators

        Vec2d& operator=(const Vec2d& other) noexcept = default;
        Vec2d& operator=(Vec2d&& other) noexcept = default;

        // Access
        TNB_NODISCARD const auto& components() const noexcept { return components_; }
        TNB_NODISCARD constexpr real u() const noexcept {return components_[0];}
        TNB_NODISCARD constexpr real v() const noexcept {return components_[1];}

        void set_u(const real u) noexcept {components_[0] = u;}
        void set_v(const real v) noexcept {components_[1] = v;}

        TNB_NODISCARD constexpr real operator[](const size_t i) const noexcept {return components_[i];}
        TNB_NODISCARD constexpr real& operator[](const size_t i) noexcept {return components_[i];}

        // common operators
        TNBGEOM_EXPORT Vec2d& operator+=(const Vec2d& rhs) noexcept;
        TNBGEOM_EXPORT Vec2d& operator-=(const Vec2d& rhs) noexcept;
        TNBGEOM_EXPORT Vec2d& operator*=(real rhs) noexcept;
        TNBGEOM_EXPORT Vec2d& operator/=(real rhs) noexcept;

        // transformation

        // standard math
        TNBGEOM_ND_EXPORT real dot(const Vec2d& rhs) const noexcept;
        TNBGEOM_ND_EXPORT real cross(const Vec2d& rhs) const noexcept;
        TNBGEOM_ND_EXPORT real length() const noexcept;
        TNBGEOM_ND_EXPORT real length_squared() const noexcept;
        TNBGEOM_ND_EXPORT real norm() const noexcept;
        TNBGEOM_ND_EXPORT real norm_squared() const noexcept;
        TNBGEOM_EXPORT void normalize(real eps = std::numeric_limits<real>::epsilon());
        TNBGEOM_EXPORT void add(const Vec2d& rhs) noexcept;
        TNBGEOM_EXPORT void add(real rhs) noexcept;
        TNBGEOM_EXPORT void sub(const Vec2d& rhs) noexcept;
        TNBGEOM_EXPORT void sub(real rhs) noexcept;

        friend TNBGEOM_EXPORT Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs) noexcept;
        friend TNBGEOM_EXPORT Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs) noexcept;
        friend TNBGEOM_EXPORT Vec2d operator*(const Vec2d& lhs, real rhs) noexcept;
        friend TNBGEOM_EXPORT Vec2d operator*(real lhs, const Vec2d& rhs) noexcept;
        friend TNBGEOM_EXPORT Vec2d operator/(const Vec2d& lhs, real rhs) noexcept;
    };
}
#endif //TONB_GEOMETRY_VEC_2D_HXX
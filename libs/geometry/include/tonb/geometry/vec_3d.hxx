//
// Created by amir on 8/23/25.
//

#ifndef TONB_GEOMETRY_VEC_3D_HXX
#define TONB_GEOMETRY_VEC_3D_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <limits>
#include <algorithm>

/**
 * @file
 * @brief 3D vector type with basic linear algebra utilities.
 *
 * `tonb::geometry::Vec3d` stores a 3-component vector `(u, v, w)` and provides
 * common arithmetic, norms, and products. It is a lightweight value type meant
 * for geometric computations (directions, offsets, normals).
 *
 * ## Semantics
 * - Components are stored in `components_[0..2]` and exposed as `(u, v, w)`.
 * - Operations are element-wise unless otherwise stated (e.g., dot/cross).
 * - The zero vector is allowed; `normalize()` guards against near-zero length
 *   with an epsilon.
 *
 * ## Example
 * @code
 * using tonb::geometry::Vec3d;
 *
 * Vec3d a{1.0, 0.0, 0.0};
 * Vec3d b{0.0, 1.0, 0.0};
 *
 * auto d  = a.dot(b);          // 0
 * auto n  = cross(a, b);       // (0,0,1)
 * auto s  = a + b;             // (1,1,0)
 * auto t  = 2.0 * s;           // (2,2,0)
 *
 * Vec3d c{3.0, 4.0, 0.0};
 * c.normalize();               // becomes (0.6, 0.8, 0.0)
 * @endcode
 *
 * @see dot(const Vec3d&, const Vec3d&), cross(const Vec3d&, const Vec3d&)
 */

namespace tonb::geometry {

    class Vec3d {
    public:
        using Array = std::array<double, 3>;
    private:

        /*Private Data*/
        Array components_{};
    public:

        /**
         * @brief Number of components (3).
         * @note Exposed as a static constant for generic code.
         */
        static TNBGEOM_EXPORT const int nb_cmpts;

        /// @brief Default-construct to (0,0,0)
        TNBGEOM_EXPORT Vec3d() noexcept;

        // constructors
        Vec3d(const real u, const real v, const real w) noexcept : components_{u, v, w} {}
        /// @brief Construct from an array `{u,v,w}`.
        explicit Vec3d(const Array& components) noexcept : components_{components} {}

        Vec3d(const Vec3d& other) noexcept = default;
        Vec3d(Vec3d&& other) noexcept = default;

        // Public functions and operators

        Vec3d& operator=(const Vec3d& other) noexcept = default;
        Vec3d& operator=(Vec3d&& other) noexcept = default;

        // Access
        TNB_NODISCARD const auto& components() const noexcept { return components_; }
        TNB_NODISCARD constexpr real u() const noexcept { return components_[0]; }
        TNB_NODISCARD constexpr real v() const noexcept { return components_[1]; }
        TNB_NODISCARD constexpr real w() const noexcept { return components_[2]; }

        void set_u(const real u) noexcept { components_[0] = u; }
        void set_v(const real v) noexcept { components_[1] = v; }
        void set_w(const real w) noexcept { components_[2] = w; }

        TNB_NODISCARD constexpr real operator[](const size_t i) const noexcept {return components_[i];}
        TNB_NODISCARD constexpr real& operator[](const size_t i) noexcept {return components_[i];}

        // common operators
        TNBGEOM_EXPORT Vec3d& operator+=(const Vec3d& rhs) noexcept;
        TNBGEOM_EXPORT Vec3d& operator-=(const Vec3d& rhs) noexcept;
        TNBGEOM_EXPORT Vec3d& operator*=(real rhs) noexcept;
        TNBGEOM_EXPORT Vec3d& operator/=(real rhs) noexcept;

        // transformation

        // standard math

        /**
         * @brief Dot (inner) product.
         * @return `u1*u2 + v1*v2 + w1*w2`
         */
        TNBGEOM_ND_EXPORT real dot(const Vec3d& rhs) const noexcept;
        /// \brief 3D cross product: this × v.
        /// \return A vector perpendicular to both operands (right-hand rule).
        /// \note The result is zero if the vectors are parallel or one is zero.
        TNBGEOM_ND_EXPORT Vec3d cross(const Vec3d& rhs) const noexcept;
        /// @brief Euclidean length (`sqrt(u^2+v^2+w^2)`).
        TNBGEOM_ND_EXPORT real length() const noexcept;
        /// @brief Squared length (`u^2+v^2+w^2`) — avoids `sqrt()`.
        TNBGEOM_ND_EXPORT real length_squared() const noexcept;
        /// @brief Alias for @ref length().
        TNBGEOM_ND_EXPORT real norm() const noexcept;
        /// @brief Alias for @ref length_squared().
        TNBGEOM_ND_EXPORT real norm_squared() const noexcept;
        /**
         * @brief Normalize in place to unit length when possible.
         * @param eps Small positive threshold if 'norm() <= eps', the vector is
         *        left unchanged to avoid overflow/NaN
         */
        TNBGEOM_EXPORT void normalize(real eps = std::numeric_limits<real>::epsilon());
        /// @brief Add a vector (component-wise) in place.
        TNBGEOM_EXPORT void add(const Vec3d& rhs) noexcept;

        /// @brief Add a scalar to all components in place.
        TNBGEOM_EXPORT void add(real rhs) noexcept;

        /// @brief Subtract a vector (component-wise) in place.
        TNBGEOM_EXPORT void sub(const Vec3d& rhs) noexcept;

        /// @brief Subtract a scalar from all components in place.
        TNBGEOM_EXPORT void sub(real rhs) noexcept;

        friend TNBGEOM_EXPORT Vec3d operator+(const Vec3d& lhs, const Vec3d& rhs) noexcept;
        friend TNBGEOM_EXPORT Vec3d operator+(real lhs, const Vec3d& rhs) noexcept;
        friend TNBGEOM_EXPORT Vec3d operator+(const Vec3d& lhs, real rhs) noexcept;
        friend TNBGEOM_EXPORT Vec3d operator-(const Vec3d& lhs, const Vec3d& rhs) noexcept;
        friend TNBGEOM_EXPORT Vec3d operator-(const Vec3d& lhs, real rhs) noexcept;
        friend TNBGEOM_EXPORT Vec3d operator*(real lhs, const Vec3d& rhs) noexcept;
        friend TNBGEOM_EXPORT Vec3d operator*(const Vec3d& lhs, real rhs) noexcept;
        friend TNBGEOM_EXPORT Vec3d operator/(const Vec3d& lhs, real rhs) noexcept;
    };

    /// @brief Free dot product wrapper: `lhs.dot(rhs)`.
    inline real dot(const Vec3d& lhs, const Vec3d& rhs) noexcept {return lhs.dot(rhs);}

    /// @brief Free cross product wrapper: `lhs.cross(rhs)`.
    inline Vec3d cross(const Vec3d& lhs, const Vec3d& rhs) noexcept {return lhs.cross(rhs);}
}
#endif //TONB_GEOMETRY_VEC_3D_HXX
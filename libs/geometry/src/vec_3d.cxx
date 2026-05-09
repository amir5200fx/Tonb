//
// Created by amir on 8/25/25.
//
#include <tonb/geometry/vec_3d.hxx>

#include <cmath>
#include <cmath>
#include <stdexcept>

namespace tonb::geometry {

    const int Vec3d::nb_cmpts = 3;

    Vec3d::Vec3d() noexcept : components_{0, 0, 0} {}

    Vec3d& Vec3d::operator+=(const Vec3d& rhs) noexcept {
        components_[0] += rhs.components_[0];
        components_[1] += rhs.components_[1];
        return *this;
    }
    Vec3d& Vec3d::operator-=(const Vec3d& rhs) noexcept {
        components_[0] -= rhs.components_[0];
        components_[1] -= rhs.components_[1];
        return *this;
    }
    Vec3d& Vec3d::operator*=(const real rhs) noexcept {
        components_[0] *= rhs;
        components_[1] *= rhs;
        return *this;
    }
    Vec3d& Vec3d::operator/=(const real rhs) noexcept {
        components_[0] /= rhs;
        components_[1] /= rhs;
        return *this;
    }

    real Vec3d::dot(const Vec3d& rhs) const noexcept {
        return components_[0] * rhs.components_[0] + components_[1] * rhs.components_[1] + components_[2] * rhs.
               components_[2];
    }
    Vec3d Vec3d::cross(const Vec3d& rhs) const noexcept {
        const double ax = u(), ay = v(), az = w();
        const double bx = rhs.u(), by = rhs.v(), bz = rhs.w();
        return Vec3d{
            ay * bz - az * by,  // u
            az * bx - ax * bz,  // v
            ax * by - ay * bx   // w
        };
    }

    real Vec3d::length() const noexcept {
        return sqrt(dot(*this));
    }
    real Vec3d::length_squared() const noexcept {
        return dot(*this);
    }
    real Vec3d::norm() const noexcept {
        return sqrt(dot(*this));
    }
    real Vec3d::norm_squared() const noexcept {
        return dot(*this);
    }
    void Vec3d::normalize(const real eps) {
        const auto len = norm();
        if (len <= eps) {
            throw std::invalid_argument("Vec3d::normalize() must be positive");
        }
        components_[0] /= len;
        components_[1] /= len;
        components_[2] /= len;
    }
    void Vec3d::add(const Vec3d& rhs) noexcept {
        components_[0] += rhs.components_[0];
        components_[1] += rhs.components_[1];
        components_[2] += rhs.components_[2];
    }
    void Vec3d::add(const real rhs) noexcept {
        components_[0] += rhs;
        components_[1] += rhs;
        components_[2] += rhs;
    }
    void Vec3d::sub(const Vec3d& rhs) noexcept {
        components_[0] -= rhs.components_[0];
        components_[1] -= rhs.components_[1];
        components_[2] -= rhs.components_[2];
    }
    void Vec3d::sub(const real rhs) noexcept {
        components_[0] -= rhs;
        components_[1] -= rhs;
        components_[2] -= rhs;
    }

    Vec3d operator+(const Vec3d& lhs, const Vec3d& rhs) noexcept {
        auto r = lhs;  r += rhs;  return r;
    }
    Vec3d operator+(const real lhs, const Vec3d& rhs) noexcept {
        auto r = Vec3d(lhs, lhs, lhs);  r+=rhs;  return r;
    }
    Vec3d operator+(const Vec3d& lhs, const real rhs) noexcept {
        auto r = Vec3d(rhs, rhs, rhs);  r+=lhs;  return r;
    }
    Vec3d operator-(const Vec3d& lhs, const Vec3d& rhs) noexcept {
        auto r = lhs;  r -= rhs;  return r;
    }
    Vec3d operator-(const Vec3d& lhs, const real rhs) noexcept {
        auto r = Vec3d(rhs, rhs, rhs);  r-=lhs;  return r;
    }
    Vec3d operator*(const real lhs, const Vec3d& rhs) noexcept {
        return {lhs * rhs.components_[0], lhs * rhs.components_[1], lhs * rhs.components_[2]};
    }
    Vec3d operator*(const Vec3d& lhs, const real rhs) noexcept {
        return rhs * lhs;
    }
    Vec3d operator/(const Vec3d& lhs, const real rhs) noexcept {
        auto r = lhs;  r /= rhs;  return r;
    }
}
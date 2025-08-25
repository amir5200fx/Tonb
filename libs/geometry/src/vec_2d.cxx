//
// Created by amir on 8/25/25.
//
#include <cmath>
#include <tonb/geometry/vec_2d.hxx>

namespace tonb::geometry {
    const int Vec2d::nb_cmpts = 2;

    Vec2d::Vec2d() noexcept : components_{0, 0} {}

    Vec2d& Vec2d::operator+=(const Vec2d& rhs) noexcept {
        components_[0] += rhs.components_[0];
        components_[1] += rhs.components_[1];
        return *this;
    }
    Vec2d& Vec2d::operator-=(const Vec2d& rhs) noexcept {
        components_[0] -= rhs.components_[0];
        components_[1] -= rhs.components_[1];
        return *this;
    }
    Vec2d& Vec2d::operator*=(const real rhs) noexcept {
        components_[0] *= rhs;
        components_[1] *= rhs;
        return *this;
    }
    Vec2d& Vec2d::operator/=(const real rhs) noexcept {
        components_[0] /= rhs;
        components_[1] /= rhs;
        return *this;
    }

    real Vec2d::dot(const Vec2d& rhs) const noexcept {
        return components_[0] * rhs.components_[0] + components_[1] * rhs.components_[1];
    }
    real Vec2d::cross(const Vec2d& rhs) const noexcept {
        return components_[0]*rhs.components_[1] - components_[1]*rhs.components_[0];
    }
    real Vec2d::length() const noexcept {
        return std::sqrt(components_[0]*components_[0] + components_[1]*components_[1]);
    }
    real Vec2d::length_squared() const noexcept {
        return components_[0]*components_[0] + components_[1]*components_[1];
    }
    real Vec2d::norm() const noexcept {
        return std::sqrt(components_[0]*components_[0] + components_[1]*components_[1]);
    }
    real Vec2d::norm_squared() const noexcept {
        return components_[0]*components_[0] + components_[1]*components_[1];
    }
    void Vec2d::normalize(const real eps) {
        const auto len = norm();
        if (len <= eps) {
            throw std::runtime_error("Vec2d::normalize: length too small");
        }
        components_[0] /= len;
        components_[1] /= len;
    }
    void Vec2d::add(const Vec2d &rhs) noexcept {
        this->operator+=(rhs);
    }
    void Vec2d::add(const real rhs) noexcept {
        this->operator+=(Vec2d(rhs, rhs));
    }
    void Vec2d::sub(const Vec2d &rhs) noexcept {
        this->operator-=(rhs);
    }
    void Vec2d::sub(const real rhs) noexcept {
        this->operator-=(Vec2d(rhs, rhs));
    }

    Vec2d operator+(const Vec2d& lhs, const Vec2d& rhs) noexcept {
        auto r = lhs; r += rhs; return r;
    }
    Vec2d operator-(const Vec2d& lhs, const Vec2d& rhs) noexcept {
        auto r = lhs; r -= rhs; return r;
    }
    Vec2d operator*(const Vec2d& lhs, const real rhs) noexcept {
        auto r = lhs; r *= rhs; return r;
    }
    Vec2d operator*(const real lhs, const Vec2d& rhs) noexcept {
        auto r = rhs; r *= lhs; return r;
    }
    Vec2d operator/(const Vec2d& lhs, const real rhs) noexcept {
        auto r = lhs; r /= rhs; return r;
    }
}
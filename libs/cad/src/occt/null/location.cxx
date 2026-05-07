//
// Created by amir on 8/26/25.
//
#include <tonb/cad/occt/location.hxx>

namespace tonb::cad::occt {
    struct Location::Impl {
        bool identity() const noexcept {return true;}
    };
    bool Location::is_identity() const noexcept {
        return true;
    }
    std::array<real, 16> Location::matrix() const noexcept {
        return {1,0,0,0,
               0,1,0,0,
               0,0,1,0,
               0,0,0,1};
    }
    std::array<real, 3> Location::apply_point(const std::array<real, 3> &p) const {
        return p; // identity behaviour without OCCT
    }
    std::array<real, 3> Location::apply_vector(const std::array<real, 3> &v) const {
        return v; // identity without OCCT
    }
    Location Location::inverted() const {
        return {};
    }
    Location Location::operator*(const Location &rhs) const {
        // No backend: identity composition
        return {};
    }
    Location& Location::operator*=(const Location &rhs) {
        *this = (*this) * rhs;
        return *this;
    }
}
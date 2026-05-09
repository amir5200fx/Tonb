//
// Created by amir on 8/24/25.
//
#include <tonb/geometry/occt/curve.hxx>

namespace tonb::geometry::occt {
    struct Curve::Impl {/*empty*/};

    bool Curve::is_valid() const noexcept {
        return false;
    }
    bool Curve::is_closed() const noexcept {
        return false;
    }
    bool Curve::is_periodic() const noexcept {
        return false;
    }
    int Curve::degree() const noexcept {
        return -1;
    }
    std::optional<std::pair<real, real> > Curve::parameter_range() const noexcept {
        return std::nullopt;
    }
    std::array<real, 3> Curve::value(double u) const {
        return {0,0,0};
    }
    Curve::D1 Curve::d1(double u) const {
        return {{0,0,0}, {0,0,0}};
    }
    Curve Curve::trimmed(double u0, double u1) const {
        return {};
    }

}
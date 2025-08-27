//
// Created by amir on 8/26/25.
//
#include <tonb/geometry/occt/curve_2d.hxx>
#include <stdexcept>

namespace tonb::geometry::occt {

    struct Curve2d::Impl {
        bool valid() const noexcept {return false;}
    };

    bool Curve2d::is_valid() const noexcept {
        return pimpl_ && pimpl_->valid();
    }
    bool Curve2d::is_closed() const noexcept {
        return false;
    }
    bool Curve2d::is_periodic() const noexcept {
        return false;
    }
    int Curve2d::degree() const noexcept {
        return -1;
    }
    std::optional<std::pair<real, real> > Curve2d::parameter_range() const noexcept {
        return std::nullopt;
    }
    std::array<real, 2> Curve2d::value(const real u) const {
        return {};
    }
    Curve2d::D1 Curve2d::d1(const real u) const {
        return {{0,0}, {0,0}};
    }
    Curve2d Curve2d::trimmed(const real u0, const real u1) const {
        return {};
    }

}
//
// Created by amir on 8/26/25.
//
#include <tonb/geometry/occt/surface.hxx>

#include <stdexcept>

namespace tonb::geometry::occt {
    struct Surface::Impl {
        bool valid() const noexcept {return false;}
    };

    bool Surface::is_valid() const noexcept {
        return false;
    }
    std::optional<std::tuple<real, real, real, real>> Surface::bounds() const noexcept {
        return std::nullopt;
    }
    std::array<real, 3> Surface::value(const real, const real) const {
        throw std::logic_error("Surface::value: no backend available (built without OCCT)");
    }
    Surface::D1 Surface::d1(const real, const real) const {
        throw std::logic_error("Surface::d1: no backend available (built without OCCT)");
    }
    Surface Surface::trimmed(const real, const real, const real, const real) const {
        return Surface{};
    }

    bool Surface::is_u_closed() const noexcept {return false;}
    bool Surface::is_v_closed() const noexcept {return false;}
    bool Surface::is_u_periodic() const noexcept {return true;}
    bool Surface::is_v_periodic() const noexcept {return true;}
    real Surface::u_period() const noexcept {return 0;}
    real Surface::v_period() const noexcept {return 0;}
}
//
// Created by amir on 8/26/25.
//
#include <tonb/cad/occt/face.hxx>
#include <stdexcept>

namespace tonb::cad::occt {
    struct Face::Impl {
    };

    bool Face::is_valid() const noexcept {
        return false;
    }
    std::optional<std::tuple<real, real, real, real> > Face::uv_bounds() const {
        return std::nullopt;
    }
    std::array<real, 3> Face::value(real u, real v) const {
        throw std::logic_error("Face::value no backend available (built without OCCT)");
    }
    std::array<real, 3> Face::normal(real u, real v) const {
        throw std::logic_error("Face::normal no backend available (built without OCCT)");
    }

    bool Face::is_forward() const noexcept {return false;}
    bool Face::is_reversed() const noexcept {return false;}

}
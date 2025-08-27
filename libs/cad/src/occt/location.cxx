//
// Created by amir on 8/26/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/cad/occt/location.hxx>
#include <tonb/cad/occt/core/location_helpers.hxx>
#include <tonb/geometry/occt/core/adapters.hxx>
#include <tonb/geometry/occt/core/vector_helpers.hxx>

// OCCT
#include <opencascade/TopLoc_Location.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Vec.hxx>
#include <opencascade/gp_Trsf.hxx>

#include <array>
#include <memory>

namespace tonb::cad::occt {

    bool Location::is_identity() const noexcept {
        // Null pimpl_ also means identity.
        return !pimpl_ || pimpl_->identity();
    }
    std::array<real, 16> Location::matrix() const noexcept {
        // Row-major 4x4
        if (is_identity()) {
            return {1,0,0,0,
                        0,1,0,0,
                        0,0,1,0,
                        0,0,0,1};
        }
        const gp_Trsf& t = pimpl_->l.Transformation();
        // gp_Trsf::Value(i, j) is 1-based, j in [1..4] gives rotation + translation
        return {
            t.Value(1,1), t.Value(1,2), t.Value(1,3), t.Value(1,4),
            t.Value(2,1), t.Value(2,2), t.Value(2,3), t.Value(2,4),
            t.Value(3,1), t.Value(3,2), t.Value(3,3), t.Value(3,4),
            0.0, 0.0, 0.0, 1.0
        };
    }

    std::array<real, 3> Location::apply_point(const std::array<real, 3> &p) const {
        if (is_identity()) return p;
        gp_Pnt tp = geometry::occt::core::make_gp_pnt(p);
        tp.Transform(pimpl_->l.Transformation());
        return geometry::occt::core::from_gp_to_array(tp);
    }
    std::array<real, 3> Location::apply_vector(const std::array<real, 3> &v) const {
        if (is_identity()) return v;
        gp_Vec tv = {static_cast<Standard_Real>(v[0]), static_cast<Standard_Real>(v[1]), static_cast<Standard_Real>(v[2])};
        tv.Transform(pimpl_->l.Transformation());
        return {static_cast<real>(tv.X()), static_cast<real>(tv.Y()), static_cast<real>(tv.Z())};
    }

    Location Location::inverted() const {
        if (is_identity()) return {};
        return Location{std::make_shared<Impl>(pimpl_->l.Inverted())};
    }
    Location Location::operator*(const Location &rhs) const {
        if (is_identity()) return rhs;
        if (rhs.is_identity()) return *this;
        TopLoc_Location res = pimpl_->l.Multiplied(rhs.pimpl_ ? rhs.pimpl_->l : TopLoc_Location());
        return Location{std::make_shared<Impl>(res)};
    }
    Location& Location::operator*=(const Location &rhs) {
        *this = (*this) * rhs;
        return *this;
    }

}
#else
static_assert(true, "src/occt/location.cxx compiled without TONB_WITH_OCCT");
#endif
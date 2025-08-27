//
// Created by amir on 8/26/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/surface.hxx>
#include <tonb/geometry/occt/core/surface_helpers.hxx>
#include <tonb/geometry/occt/core/adapters.hxx>

// OCCT
#include <opencascade/Geom_Surface.hxx>
#include <opencascade/Geom_RectangularTrimmedSurface.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Vec.hxx>

#include <stdexcept>
#include <utility>
#include <sys/stat.h>

namespace tonb::geometry::occt {

    bool Surface::is_valid() const noexcept {
        return pimpl_ && !pimpl_->h.IsNull();
    }
    std::optional<std::tuple<real, real, real, real>> Surface::bounds() const noexcept {
        if (!is_valid()) return std::nullopt;
        Standard_Real u0, u1, v0, v1;
        pimpl_->h->Bounds(u0, u1, v0, v1);
        const auto bs = Handle(Geom_BoundedSurface)::DownCast(pimpl_->h);
        if (bs.IsNull()) return std::nullopt;
        return std::make_tuple(static_cast<real>(u0), static_cast<real>(u1), static_cast<real>(v0),
                               static_cast<real>(v1));
    }

    std::array<real, 3> Surface::value(const real u, const real v) const {
        if (!is_valid()) throw std::logic_error("Surface::value: invalid surface");
        gp_Pnt p;
        pimpl_->h->D0(u, v, p);
        return {static_cast<real>(p.X()), static_cast<real>(p.Y()), static_cast<real>(p.Z())};
    }
    Surface::D1 Surface::d1(const real u, const real v) const {
        if (!is_valid()) throw std::logic_error("Surface::value: invalid surface");
        gp_Pnt p;
        gp_Vec du, dv;
        pimpl_->h->D1(u, v, p, du, dv);
        return D1{core::from_gp_to_array(p), core::from_gp_to_array(du), core::from_gp_to_array(dv)};
    }
    Surface Surface::trimmed(const real u1, const real u2, const real v1, const real v2) const {
        if (!is_valid()) throw std::logic_error("Surface::value: invalid surface");
        Handle(Geom_Surface) h = new Geom_RectangularTrimmedSurface(pimpl_->h, u1, u2, v1, v2);
        return Surface{std::make_shared<Impl>(std::move(h))};
    }

    bool Surface::is_u_closed() const noexcept {
        return is_valid() ? pimpl_->h->IsUClosed() : false;
    }
    bool Surface::is_v_closed() const noexcept {
        return is_valid() ? pimpl_->h->IsVClosed() : false;
    }
    bool Surface::is_u_periodic() const noexcept {
        return is_valid() ? pimpl_->h->IsUPeriodic() : false;
    }
    bool Surface::is_v_periodic() const noexcept {
        return is_valid() ? pimpl_->h->IsVPeriodic() : false;
    }

    real Surface::u_period() const noexcept {
        return (is_valid() && pimpl_->h->IsUClosed())
        ? static_cast<real>(pimpl_->h->UPeriod())
        : 0.0;
    }
    real Surface::v_period() const noexcept {
        return (is_valid() && pimpl_->h->IsVClosed())
        ? static_cast<real>(pimpl_->h->VPeriod())
        : 0.0;
    }

}
#else
static_assert(true, "src/occt/surface.cxx compiled without TONB_WITH_OCCT");
#endif
//
// Created by amir on 8/26/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/surface.hxx>
#include <tonb/geometry/occt/core/surface_helpers.hxx>
#include <tonb/geometry/occt/core/adapters.hxx>

// OCCT
#include <opencascade/Geom_BSplineSurface.hxx>
#include <opencascade/Geom_Surface.hxx>
#include <opencascade/Geom_RectangularTrimmedSurface.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Vec.hxx>
#include <opencascade/TColgp_Array2OfPnt.hxx>
#include <opencascade/TColStd_Array2OfReal.hxx>
#include <opencascade/TColStd_Array1OfReal.hxx>
#include <opencascade/TColStd_Array1OfInteger.hxx>

#include <stdexcept>
#include <utility>
#include <sys/stat.h>

namespace tonb::geometry::occt {

    Surface::Surface(const std::vector<std::vector<Pnt3d> > &poles, const std::vector<std::vector<real> > &weights, const std::vector<real> &u_knots, const std::vector<real> &v_knots, const std::vector<int> &u_mults, const std::vector<int> &v_mults, const int u_deg, const int v_deg) {

        try {
            Handle(Geom_Surface) g = new Geom_BSplineSurface(core::to_colgp_array2(poles),
                                                             core::to_colstd_array2(weights),
                                                             core::to_colstd_array(u_knots),
                                                             core::to_colstd_array(v_knots),
                                                             core::to_colstd_array(u_mults),
                                                             core::to_colstd_array(v_mults), u_deg, v_deg);
            pimpl_ = std::make_shared<Impl>(std::move(g));

        } catch (const Standard_Failure& err) {
            throw std::runtime_error(std::string("Surface::Surface(): ") + err.GetMessageString());
        }
    }



    bool Surface::is_valid() const noexcept {
        return pimpl_ && !pimpl_->h.IsNull();
    }
    std::optional<std::tuple<real, real, real, real>> Surface::bounds() const noexcept {
        if (!is_valid()) return std::nullopt;
        Standard_Real u0, u1, v0, v1;
        pimpl_->h->Bounds(u0, u1, v0, v1);
        //const auto bs = Handle(Geom_BoundedSurface)::DownCast(pimpl_->h);
        //if (bs.IsNull()) return std::nullopt;
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

    Surface::QuadMesh Surface::make_uniform_quad_mesh(const int nu, const int nv, const bool closePeriodic) const {
        if (!is_valid())
        throw std::logic_error("Surface::make_uniform_quad_mesh: invalid surface");

        if (nu < 1 || nv < 1)
            throw std::logic_error("Surface::make_uniform_quad_mesh: nu and nv must be >= 1");

        const auto b = bounds();
        if (!b.has_value())
            throw std::logic_error("Surface::make_uniform_quad_mesh: surface bounds unavailable");

        auto [u1, u2, v1, v2] = *b;

        // Detect periodicity; we can omit the seam if requested.
        const bool uClosed = is_u_periodic() && closePeriodic;
        const bool vClosed = is_v_periodic() && closePeriodic;

        // Vertex grid sizes
        const int nuPts = uClosed ? nu : (nu + 1);
        const int nvPts = vClosed ? nv : (nv + 1);

        QuadMesh mesh;
        mesh.points.resize(static_cast<size_t>(nuPts) * static_cast<size_t>(nvPts));
        mesh.uv.resize(mesh.points.size());

        // Parameter steps chosen so that:
        // - When not closing: last vertex hits the upper bound exactly.
        // - When closing: last vertex is excluded (no duplication at the seam).
        const real du = (u2 - u1) / static_cast<real>(nu);
        const real dv = (v2 - v1) / static_cast<real>(nv);

        auto uv_at = [&](const int i, const int j) -> std::array<real, 2> {
            const bool lastU = (!uClosed) && (i == nuPts - 1);
            const bool lastV = (!vClosed) && (j == nvPts - 1);
            const real u = lastU ? u2 : (u1 + du * static_cast<real>(i));
            const real v = lastV ? v2 : (v1 + dv * static_cast<real>(j));
            return {u, v};
        };

        auto idx = [&](const int iu, const int jv) -> int {
            // row-major: v changes slowest (rows), u fastest (columns)
            return jv * nuPts + iu;
        };

        // Sample vertices
        for (int j = 0; j < nvPts; ++j) {
            for (int i = 0; i < nuPts; ++i) {
                const auto uv = uv_at(i, j);
                const auto p  = value(uv[0], uv[1]);
                const int k   = idx(i, j);
                mesh.points[static_cast<size_t>(k)] = Pnt3d{p[0], p[1], p[2]};
                mesh.uv[static_cast<size_t>(k)]     = {uv[0], uv[1]};
            }
        }

        // Quads: nu * nv
        mesh.quads.reserve(static_cast<size_t>(nu) * static_cast<size_t>(nv));

        auto wrapU = [&](const int i) { return uClosed ? (i % nu) : i; };
        auto wrapV = [&](const int j) { return vClosed ? (j % nv) : j; };

        for (int j = 0; j < nv; ++j) {
            for (int i = 0; i < nu; ++i) {
                const int i0 = wrapU(i);
                const int j0 = wrapV(j);
                const int i1 = wrapU(i + 1);
                const int j1 = wrapV(j + 1);

                const int v00 = idx(i0, j0);
                const int v10 = idx(i1, j0);
                const int v11 = idx(i1, j1);
                const int v01 = idx(i0, j1);

                mesh.quads.push_back({v00, v10, v11, v01});
            }
        }

        return mesh;
    }

    void * Surface::native_backend_handle() noexcept {
        if (!pimpl_) return nullptr;
        // Expose the address of the *handle object* (NOT the underlying Geom_Surface*).
        return static_cast<void*>(&(pimpl_->h));
    }

    const void * Surface::native_backend_handle() const noexcept {
        if (!pimpl_) return nullptr;
        // Expose the address of the *handle object* (NOT the underlying Geom_Surface*).
        return static_cast<void*>(&(pimpl_->h));
    }

    Surface Surface::from_native_backend_handle(const void *ptr) {
        Surface s; // invalid by default
        if (!ptr) return s;

        // The pointer is expected to point to an opencascade::handle<Geom_Surface>
        // Copy-construct out internal handle from it.
        const opencascade::handle<Geom_Surface>& href =
            *reinterpret_cast<const opencascade::handle<Geom_Surface>*>(ptr);

        // Build pIpml from the handle
        s.pimpl_ = std::make_shared<Impl>(Impl{href});
        return s;
    }
}
#else
static_assert(true, "src/occt/surface.cxx compiled without TONB_WITH_OCCT");
#endif
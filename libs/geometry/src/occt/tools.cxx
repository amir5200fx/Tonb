//
// Created by amir on 8/24/25.
//
#include <tonb/config.hxx>

#if defined(TONB_WITH_OCCT)
#include <tonb/geometry/occt/tools.hxx>
#include <tonb/geometry/occt/curve.hxx>
#include <tonb/geometry/occt/core/adapters.hxx>
#include <tonb/geometry/occt/core/curve_helpers.hxx>
#include <tonb/geometry/occt/core/point_helpers.hxx>

#include <opencascade/GeomAPI_Interpolate.hxx>
#include <opencascade/TColgp_HArray1OfPnt.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/StdFail_NotDone.hxx>

namespace tonb::geometry::occt {

    Curve Tools::interpolate(const std::vector<Point> &qs, const real tol) {
        if (qs.empty()) {
            throw std::runtime_error("Tools::interpolate: empty qs vector");
        }
        if (qs.size() < 2) {
            throw std::runtime_error("Tools::interpolate: qs vector too small");
        }
        Handle(TColgp_HArray1OfPnt) points = new TColgp_HArray1OfPnt(1, static_cast<int>(qs.size()));
        for (int i = 0; i < qs.size(); i++) {
            points->SetValue(i + 1, core::occt_point_access::get(qs[i]));
        }
        try {
            GeomAPI_Interpolate app(points, false, tol);
            app.Perform();

            return core::occt_curve_access::make(app.Curve());
        } catch (const StdFail_NotDone &e) {
            std::ostringstream oss;
            oss<<"Tools::interpolate: failed to interpolate"<<'\n'
            <<e.GetMessageString()<<'\n';
            throw std::runtime_error(oss.str());
        } catch (...) {
            throw std::runtime_error("Tools::interpolate: failed to interpolate - Unknown error");
        }
    }

}
#endif
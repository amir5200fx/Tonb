//
// Created by amir on 8/27/25.
//
#include <tonb/config.hxx>
#if defined(TONB_HAS_OCCT_ADAPTERS)
#include <tonb/cad2d/occt/tools.hxx>
#include <tonb/geometry/occt/core/point_2d_helpers.hxx>
#include <tonb/geometry/occt/core/curve_2d_helpers.hxx>
#include <tonb/geometry/occt/core/circle_2d_helpers.hxx>

// OCCT
#include <opencascade/GCE2d_MakeSegment.hxx>
#include <opencascade/GCE2d_MakeArcOfCircle.hxx>
#include <opencascade/Standard_Failure.hxx>

namespace tonb::cad2d::occt {
    geometry::occt::Curve2d Tools::make_segment(const geometry::occt::Point2d& p0, const geometry::occt::Point2d& p1) {
        try {
            using namespace geometry::occt;
            const GCE2d_MakeSegment maker(core::occt_point_2d_access::get(p0), core::occt_point_2d_access::get(p1));
            return core::occt_curve_2d_access::make(maker.Value());
        } catch (const Standard_Failure& err) {
            throw std::runtime_error(std::string("thrown OCCT exception: ") + err.GetMessageString());
        }
    }
    geometry::occt::Curve2d Tools::make_circle_arc(const geometry::occt::Point2d& p0, const geometry::occt::Point2d& p1, const geometry::occt::Point2d& p2) {
        try {
            using namespace geometry::occt;
            const GCE2d_MakeArcOfCircle maker(core::occt_point_2d_access::get(p0), core::occt_point_2d_access::get(p1), core::occt_point_2d_access::get(p2));
            return core::occt_curve_2d_access::make(maker.Value());
        } catch (const Standard_Failure& err) {
            throw std::runtime_error(std::string("thrown OCCT exception: ") + err.GetMessageString());
        }
    }

    Tools::Curve Tools::make_circle_arc(const Circle &circle, const double angle0, const double angle1) {
        try {
            using namespace geometry::occt;
            const GCE2d_MakeArcOfCircle maker(core::occt_circle_2d_access::get(circle), angle0, angle1);
            return core::occt_curve_2d_access::make(maker.Value());
        } catch (const Standard_Failure& err) {
            throw std::runtime_error(std::string("thrown OCCT exception: ") + err.GetMessageString());
        }
    }
}
#else
#endif


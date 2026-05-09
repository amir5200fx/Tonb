//
// Created by amir on 8/24/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/cad/occt/core/body_helpers.hxx>
#include <tonb/cad/occt/core/edge_helpers.hxx>
#include <tonb/geometry/occt/core/axis_helpers.hxx>
#include <tonb/geometry/occt/core/curve_helpers.hxx>
#include <tonb/cad/occt/tools.hxx>
#include <tonb/cad/occt/body.hxx>
#include <tonb/cad/occt/edge.hxx>

// OCCT
#include <opencascade/BRepPrimAPI_MakeRevol.hxx>
#include <opencascade/BRepBuilderAPI_MakeEdge.hxx>
#include <opencascade/Standard_Failure.hxx>

namespace tonb::cad::occt {

    Edge Tools::make_edge(const Curve & c) {
        try {
            return core::occt_edge_access::make(BRepBuilderAPI_MakeEdge(geometry::occt::core::occt_curve_access::get(c)));
        } catch (const Standard_Failure& e) {
            std::ostringstream os;
            os << "OCCT exception thrown on Tools::make_edge(const Curve&) function: " << '\n'
            << e.GetMessageString() << '\n';
            throw std::runtime_error(os.str());
        } catch (...) {
            throw std::runtime_error("An Unknown OCCT exception thrown on Tools::make_edge(const curve&) function");
        }
    }

    Body Tools::make_revol(const Edge & edge, const Axis & axis) {
        try {
            return core::from_topo(BRepPrimAPI_MakeRevol(core::occt_edge_access::get(edge), geometry::occt::core::occt_axis_access::get(axis)));
        } catch (const Standard_Failure& e) {
            std::ostringstream os;
            os << "OCCT exception thrown on Tools::make_revol(const Edge&, const Axis&) function: " << '\n'
            << e.GetMessageString() << '\n';
            throw std::runtime_error(os.str());
        } catch (...) {
            throw std::runtime_error("An Unknown OCCT exception thrown on Tools::make_edge(const curve&) function");
        }
    }

}

#else
static_assert(true, "src/occt/tools.cxx built without TONB_WITH_OCCT");
#endif

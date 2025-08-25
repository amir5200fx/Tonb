//
// Created by amir on 8/24/25.
//
#pragma once
#ifndef TONB_CAD_OCCT_TOOLS_HXX
#define TONB_CAD_OCCT_TOOLS_HXX
#include <tonb/cad/module.hxx>
#include <tonb/geometry/occt_fwd.hxx>
#include <tonb/cad/occt_fwd.hxx>
namespace tonb::cad::occt {

    class Tools {
    public:

        using Curve = geometry::occt::Curve;
        using Axis = geometry::occt::Axis;

        static TNBCAD_EXPORT Edge make_edge(const Curve&);
        static TNBCAD_EXPORT Body make_revol(const Edge&, const Axis&);
    };
}
#endif //TONB_CAD_OCCT_TOOLS_HXX
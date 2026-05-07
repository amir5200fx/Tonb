//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_CAD_TOOLS_HXX
#define TONB_CAD_TOOLS_HXX
#include <tonb/cad/module.hxx>
#include <tonb/cad/body_fwd.hxx>
#include <tonb/cad/curve_fwd.hxx>
#include <tonb/cad/edge_fwd.hxx>
#include <tonb/cad/axis_fwd.hxx>
namespace tonb::cad {
    class Tools {
    public:

        static TNBCAD_EXPORT Edge make_edge(const Curve& curve);
        static TNBCAD_EXPORT Body make_revol(const Edge&, const Axis&);
    };
}
#endif //TONB_CAD_TOOLS_HXX
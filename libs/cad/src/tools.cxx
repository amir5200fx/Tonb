//
// Created by amir on 8/27/25.
//
#include <tonb/cad/tools.hxx>

#include <tonb/cad/edge.hxx>
#include <tonb/cad/curve.hxx>
#include <tonb/cad/body.hxx>

#include <tonb/cad/occt/tools.hxx>
namespace tonb::cad {
    Edge Tools::make_edge(const Curve &curve) {
        return occt::Tools::make_edge(curve);
    }
    Body Tools::make_revol(const Edge &edge, const Axis &axis) {
        return occt::Tools::make_revol(edge, axis);
    }
}
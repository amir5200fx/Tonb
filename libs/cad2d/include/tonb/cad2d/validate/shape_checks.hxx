//
// Created by amir on 1/24/26.
//
#pragma once
#ifndef TONB_CAD2d_VALIDATE_SHAPE_CHECKS_HXX
#define TONB_CAD2d_VALIDATE_SHAPE_CHECKS_HXX

#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>

#include <memory>

namespace tonb::cad2d::topo {
    class Shape;
}

namespace tonb::cad2d::validate {

    struct ShapeCheckOptions {
        bool check_vertices = true;
        bool check_halfedges = true;
        bool check_wires = true;
        bool check_faces = true;

        bool require_closed_wires = true;

        bool verify_open_wire_ends = true;
    };

    topo::Result<void> check_shape(const topo::Shape& shape, const topo::Tolerance& tol, const ShapeCheckOptions& opt = {});
}

#endif //TONB_CAD2d_VALIDATE_SHAPE_CHECKS_HXX
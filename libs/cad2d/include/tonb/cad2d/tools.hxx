//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_CAD2D_TOOLS_HXX
#define TONB_CAD2D_TOOLS_HXX
#include <tonb/cad2d/module.hxx>
#include <tonb/cad2d/point_fwd.hxx>
#include <tonb/cad2d/curve_fwd.hxx>
namespace tonb::cad2d {
    class Tools {
    public:
        static TNBCAD2D_EXPORT Curve make_segment(const Point& p0, const Point& p1);
        static TNBCAD2D_EXPORT Curve make_circle_arc(const Point& p0, const Point& p1, const Point& p2);
    };
}
#endif //TONB_CAD2D_TOOLS_HXX
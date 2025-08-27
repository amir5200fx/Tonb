//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_CAD2D_OCCT_TOOLS_HXX
#define TONB_CAD2D_OCCT_TOOLS_HXX
#include <tonb/cad2d/module.hxx>
#include <tonb/geometry/occt/curve_2d.hxx>
#include <tonb/geometry/occt/point_2d.hxx>
namespace tonb::cad2d::occt {
    class Tools {
    public:
        using Curve = geometry::occt::Curve2d;
        using Point = geometry::occt::Point2d;

        static TNBCAD2D_EXPORT Curve make_segment(const Point& p0, const Point& p1);
        static TNBCAD2D_EXPORT Curve make_circle_arc(const Point& p0, const Point& p1, const Point& p2);
    };
}
#endif  // TONB_CAD2D_OCCT_TOOLS_HXX

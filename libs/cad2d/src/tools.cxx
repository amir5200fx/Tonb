//
// Created by amir on 8/27/25.
//
#include <tonb/cad2d/occt/tools.hxx>
#include <tonb/cad2d/curve.hxx>
#include <tonb/cad2d/tools.hxx>

namespace tonb::cad2d {
    Curve Tools::make_segment(const Point& p0, const Point& p1) {
        return occt::Tools::make_segment(p0, p1);
    }
    Curve Tools::make_circle_arc(const Point &p0, const Point &p1, const Point &p2) {
        return occt::Tools::make_circle_arc(p0, p1, p2);
    }

}
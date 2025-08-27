//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_CAD2D_CURVE_FWD_HXX
#define TONB_CAD2D_CURVE_FWD_HXX
namespace tonb::geometry::occt {
    class Curve2d;
}
namespace tonb::cad2d {
    using Curve = geometry::occt::Curve2d;
}
#endif //TONB_CAD2D_CURVE_FWD_HXX
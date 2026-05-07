//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_CAD2D_TRANSFORM_FWD_HXX
#define TONB_CAD2D_TRANSFORM_FWD_HXX
namespace tonb::geometry::occt {
    class Transform2d;
}
namespace tonb::cad2d {
    using Transform = tonb::geometry::occt::Transform2d;
}
#endif //TONB_CAD2D_TRANSFORM_FWD_HXX
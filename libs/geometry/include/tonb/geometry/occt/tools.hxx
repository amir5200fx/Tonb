//
// Created by amir on 8/24/25.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_TOOLS_HXX
#define TONB_GEOMETRY_OCCT_TOOLS_HXX
#include <tonb/geometry/occt/point.hxx>

#include <vector>
namespace tonb::geometry::occt {

    // Forward Declarations
    class Curve;
    class Tools {
    public:

        static TNBGEOM_EXPORT Curve interpolate(const std::vector<Point>& qs, real tol = 1e-6);
    };
}
#endif //TONB_GEOMETRY_OCCT_TOOLS_HXX
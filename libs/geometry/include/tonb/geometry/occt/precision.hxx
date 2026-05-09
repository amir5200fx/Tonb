//
// Created by amir on 02/09/2025.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_PRECISION_HXX
#define TONB_GEOMETRY_OCCT_PRECISION_HXX
#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>
namespace tonb::geometry::occt {
    class Precision {
    public:
        static TNBGEOM_EXPORT bool is_infinite(real x);
    };
}
#endif //TONB_GEOMETRY_OCCT_PRECISION_HXX
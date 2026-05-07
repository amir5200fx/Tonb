//
// Created by amir on 1/25/26.
//
/**
 * @file curve_ops.hxx
 * @brief Lightweight operations on cad2d::Curve wrapper types.
 *
 * This module calls wrapper methods only (no OCCT includes).
 */
#pragma once
#ifndef TONB_CAD2D_GEOM_CURVE_OPS_HXX
#define TONB_CAD2D_GEOM_CURVE_OPS_HXX

#include <utility>

#include <tonb/cad2d/curve.hxx>
#include <tonb/cad2d/point.hxx>

namespace tonb::cad2d::geom {

    /**
     * @brief Return curve parameter domain.
     */
    TNB_NODISCARD inline std::pair<real, real> domain(const Curve& c) {
        return {c.first_parameter(), c.last_parameter()};
    }

    /**
     * @brief Evaluate curve point at parameter u.
     */
    TNB_NODISCARD inline Point value(const Curve& c, const real u) {
        return Point{c.value(u)};
    }
}
#endif //TONB_CAD2D_GEOM_CURVE_OPS_HXX
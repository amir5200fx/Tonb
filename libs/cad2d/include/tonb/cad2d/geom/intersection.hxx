//
// Created by amir on 5/7/26.
//
/**
 * @file intersection.hxx
 * @brief Declares bounded 2D curve-span intersection utilities.
 *
 * The current implementation is intentionally segment-first:
 * - segment-segment is implemented manually and deterministically,
 * - segment-arc and arc-arc are supported for circular arc spans,
 * - unsupported curve types fail explicitly via Result diagnostics.
 *
 * This public API remains kernel-agnostic at the cad2d surface even when
 * backend-specific geometry classification is used internally.
 */
#pragma once
#ifndef TONB_CAD2D_GEOM_INTERSECTION_HXX
#define TONB_CAD2D_GEOM_INTERSECTION_HXX

#include <tonb/cad2d/module.hxx>
#include <tonb/cad2d/curve.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/geom/intersection_result.hxx>

namespace tonb::cad2d::geom {

    /**
     * @brief Numerical controls for bounded-span intersection queries.
     */
    struct IntersectionOptions {
        /**
         * @brief Point-space tolerance used for geometric comparisons.
         */
        real point_tolerance = 1.0e-9;

        /**
         * @brief Parameter-space tolerance used for span membership checks.
         */
        real param_tolerance = 1.0e-12;

        /**
         * @brief Periodic parameter used for circular support.
         */
        real angular_period = 2.0 * 3.141592653589793238462643383279502884L;
    };

    /**
     * @brief Intersect two bounded curve spans.
     *
     * The spans are given by:
     * - first curve over [first_u0, first_u1]
     * - second curve over [second_u0, second_u1]
     *
     * The returned parameters remain consistent with the input span direction.
     *
     * @param first First curve.
     * @param first_u0 First span start parameter.
     * @param first_u1 First span end parameter.
     * @param second Second curve.
     * @param second_u0 Second span start parameter.
     * @param second_u1 Second span end parameter.
     * @param options Numerical tolerances and periodic controls.
     * @return IntersectionResult on success; explicit Result error otherwise.
     */
    TNBCAD2D_ND_EXPORT topo::Result<IntersectionResult> intersect_bounded_spans(
        const Curve& first,
        real first_u0,
        real first_u1,
        const Curve& second,
        real second_u0,
        real second_u1,
        const IntersectionOptions& options = {});
}

#endif // TONB_CAD2D_GEOM_INTERSECTION_HXX

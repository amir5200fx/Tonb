/**
 * @file wire_length.hxx
 * @brief Declares geometric length utilities for cad2d wires.
 *
 * This module provides a geometry-aware utility that computes the total length
 * of a topological wire by summing the arc lengths of its boundary half-edge
 * spans.
 *
 * Architectural intent
 * --------------------
 * - topology ownership remains in cad2d/topo,
 * - geometry lookup remains in cad2d/geom,
 * - numerical integration remains in tonb::numerics,
 * - this module performs only the algorithmic orchestration required to bridge
 *   those layers.
 *
 * The implementation is intentionally defensive:
 * - missing or expired half-edges fail with Result error information,
 * - missing curve ids fail,
 * - unbounded or non-finite curve domains fail,
 * - non-converged numerical integration fails with a descriptive diagnostic.
 */
#pragma once
#ifndef TONB_CAD2D_ALGO_WIRE_LENGTH_HXX
#define TONB_CAD2D_ALGO_WIRE_LENGTH_HXX

#include <tonb/cad2d/module.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/numerics/arc_length_integration.hxx>

#include <memory>

namespace tonb::cad2d::topo {
    class Wire;
}

namespace tonb::cad2d::geom {
    class CurveStore;
}

namespace tonb::cad2d::algo {

    /**
     * @brief Configuration for wire-length estimation.
     *
     * The numerical controls are delegated directly to the public arc-length
     * integration API in tonb::numerics.
     */
    struct WireLengthOptions {
        numerics::ArcLengthOptions integration{};
    };

    /**
     * @brief Compute the total geometric length of a wire.
     *
     * @param wire Wire whose boundary length will be measured.
     * @param curves Geometry registry used to resolve half-edge curve ids.
     * @param options Numerical integration controls.
     * @return Total wire length on success; failure diagnostic otherwise.
     */
    TNBCAD2D_ND_EXPORT topo::Result<real> wire_length(
        const std::shared_ptr<topo::Wire>& wire,
        const geom::CurveStore& curves,
        const WireLengthOptions& options = {});
}

#endif // TONB_CAD2D_ALGO_WIRE_LENGTH_HXX

//
// Created by amir on 5/7/26.
//
/**
 * @file face_area.hxx
 * @brief Declares polygonal face-area and orientation utilities for cad2d.
 *
 * This module provides the first face-level geometric utilities for cad2d.
 * The current implementation is intentionally limited to polygonal boundaries
 * represented by segment-like half-edge spans. General curved-area integration
 * is outside the scope of this issue and must be added separately in a future
 * milestone.
 *
 * Scope of this module
 * --------------------
 * - compute signed area of a wire interpreted as a polygon boundary
 * - classify wire orientation from the sign of the signed area
 * - compute signed area of a face as outer-loop area plus hole-loop areas
 * - detect whether a face matches the documented orientation convention
 * - optionally normalise wire and face orientation using existing twin
 *   half-edges
 *
 * Orientation convention
 * ----------------------
 * This module documents and uses the following standard convention:
 *
 * - outer boundary : counter-clockwise (CCW)
 * - hole boundaries: clockwise (CW)
 *
 * Under that convention:
 * - a CCW loop has positive signed area
 * - a CW loop has negative signed area
 * - a properly oriented face has positive total area
 *
 * Important restriction
 * ---------------------
 * The algorithms in this file are designed for segment-only polygonal loops.
 * To keep the implementation honest, the default behaviour checks that each
 * half-edge span behaves like a straight segment within a configurable
 * tolerance. If a span is curved, the utility fails explicitly instead of
 * silently approximating it as polygonal.
 */
#pragma once
#ifndef TONB_CAD2D_ALGO_FACE_AREA_HXX
#define TONB_CAD2D_ALGO_FACE_AREA_HXX

#include <tonb/cad2d/module.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/base/precision.hxx>

#include <memory>

namespace tonb::cad2d::topo {
    class Wire;
    class Face;
}

namespace tonb::cad2d::geom {
    class CurveStore;
}

namespace tonb::cad2d::algo {

    /**
     * @brief Orientation classification for polygon loops.
     */
    enum class LoopOrientation : std::uint8_t {
        collinear = 0,  ///< Area magnitude is below the configured epsilon.
        ccw,            ///< Positive signed area.
        cw              ///< Negative signed area.
    };

    /**
     * @brief Options controlling polygon-area and orientation utilities.
     */
    struct FaceAreaOptions {
        /**
         * @brief Area epsilon used to classify nearly-zero signed areas.
         */
        real area_epsilon = 1.0e-12;

        /**
         * @brief Tolerance used to decide whether a half-edge span behaves like
         *        a straight segment.
         *
         * The current implementation samples the midpoint of the referenced
         * curve span and compares it against the chord midpoint. If the
         * deviation exceeds this tolerance, the edge is rejected as non-linear.
         */
        real linearity_tolerance = 1.0e-9;

        /**
         * @brief If true, reject non-linear edge spans.
         *
         * This should remain true for the current milestone because only
         * segment-only polygonal faces are supported.
         */
        bool require_linear_geometry = true;

        /**
         * @brief If true, update next/prev links when a wire is normalised.
         */
        bool update_next_prev_on_normalize = true;
    };

    /**
     * @brief Compute the signed area of a wire interpreted as a polygon loop.
     *
     * The wire must be closed and continuous, and each boundary half-edge must
     * resolve to a segment-like geometric span.
     *
     * @param wire Boundary wire to evaluate.
     * @param curves Curve registry used to resolve curve ids.
     * @param options Polygon-area options and tolerances.
     * @return Signed area on success.
     */
    TNBCAD2D_ND_EXPORT topo::Result<real> signed_area_of_wire_polygon(
        const std::shared_ptr<topo::Wire>& wire,
        const geom::CurveStore& curves,
        const FaceAreaOptions& options = {});

    /**
     * @brief Classify wire orientation from its signed polygon area.
     *
     * @param wire Boundary wire to classify.
     * @param curves Curve registry used to resolve curve ids.
     * @param options Polygon-area options and tolerances.
     * @return Loop orientation classification on success.
     */
    TNBCAD2D_ND_EXPORT topo::Result<LoopOrientation> classify_wire_orientation(
        const std::shared_ptr<topo::Wire>& wire,
        const geom::CurveStore& curves,
        const FaceAreaOptions& options = {});

    /**
     * @brief Compute the signed area of a polygonal face.
     *
     * The returned value is:
     *
     *     A_face = A_outer + sum(A_hole_i)
     *
     * so a face that follows the documented convention (outer CCW, holes CW)
     * yields a positive total area equal to outer minus holes.
     *
     * @param face Face to evaluate.
     * @param curves Curve registry used to resolve curve ids.
     * @param options Polygon-area options and tolerances.
     * @return Signed face area on success.
     */
    TNBCAD2D_ND_EXPORT topo::Result<real> signed_area_of_face_polygon(
        const std::shared_ptr<topo::Face>& face,
        const geom::CurveStore& curves,
        const FaceAreaOptions& options = {});

    /**
     * @brief Check whether a face matches the standard orientation convention.
     *
     * Standard convention:
     * - outer boundary is CCW
     * - hole boundaries are CW
     *
     * @param face Face to inspect.
     * @param curves Curve registry used to resolve curve ids.
     * @param options Polygon-area options and tolerances.
     * @return True on success if the face already matches the convention.
     */
    TNBCAD2D_ND_EXPORT topo::Result<bool> face_has_standard_orientation(
        const std::shared_ptr<topo::Face>& face,
        const geom::CurveStore& curves,
        const FaceAreaOptions& options = {});

    /**
     * @brief Reverse a wire by replacing its boundary with the reversed twin sequence.
     *
     * This function requires that every boundary half-edge has a valid twin.
     * The wire boundary is rewritten as:
     *
     *     [e0, e1, ..., en-1] -> [twin(en-1), ..., twin(e1), twin(e0)]
     *
     * Optionally, the next/prev links of the new sequence are updated to match
     * the new boundary order.
     *
     * This utility intentionally changes only the wire boundary ordering and the
     * optional next/prev links. It does not update face assignment or any other
     * higher-level topology relationships.
     *
     * @param wire Wire to reverse.
     * @param options Polygon-area options and normalize behaviour.
     * @return True if the wire was changed, false if it was already degenerate.
     */
    TNBCAD2D_ND_EXPORT topo::Result<bool> reverse_wire_using_twins(
        const std::shared_ptr<topo::Wire>& wire,
        const FaceAreaOptions& options = {});

    /**
     * @brief Normalise a face to the standard orientation convention.
     *
     * Standard convention:
     * - outer boundary is CCW
     * - hole boundaries are CW
     *
     * Wires are reversed only when necessary. Reversal is performed using
     * existing twin half-edges, so each affected wire must be reversible
     * through valid twin links.
     *
     * @param face Face to normalise.
     * @param curves Curve registry used to resolve curve ids.
     * @param options Polygon-area options and normalize behaviour.
     * @return True if any wire was modified.
     */
    TNBCAD2D_ND_EXPORT topo::Result<bool> normalize_face_polygon_orientations(
        const std::shared_ptr<topo::Face>& face,
        const geom::CurveStore& curves,
        const FaceAreaOptions& options = {});
}

#endif // TONB_CAD2D_ALGO_FACE_AREA_HXX

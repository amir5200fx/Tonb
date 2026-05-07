//
// Created by amir on 1/24/26.
//
/**
 * @file face_checks.hxx
 * @brief Declares topology-only validation routines for cad2d Face objects.
 *
 * This module validates the structural integrity of a face boundary in the
 * cad2d topology layer. The checks performed here are intentionally limited to
 * topology and ownership/connectivity consistency. They do not perform
 * geometric containment tests, area-orientation checks, or wire intersection
 * algorithms.
 *
 * The current validation responsibilities are:
 * - verify that the outer wire exists and is valid,
 * - verify that all hole wires exist and are valid,
 * - verify that hole-wire identity is unique,
 * - verify that the outer wire is not reused as a hole wire,
 * - verify that no half-edge object is reused across the outer boundary and
 *   any hole boundary, or across two different hole boundaries.
 *
 * This last disjointness rule is important because a topological face boundary
 * must be composed of disjoint boundary cycles. Reusing the same half-edge in
 * two loops is invalid even if the loops were otherwise individually well
 * formed.
 */

#pragma once
#ifndef TONB_CAD2D_VALIDATE_FACE_CHECKS_HXX
#define TONB_CAD2D_VALIDATE_FACE_CHECKS_HXX

#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>

#include <memory>

namespace tonb::cad2d::topo {
    class Face;
}

namespace tonb::cad2d::validate {

    /**
     * @brief Validate the outer and hole wires referenced by a face.
     *
     * This routine checks only the existence and individual validity of the
     * boundary wires. It does not check whether half-edges are shared across
     * wires. Use @ref check_face_edge_disjointness for that.
     *
     * @param f Face to validate.
     * @param tol Tolerance policy forwarded to wire checks.
     * @param requireClosed If true, each boundary wire must be closed.
     * @return Success if the face boundary references are structurally valid.
     */
    topo::Result<void> check_face_wires(
        const std::shared_ptr<topo::Face>& f,
        const topo::Tolerance& tol,
        bool requireClosed = true);

    /**
     * @brief Validate that the face outer wire and hole wires do not reuse
     *        the same half-edge objects.
     *
     * The comparison is based on half-edge object identity (pointer identity),
     * not on geometric coincidence. This is a topology-level rule.
     *
     * @param f Face to validate.
     * @return Success if all boundary cycles are edge-disjoint.
     */
    topo::Result<void> check_face_edge_disjointness(
        const std::shared_ptr<topo::Face>& f);

    /**
     * @brief Run the full topology-only face validation sequence.
     *
     * This combines:
     * - boundary wire validation, and
     * - edge disjointness validation.
     *
     * @param f Face to validate.
     * @param tol Tolerance policy forwarded to wire checks.
     * @param requireClosed If true, each boundary wire must be closed.
     * @return Success if the face passes all topology-only checks.
     */
    topo::Result<void> check_face(
        const std::shared_ptr<topo::Face>& f,
        const topo::Tolerance& tol,
        bool requireClosed = true);
}

#endif // TONB_CAD2D_VALIDATE_FACE_CHECKS_HXX

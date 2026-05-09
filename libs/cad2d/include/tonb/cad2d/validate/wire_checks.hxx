//
// Created by amir on 1/24/26.
//
/**
 * @file wire_checks.hxx
 * @brief Topology-only validation routines for Wire invariants.
 *
 * This module validates the integrity of a Wire boundary list and, optionally,
 * the consistency between that boundary list and any next or prev links stored
 * on the underlying half-edges.
 *
 * The checks are intentionally geometry-free:
 * - No curve evaluation
 * - self-intersection checks
 * - No containment checks
 *
 * Error model:
 * - Functions return topo::Result<void> with a descriptive message and ErrorCode.
 *
 * Intended usage:
 * - Builder post-condition checks (WireBuilder)
 * - Regression tests
 * - Debug validation when editing topology
 */
#pragma once
#ifndef TONB_CAD2d_VALIDATE_WIRE_CHECKS_HXX
#define TONB_CAD2d_VALIDATE_WIRE_CHECKS_HXX

#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>

#include <memory>

namespace tonb::cad2d::topo {
    class Wire;
}

namespace tonb::cad2d::validate {

    /**
     * @brief Validate that a wire's boundary list does not contain expired edges.
     *
     * This check verifies:
     * - wire pointer is non-null
     * - wire boundary list contains at least one edge (optional, see allowEmpty)
     * - every boundary edge reference can be locked (no expired weak pointers)
     *
     * It does not verify continuity, closure, or next/prev structure.
     *
     * @param w Wire to validate.
     * @param allowEmpty If true, empty boundary is treated as success.
     * @return Success if the boundary list contains only valid edge references.
     */
    topo::Result<void> check_boundary_refs(const std::shared_ptr<topo::Wire>& w, bool allowEmpty = false);

    /**
     * @brief Validate boundary continuity and optional closure using the Wire methods.
     *
     * This check delegates to:
     * - Wire::check_continuous(tol)
     * - Wire::check_closed(tol) if requireClosed is true
     *
     * @param w Wire to validate.
     * @param tol Tolerance policy used for endpoint matching.
     * @param requireClosed If true, requires the wire to be closed.
     * @return Success if continuity and closure requirements are satisfied.
     *
     */
    topo::Result<void> check_continuity(const std::shared_ptr<topo::Wire>& w, const topo::Tolerance& tol, bool requireClosed = true);

    /**
     * @brief Validate that wire boundary order agrees with half-edge next and prev links.
     *
     * This check is only meaningful if builders assign next and prev links. It verifies:
     * - For each boundary edge ei, if ei->next exists then it equals e(i+1)
     * - For each boundary edge ei, if ei->prev exists then it equals e(i-1)
     *
     * For closed wires, indices wrap around.
     * For open wires (requireClosed=false), callers typically set:
     * - first.prev == null
     * - last.next == null
     * The check can validate that pattern if verifyOpenEnds is true.
     *
     * Important:
     * - This check does not require next and prev to be present. It only checks
     *   them when they exist.
     *
     * @param w Wire to validate.
     * @param requireClosed If true, expects wrap-around order.
     * @param verifyOpenEnds If true and requireClosed is false, checks open-end nulls.
     * @return Success if next/prev links agree with boundary order.
     */
    topo::Result<void> check_next_prev_matches_boundary(const std::shared_ptr<topo::Wire>& w, bool requireClosed = true, bool verifyOpenEnds = true);

    /**
     * @brief Combined wire validation.
     *
     * Runs in this order:
     *  1) check_boundary_refs
     *  2) check_continuity
     *  3) check_next_pre_matches_boundary
     *
     * The order is deterministic to provide stable error reporting in tests.
     *
     * @param w Wire to validate
     * @param tol Tolerance policy used for continuity and closure.
     * @param requireClosed If true, requires closure.
     * @param verifyOpenEnds For open wires, validate first.prev and last.next behaviour.
     * @return Success if all checks pass.
     */
    topo::Result<void> check_wire(const std::shared_ptr<topo::Wire>& w, const topo::Tolerance& tol, bool requireClosed = true, bool verifyOpenEnds = true);
}
#endif //TONB_CAD2d_VALIDATE_WIRE_CHECKS_HXX
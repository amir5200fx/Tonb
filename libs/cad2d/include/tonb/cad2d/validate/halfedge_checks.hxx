//
// Created by amir on 1/24/26.
//
/**
 * @file halfedge_checks.hxx
 * @brief Topology-only validation routines for individual half-edges.
 *
 * This module contains the fundamental, non-geometric checks that establish
 * whether a half-edge is structurally usable inside the cad2d topology graph.
 *
 * Scope of this module
 * --------------------
 * The checks here are intentionally restricted to topology. They validate only
 * the graph relationships stored directly on topo::HalfEdge and the immediate
 * entities it references:
 *
 * - start / end vertex references
 * - twin symmetry and basic twin compatibility
 * - next / prev reciprocity and self-link exclusion
 *
 * The following concerns are deliberately out of scope here:
 *
 * - curve existence or evaluation
 * - parameter-domain validation
 * - endpoint agreement with underlying curve geometry
 * - wire continuity and closure
 * - face-level or shape-level consistency
 *
 * Those belong to dedicated validation modules so that the overall validate
 * package remains layered and easy to reason about.
 *
 * Error handling policy
 * ---------------------
 * All routines return topo::Result<void>. Validation failures are reported as
 * structured recoverable errors instead of throwing exceptions. This keeps the
 * module suitable for builders, tests, command-line diagnostics, and future
 * batch validation workflows.
 */
#pragma once
#ifndef TONB_CAD2D_VALIDATE_HALFEDGE_CHECKS_HXX
#define TONB_CAD2D_VALIDATE_HALFEDGE_CHECKS_HXX

#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/module.hxx>

#include <memory>

namespace tonb::cad2d::topo {
    class HalfEdge;
}

namespace tonb::cad2d::validate {

    /**
     * @brief Validate that the half-edge has valid endpoint vertex references.
     *
     * The check verifies that:
     * - the half-edge pointer itself is non-null,
     * - start() and end() are both resolvable,
     * - start and end do not point to the same vertex object.
     *
     * This is a purely topological endpoint check. It does not compare the
     * vertex positions to any geometric curve.
     *
     * @param e Half-edge to inspect.
     * @return Success if endpoint references are structurally valid.
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_endpoints(const std::shared_ptr<topo::HalfEdge>& e);

    /**
     * @brief Validate the twin relationship of a half-edge.
     *
     * The check verifies that when a twin exists:
     * - it is not the same object as the input edge,
     * - the relationship is reciprocal (twin->twin() == e),
     * - the twin does not have the same traversal endpoints as e,
     * - the twin references the same underlying curve id,
     * - the twin carries the opposite orientation.
     *
     * A missing twin is allowed because open boundaries are valid in several
     * modelling stages.
     *
     * @param e Half-edge to inspect.
     * @return Success if the twin relationship is absent or structurally valid.
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_twin(const std::shared_ptr<topo::HalfEdge>& e);

    /**
     * @brief Validate local next/prev neighbourhood consistency.
     *
     * The check verifies that when next or prev links exist:
     * - neither points back to the same half-edge,
     * - next->prev() resolves back to the current half-edge,
     * - prev->next() resolves back to the current half-edge.
     *
     * Missing next/prev links are allowed because open chains and partially
     * constructed wires are valid intermediate states.
     *
     * @param e Half-edge to inspect.
     * @return Success if next/prev links are absent or structurally valid.
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_next_prev(const std::shared_ptr<topo::HalfEdge>& e);

    /**
     * @brief Run the complete topology-only half-edge validation sequence.
     *
     * This convenience entry point applies:
     * - check_endpoints()
     * - check_twin()
     * - check_next_prev()
     *
     * in that order and returns at the first failure.
     *
     * @param e Half-edge to validate.
     * @return Success if all topology-only half-edge checks pass.
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_halfedge(const std::shared_ptr<topo::HalfEdge>& e);
}

#endif // TONB_CAD2D_VALIDATE_HALFEDGE_CHECKS_HXX

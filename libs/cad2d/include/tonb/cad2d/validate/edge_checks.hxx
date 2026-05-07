//
// Created by amir on 5/7/26.
//
/**
 * @file edge_checks.hxx
 * @brief Declares validation routines for topo::Edge.
 *
 * This module introduces validation of first-class edge invariants. Unlike the
 * older half-edge-only view, topo::Edge expresses that two half-edges belong to
 * the same undirected topological edge. Validators in this module therefore
 * treat edge invariants as stronger than incidental twin symmetry.
 */
#pragma once
#ifndef TONB_CAD2D_VALIDATE_EDGE_CHECKS_HXX
#define TONB_CAD2D_VALIDATE_EDGE_CHECKS_HXX

#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/module.hxx>

#include <memory>

namespace tonb::cad2d::topo {
    class Edge;
}

namespace tonb::cad2d::validate {

    /**
     * @brief Validate the explicit owner/member relationship of a topo::Edge.
     *
     * The check verifies that:
     * - the edge pointer is non-null,
     * - forward() and reverse() both resolve,
     * - they are distinct half-edge objects,
     * - each half-edge points back to the same edge through HalfEdge::edge().
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_edge_membership(const std::shared_ptr<topo::Edge>& edge);

    /**
     * @brief Validate pair-level edge invariants between the owned half-edges.
     *
     * The check verifies that:
     * - the pair is reciprocal through twin links,
     * - endpoints reverse one another,
     * - curve ids match,
     * - orientations are opposite,
     * - parameter spans are the reverse of one another.
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_edge_pair(const std::shared_ptr<topo::Edge>& edge);

    /**
     * @brief Run full edge validation.
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_edge(const std::shared_ptr<topo::Edge>& edge);
}

#endif // TONB_CAD2D_VALIDATE_EDGE_CHECKS_HXX

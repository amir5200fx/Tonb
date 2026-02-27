//
// Created by amir on 2/27/26.
//
#pragma once
/**
 * @file halfedge_geometry.hxx
 * @brief Geometry-aware validation checks for topology half-edges.
 *
 * This module adds validation that requires geometry access via cad2d wrappers.
 *
 * Design constraints:
 *  - Must not include OCCT headers
 *  - Must operate on cad2d::Curve wrapper objects via geom::CurveStore.
 *  - Must return topo::Result<void> (no exceptions propagate).
 *
 * Current scope:
 * - Validate that the start/end vertices of a HalfEdge match the curve evaluation
 *   at its stored parameters u0/u1 within the provided tolerance.
 */
#ifndef TONB_HALFEDGE_GEOMETRY_HXX
#define TONB_HALFEDGE_GEOMETRY_HXX

#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/topo/result.hxx>

namespace tonb::cad2d::validate {
    /**
     * @brief Validate half-edge endpoint agreement with its bound curve.
     *
     * @details
     * For a given half-edge e:
     *  - curve_id must be non-zero
     *  - curve must exist in store
     *  - Let P0 = curve.value(u0), P1 = curve.value(u1)
     *  - Let V0 = e->start()->position(), V1 = e->end()->position()
     *  - Require |P0 - V0| <= tol.linear and |P1 - V1| <= tol.linear
     *
     * Notes:
     *  - This function is geometry-aware and should be called only when caller
     *    has access to the CurveStore that owns the referenced curve ids.
     *  - This function does not validate parameter domain, degeneracy, or orientation.
     *    Those are handled by a separate issue (Issue 2).
     *
     * @param e     Half-edge to validate.
     * @param store Curve registry used to resolve curve_id -> cad2d::Curve.
     * @param tol   Tolerance policy used for agreement check.
     *
     * @return topo::Result<void> success or failure with diagnostic message.
     */
    topo::Result<void> check_halfedge_geometry(const std::shared_ptr<topo::HalfEdge>& e, const geom::CurveStore& store, const topo::Tolerance& tol);
}

#endif //TONB_HALFEDGE_GEOMETRY_HXX
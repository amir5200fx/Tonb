//
// Created by amir on 2/27/26.
//
/**
 * @file halfedge_geometry.hxx
 * @brief Geometry-aware validation routines for a single topology half-edge.
 *
 * This module is the bridge between pure topology and the cad2d geometry
 * registry. It validates that a topo::HalfEdge is not only topologically well
 * formed, but also geometrically consistent with the curve segment it claims to
 * represent.
 *
 * Architectural position
 * ----------------------
 * - topo/ remains geometry-kernel-free and stores only curve ids and parameters.
 * - geom/ owns the actual cad2d::Curve wrapper objects via geom::CurveStore.
 * - validate/halfedge_geometry uses the store to resolve the bound curve and
 *   compare curve-derived points with topological vertices.
 *
 * Checks performed here
 * ---------------------
 * - half-edge pointer validity
 * - endpoint vertex availability
 * - non-zero curve id
 * - curve existence in the supplied store
 * - finite and ordered curve parameter domain
 * - finite stored parameters u0 and u1
 * - parameter inclusion in the curve domain, with tolerance
 * - non-degenerate parametric span
 * - orientation agreement with parameter ordering
 * - endpoint agreement between curve evaluation and topology vertices
 *
 * This module intentionally does not validate neighbouring edges, wires, or
 * face-level properties. Those are handled elsewhere.
 */
#pragma once
#ifndef TONB_CAD2D_VALIDATE_HALFEDGE_GEOMETRY_HXX
#define TONB_CAD2D_VALIDATE_HALFEDGE_GEOMETRY_HXX

#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/module.hxx>

#include <memory>

namespace tonb::cad2d::validate {

    /**
     * @brief Validate geometric consistency of a half-edge against CurveStore.
     *
     * @param e Half-edge to validate.
     * @param store Geometry registry used to resolve curve ids.
     * @param tol Validation tolerance policy.
     * @return Success if the half-edge is geometrically consistent with its bound curve.
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_halfedge_geometry(const std::shared_ptr<topo::HalfEdge>& e,
                                                                  const geom::CurveStore& store,
                                                                  const topo::Tolerance& tol);
}

#endif // TONB_CAD2D_VALIDATE_HALFEDGE_GEOMETRY_HXX

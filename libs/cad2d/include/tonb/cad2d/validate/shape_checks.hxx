//
// Created by amir on 1/24/26.
//
/**
 * @file shape_checks.hxx
 * @brief High-level validation entry points for the cad2d topology model.
 *
 * This module provides the top-level validation routine for topo::Shape. It is
 * responsible for orchestrating lower-level validation modules over the shape's
 * registered entities.
 *
 * Two validation modes are supported:
 *
 * 1. Topology-only validation
 *    Uses half-edge, wire, and face checks that do not require geometry access.
 *
 * 2. Geometry-aware validation
 *    Extends the topology-only pass by validating each half-edge against a
 *    supplied geom::CurveStore.
 *
 * The goal is to keep shape validation explicit and configurable. Callers that
 * do not have geometry available can still validate the shape structurally,
 * while callers with a curve registry can opt into stronger model guarantees.
 */
#pragma once
#ifndef TONB_CAD2D_VALIDATE_SHAPE_CHECKS_HXX
#define TONB_CAD2D_VALIDATE_SHAPE_CHECKS_HXX

#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/module.hxx>

namespace tonb::cad2d::topo {
    class Shape;
}

namespace tonb::cad2d::validate {

    /**
     * @brief Configuration switches controlling shape validation coverage.
     */
    struct ShapeCheckOptions {
        bool check_vertices = true;         ///< Reserved for future vertex-specific structural checks.
        bool check_halfedges = true;        ///< Run topology-only half-edge checks.
        bool check_edges = true;            ///< Run first-class edge checks.
        bool check_wires = true;            ///< Run wire checks.
        bool check_faces = true;            ///< Run face checks.
        bool check_geometry = false;        ///< Run geometry-aware half-edge checks when a CurveStore is available.

        bool require_closed_wires = true;   ///< Require closed wires for wire and face validation.
        bool verify_open_wire_ends = true;  ///< For open wires, validate null prev/next at the ends.
    };

    /**
     * @brief Validate a shape using topology-only checks.
     *
     * @param shape Shape to validate.
     * @param tol Tolerance policy used by wire, face, and future vertex checks.
     * @param opt Validation options.
     * @return Success if the requested topology-only checks pass.
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_shape(const topo::Shape& shape,
                                                      const topo::Tolerance& tol,
                                                      const ShapeCheckOptions& opt = {});

    /**
     * @brief Validate a shape using topology-only and optional geometry-aware checks.
     *
     * Geometry checks are applied only when opt.check_geometry is true. When that
     * switch is false, this overload behaves like the topology-only overload.
     *
     * @param shape Shape to validate.
     * @param store Curve registry used by geometry-aware validation.
     * @param tol Tolerance policy used throughout the validation pass.
     * @param opt Validation options.
     * @return Success if all requested checks pass.
     */
    TNBCAD2D_ND_EXPORT topo::Result<void> check_shape(const topo::Shape& shape,
                                                      const geom::CurveStore& store,
                                                      const topo::Tolerance& tol,
                                                      const ShapeCheckOptions& opt = {});
}

#endif // TONB_CAD2D_VALIDATE_SHAPE_CHECKS_HXX

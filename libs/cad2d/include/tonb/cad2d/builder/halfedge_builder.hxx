//
// Created by amir on 1/22/26.
//
/**
 * @file halfedge_builder.hxx
 * @brief Declares the HalfEdgeBuilder class for constructing half-edges and pairs.
 *
 * HalfEdgeBuilder creates directed half-edges and sets basic connectivity
 * (start and end vertices). It also supports creating a twin pair in one call.
 *
 * Geometry binding remains abstract through curve ids and parametric spans.
 */
#pragma once
#ifndef TONB_CAD2D_BUILD_HALFEDGE_BUILDER_HXX
#define TONB_CAD2D_BUILD_HALFEDGE_BUILDER_HXX

#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/curve_fwd.hxx>

namespace tonb::cad2d::geom {
    class CurveStore;
}
namespace tonb::cad2d::build {

    class HalfEdgeBuilder {
    public:
        /**
         * @brief Construct a HalfEdgeBuilder bound to a shape.
         * @param shape Target topology shape used to allocate half-edges.
         */
        explicit HalfEdgeBuilder(topo::Shape& shape) : shape_(shape) {}

        /**
         * @brief Create a single directed half-edge and set its endpoints.
         *
         * This does not create or set a twin. It also does not set next or prev.
         *
         * @param start Start vertex.
         * @param end End vertex.
         * @param curveId Opaque curve identifier (geometry binding is external).
         * @param u0 Start parameter.
         * @param u1 End parameter.
         * @param dir Orientation along the curve segment.
         * @param tol Local tolerance for the edge.
         * @return Result containing the created half-edge.
         */
        TNBCAD2D_ND_EXPORT topo::Result<std::shared_ptr<topo::HalfEdge> > create(
            const std::shared_ptr<topo::Vertex> &start, const std::shared_ptr<topo::Vertex> &end, topo::Id curveId,
            double u0, double u1, topo::Orientation dir, double tol = 1.e-9) const;

        /**
         * @brief Create a twin pair of half-edges (a directed edge in both directions).
         *
         * The returned pair is (forward, reverse) as created. The function sets:
         * - start and end vertices on both half-edges
         * - twin links between the pair
         * - vertex incident links if they are not already set
         *
         * @param a First vertex.
         * @param b Second vertex.
         * @param curveId Opaque curve identifier.
         * @param u0 Start parameter in the forward direction.
         * @param u1 End parameter in the forward direction.
         * @param tol Local tolerance for both edges.
         * @return Result containing the pair (ab, ba).
         */
        TNBCAD2D_ND_EXPORT topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge> > >
        create_pair(const std::shared_ptr<topo::Vertex> &a, const std::shared_ptr<topo::Vertex> &b, topo::Id curveId,
                    double u0, double u1, double tol = 1.e-9) const;

        /**
         * @brief Create a single half-edge by binding a cad2d::Curve through a CurveStore.
         *
         * This function:
         * - validates that the curve is valid and bounded (parameter_range exists)
         * - validates (u0, u1) ordering matches the requested orientation
         * - registers the curve in the store and uses the returned curve id
         * - delegates allocation and connectivity to create(...)
         *
         * @param store Geometry curve registry.
         * @param curve Curve wrapper to bind.
         * @param start Start vertex.
         * @param end End vertex.
         * @param u0 Start parameter.
         * @param u1 End parameter.
         * @param dir Orientation along curve (forward expects u0<u1, reversed expects u0?u1).
         * @param tol local edge tolerance.
         * @param eps Parametric epsilon used for domain checks.
         */
        TNBCAD2D_ND_EXPORT topo::Result<std::shared_ptr<topo::HalfEdge> > create_from_curve(
            geom::CurveStore &store, const Curve &curve, const std::shared_ptr<topo::Vertex> &start,
            const std::shared_ptr<topo::Vertex> &end, real u0, real u1, topo::Orientation dir, real tol = 1.e-9,
            real eps = 1.e-12) const;

        /**
         * @brief Create a twin pari by binding a cad2d::Curve through a CurveStore.
         *
         * This is equivalent to:
         *  - register curve once in store
         *  - create_pair(...) using the retuned curve id
         *
         * The returned pair is (ab, ba). The reverse edge uses swapped parameters and reversed orientation.
         */
        TNBCAD2D_ND_EXPORT topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge> > >
        create_pair_from_curve(geom::CurveStore &store, const Curve &curve, const std::shared_ptr<topo::Vertex> &a,
                               const std::shared_ptr<topo::Vertex> &b, real u0, real u1, real tol = 1.e-9,
                               real eps = 1.e-12) const;
    private:
      topo::Shape& shape_;
    };
}
#endif //TONB_CAD2D_BUILD_HALFEDGE_BUILDER_HXX
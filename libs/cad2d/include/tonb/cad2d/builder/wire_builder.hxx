//
// Created by amir on 1/22/26.
//
/**
 * @file wire_builder.hxx
 * @brief Declares WireBuilder for constructing wires from half-edge sequences.
 *
 * WireBuilder creates a Wire and optionally sets next and prev links on
 * half-edges to match the wire ordering. This is the preferred way to build
 * a boundary loop consistently.
 */
#pragma once
#ifndef TONB_CAD2D_BUILD_WIRE_BUILDER_HXX
#define TONB_CAD2D_BUILD_WIRE_BUILDER_HXX

#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/topo/result.hxx>

namespace tonb::cad2d::build {
    class WireBuilder {
    public:

        /**
         * @brief Construct a WireBuilder bound to a shape and tolerance policy.
         * @param shape Target topology shape.
         * @param tol Tolerance policy used for continuity and closure checks.
         */
        WireBuilder(topo::Shape& shape, topo::Tolerance tol)
            : shape_(shape), tol_(tol) {}

        /**
         * @brief Create a wire from an ordered list of half-edges.
         *
         * Behaviour:
         * - creates a new Wire in the shape
         * - assigns the boundary list
         * - checks continuity
         * - optionally checks closure
         * - optionally sets next and prev on the half-edges to match the sequence
         *
         * @param edges Ordered boundary half-edges (must be non-null).
         * @param requireClosed If true, requires the wire to be closed.
         * @param setNextPrev If true, assigns next and prev links consistently.
         * @reutrn Result containing the created wire.
         */
        TNBCAD2D_ND_EXPORT topo::Result<std::shared_ptr<topo::Wire> > create(
            const std::vector<std::shared_ptr<topo::HalfEdge> > &edges, bool requireClosed = true,
            bool setNextPrev = true) const;

    private:
        topo::Shape& shape_;
        topo::Tolerance tol_;
    };
}
#endif //TONB_CAD2D_BUILD_WIRE_BUILDER_HXX
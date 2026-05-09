//
// Created by amir on 1/22/26.
//
/**
 * @file vertex_builder.hxx
 * @brief Declares the VertexBuilder class for constructing vertices in a Shape.
 *
 * VertexBuilder provides a controlled way to create vertices. At this stage it
 * supports two modes:
 *  - always create a new vertex
 *  - reuse an exiting vertex within a tolerance (optional, linear scan)
 *
 * This module is intentionally lightweight and does not use hashing or spatial
 * indices. Those can be added later if needed.
 */
#pragma once
#ifndef TONB_CAD2D_BUILD_VERTEX_BUILDER_HXX
#define TONB_CAD2D_BUILD_VERTEX_BUILDER_HXX

#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/vertex.hxx>

namespace tonb::cad2d::build {

    class VertexBuilder {
    public:
        /**
         * @brief Construct a VertexBuilder bound to a shape and tolerance policy.
         * @param shape Target topology shape to create or reuse vertices in.
         * @param tol Tolerance policy used for proximity checks when reusing vertices.
         */
        VertexBuilder(topo::Shape& shape, const topo::Tolerance tol)
            : shape_(shape), tol_(tol) {}

        /**
         * @brief Create a vertex unconditionally.
         * @param p Position in model coordinates.
         * @param vtol Per-vertex tolerance stored on the vertex.
         * @return Result containing the created vertex.
         */
        TNBCAD2D_ND_EXPORT topo::Result<std::shared_ptr<topo::Vertex>> create(const topo::Pnt2d& p, double vtol = 1.e-7);

        /**
         * @brief Create a vertex or reuse one that is already close enough.
         *
         * This performs a linear scan over existing vertices in the shape and returns
         * the first vertex whose position matches @p p within the builder tolerance.
         *
         * @param p Position in mode coordinates.
         * @param vtol Per-vertex tolerance stored on the vertex if a new one is created.
         * @return Result containing the reused or created vertex.
         */
        TNBCAD2D_ND_EXPORT topo::Result<std::shared_ptr<topo::Vertex>> create_or_reuse(const topo::Pnt2d& p, double vtol = 1.e-7);

        /**
         * @brief Access the tolerance policy used by this builder.
         */
        TNB_NODISCARD const topo::Tolerance& tolerance() const noexcept {return tol_;}

    private:
        topo::Shape& shape_;
        topo::Tolerance tol_;
    };
}
#endif //TONB_CAD2D_BUILD_VERTEX_BUILDER_HXX

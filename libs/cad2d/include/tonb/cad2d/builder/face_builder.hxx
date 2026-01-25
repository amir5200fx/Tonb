//
// Created by amir on 1/22/26.
//
/**
 * @file face_builder.hxx
 * @brief Declares FaceBuilder for constructing faces from wires.
 *
 * FaceBuilder creates a Face, assigns its outer and hole wires, performs basic
 * checks, and optionally assigns the face as the left face for boundary edges.
 */
#pragma once
#ifndef TONB_CAD2D_BUILD_FACE_BUILDER_HXX
#define TONB_CAD2D_BUILD_FACE_BUILDER_HXX

#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>

namespace tonb::cad2d::build {

    class FaceBuilder {
    public:

        /**
         * @brief Construct a FaceBuilder bound to a shape and tolerance policy.
         * @param shape Target topology shape.
         * @param tol Tolerance policy used for basic boundary checks.
         */
        FaceBuilder(topo::Shape& shape, topo::Tolerance tol)
            : shape_(shape), tol_(tol) {}

        /**
         * @brief Create a face from an outer wire and optional hole wires.
         *
         * Behaviour:
         * - creates a new Face in the shape
         * - assigns outer and holes
         * - runs Face::check_basic
         * - optionally sets HalfEdge::left_face for all edges in the boundary wires
         *
         * Note: assigning left_face is purely topological. Orientation conventions are
         * not enforced here.
         *
         * @param outer Outer boundary wire.
         * @param holes Hole wires.
         * @param requireClosed If true, requires all wires to be closed.
         * @param setLeftFace If true, assigns left_face on each boundary half-edge.
         * @retuen Result containing the created face.
         */
        TNBCAD2D_ND_EXPORT topo::Result<std::shared_ptr<topo::Face> > create(
            const std::shared_ptr<topo::Wire> &outer, const std::vector<std::shared_ptr<topo::Wire> > &holes = {},
            bool requireClosed = true, bool setLeftFace = true) const;
    private:
        topo::Shape& shape_;
        topo::Tolerance tol_;
    };
}
#endif //TONB_CAD2D_BUILD_FACE_BUILDER_HXX
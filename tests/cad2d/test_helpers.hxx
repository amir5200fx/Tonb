#pragma once
/**
 * @file test_halpers.hxx
 * @brief Shared helper utilities for cad2d unit tests.
 *
 * These helpers build small, deterministic topology arrangements to feed into
 * validators. They deliberately avoid OCCT geometry and rely only on topology
 * and builders.
 *
 * All halper functions are intended for unit test only. Do not include them in
 * production code paths.
 */

#include <memory>
#include <vector>

#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/topo/result.hxx>

#include <tonb/cad2d/builder/vertex_builder.hxx>
#include <tonb/cad2d/builder/halfedge_builder.hxx>
#include <tonb/cad2d/builder/wire_builder.hxx>
#include <tonb/cad2d/builder/face_builder.hxx>

namespace tonb::cad2d::tests {

    /**
     * @brief Bundle of commonly used topology objects for a simple square face.
     *
     * This is a stable fixture-like object returned by build_square_face().
     */
    struct SquareFaceFixture {
        std::shared_ptr<topo::Vertex> v0, v1, v2, v3;
        std::shared_ptr<topo::HalfEdge> e0, e1, e2, e3;
        std::shared_ptr<topo::Wire> outer;
        std::shared_ptr<topo::Face> face;
    };

    inline topo::Result<SquareFaceFixture> build_square_face(topo::Shape& shape, const topo::Tolerance& tol, bool setNextPrev, bool setLeftFace = true) {
        // Builders
        build::VertexBuilder vb(shape, tol);
        build::HalfEdgeBuilder eb(shape);
        build::WireBuilder wb(shape, tol);
        build::FaceBuilder fb(shape, tol);

        SquareFaceFixture fx{};

        // Create vertices (defensive: builders return Result<std::shared_ptr<...>>.
        {
            auto r0 = vb.create({0, 0}, 1.e-7); if (!r0) return topo::Result<SquareFaceFixture>(r0.error()); fx.v0 = std::move(r0.value());
            auto r1 = vb.create({1, 0}, 1.e-7); if (!r1) return topo::Result<SquareFaceFixture>(r1.error()); fx.v1 = std::move(r1.value());
            auto r2 = vb.create({1, 1}, 1.e-7); if (!r2) return topo::Result<SquareFaceFixture>(r2.error()); fx.v2 = std::move(r2.value());
            auto r3 = vb.create({0, 1}, 1.e-7); if (!r3) return topo::Result<SquareFaceFixture>(r3.error()); fx.v3 = std::move(r3.value());
        }

        // Create directed edges in CCW order.
        // curve_id is a placeholder (0). up/uq are placeholders (0..1).
        {
            auto r0 = eb.create(fx.v0, fx.v1, 0, 0.0, 1.0, topo::Orientation::forward, 1.e-9);
            if (!r0) return topo::Result<SquareFaceFixture>(r0.error());
            fx.e0 = std::move(r0.value());

            auto r1 = eb.create(fx.v1, fx.v2, 0, 0.0, 1.0, topo::Orientation::forward, 1.e-9);
            if (!r1) return topo::Result<SquareFaceFixture>(r1.error());
            fx.e1 = std::move(r1.value());

            auto r2 = eb.create(fx.v2, fx.v3, 0, 0.0, 1.0, topo::Orientation::forward, 1.e-9);
            if (!r2) return topo::Result<SquareFaceFixture>(r2.error());
            fx.e2 = std::move(r2.value());

            auto r3 = eb.create(fx.v3, fx.v0, 0, 0.0, 1.0, topo::Orientation::forward, 1.e-9);
            if (!r3) return topo::Result<SquareFaceFixture>(r3.error());
            fx.e3 = std::move(r3.value());
        }

        // Create a closed outer wire.
        {
            auto rw = wb.create({fx.e0, fx.e1, fx.e2, fx.e3}, true, setNextPrev);
            if (!rw) return topo::Result<SquareFaceFixture>(rw.error());
            fx.outer = std::move(rw.value());
        }

        // Create a face using the outer wire.
        {
            auto rf = fb.create(fx.outer, {}, true, setLeftFace);
            if (!rf) return topo::Result<SquareFaceFixture>(rf.error());
            fx.face = std::move(rf.value());
        }
        return topo::ok(std::move(fx));
    }
}
//
// Created by amir on 1/25/26.
//
/**
 * @file validate_face_tests.cxx
 * @brief Unit tests for face validation invariants.
 */

#include <gtest/gtest.h>

#include "test_helpers.hxx"

#include <tonb/cad2d/validate/face_checks.hxx>

#include "tonb/cad2d/topo/face.hxx"
#include "tonb/cad2d/topo/wire.hxx"

namespace tonb::cad2d::tests {
    TEST(Cad2dValidateFace, SquareFacePassesFaceChecks) {
        topo::Shape shape;
        topo::Tolerance tol;

        auto fxr = build_square_face(shape, tol, true, true);
        ASSERT_TRUE(fxr) << fxr.error().message;

        auto r = validate::check_face(fxr.value().face, tol, true);
        EXPECT_TRUE(r) << (r ? "" : r.error().message);
    }

    TEST(Cad2dValidateFace, EdgeOverlapBetweenOuterAndHoleIsCaught) {
        topo::Shape shape;
        topo::Tolerance tol;

        // Outer face is fine.
        auto outerFx = build_square_face(shape, tol, true, true);
        ASSERT_TRUE(outerFx) << outerFx.error().message;

        // Build a second Wire that intentionally reuses and edge from the outer boundary.
        // This is an invalid face boundary configuration adn should be caught by disjointness.
        auto holeWire = shape.make_wire();

        // This assumes Wire has set_boundary that accepts weak_ptr list, and edge_locked works.
        // We reuse e0 and e1 from the outer fixture intentionally.
        std::vector<std::weak_ptr<topo::HalfEdge>> holeEdges;
        holeEdges.emplace_back(outerFx.value().e0);
        holeEdges.emplace_back(outerFx.value().e1);
        holeWire->set_boundary(std::move(holeEdges));

        // Create a face with that hole.
        auto face = shape.make_face();
        face->set_outer((outerFx.value().outer));
        face->set_holes({holeWire});

        auto r = validate::check_face_edge_disjointness(face);
        EXPECT_FALSE(r);
    }
}

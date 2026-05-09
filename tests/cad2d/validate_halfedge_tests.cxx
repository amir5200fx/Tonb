//
// Created by amir on 1/25/26.
//
/**
 * @file validate_halfedge_tests.cxx
 * @brief Unit tests for half-edge validation invariants.
 */

#include "test_helpers.hxx"

#include <tonb/cad2d/validate/halfedge_checks.hxx>

#include <gtest/gtest.h>

namespace tonb::cad2d::tests {
    TEST(Cad2dValidationHalfEdge, SquareEdgesPassHalfEdgeChecks) {
        topo::Shape shape;
        topo::Tolerance tol;

        auto fxr = build_square_face(shape, tol, true, true);
        ASSERT_TRUE(fxr) << fxr.error().message;

        const auto& fx = fxr.value();

        EXPECT_TRUE(validate::check_halfedge(fx.e0));
        EXPECT_TRUE(validate::check_halfedge(fx.e1));
        EXPECT_TRUE(validate::check_halfedge(fx.e2));
        EXPECT_TRUE(validate::check_halfedge(fx.e3));
    }

    TEST(Cad2dValidateHalfEdge, TwinSymmetryViolationIsCaught) {
        topo::Shape shape;
        topo::Tolerance tol;

        // Build two vertices and a twin pair, then deliberately break symmetry.
        build::VertexBuilder vb(shape, tol);
        build::HalfEdgeBuilder eb(shape);

        auto va = vb.create({0, 0}, 1.e-7); ASSERT_TRUE(va) << va.error().message;
        auto vbv = vb.create({1, 0}, 1.e-7); ASSERT_TRUE(vbv) << vbv.error().message;

        auto rp = eb.create_pair(va.value(), vbv.value(), 0, 0,1, 1.e-9);
        ASSERT_TRUE(rp) << rp.error().message;

        auto ab = rp.value().first;
        auto ba = rp.value().second;

        // Break twin symmetry: remove ba's twin link while ab still points to ba.
        // This should be caught by validate::check_twin(ab).
        ba->set_twin(std::shared_ptr<topo::HalfEdge>{});

        auto r = validate::check_twin(ab);
        EXPECT_FALSE(r);
    }
}
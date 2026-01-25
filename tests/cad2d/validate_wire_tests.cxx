//
// Created by amir on 1/25/26.
//
/**
 * @file validate_wire_tests.cxx
 * @brief Unit tests for wire validation invariants.
 */

#include <gtest/gtest.h>

#include <tonb/cad2d/validate/wire_checks.hxx>

#include "test_helpers.hxx"

namespace tonb::cad2d::tests {
    TEST(Cad2dValidateWire, SquareWirePassesWireChecks) {
        topo::Shape shape;
        topo::Tolerance tol;

        auto fxr = build_square_face(shape, tol, true, true);
        ASSERT_TRUE(fxr) << fxr.error().message;

        auto r = validate::check_wire(fxr.value().outer, tol, true, true);
        EXPECT_TRUE(r) << (r ? "" : r.error().message);
    }

    TEST(Cad2dValidateWire, BoundaryOrderMismatchWithNextPrevIsCaught) {
        topo::Shape shape;
        topo::Tolerance tol;

        // Build square with next/prev set.
        auto fxr = build_square_face(shape, tol, true, false);
        ASSERT_TRUE(fxr) << fxr.error().message;

        auto& fx = fxr.value();

        // Deliberately corrupt: set e1->prev to e3 (wrong; should be e0).
        // This should fail the "next/prev matches boundary" check.
        fx.e1->set_prev(fx.e3);

        auto r = validate::check_next_prev_matches_boundary(fx.outer, true, true);
        EXPECT_FALSE(r);
    }

    TEST(Cad2dValidateWire, ContinuityBreakIsCaught) {
        topo::Shape shape;
        topo::Tolerance tol;

        auto fxr = build_square_face(shape, tol, false, false);
        ASSERT_TRUE(fxr) << fxr.error().message;

        auto& fx = fxr.value();

        // Break continuity: make e1 start at v0 instead of v1;
        // This breaks v0->v1? continuity for th chain e0 end (v1) != e1 start (v0).
        fx.e1->set_start(fx.v0);

        auto r = validate::check_continuity(fx.outer, tol, true);
        EXPECT_FALSE(r);
    }
}
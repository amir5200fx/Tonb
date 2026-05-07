//
// Created by amir on 1/25/26.
//
/**
 * @file validate_shape_tests.cxx
 * @brief Unit tests for top-level shape validation.
 */

#include <gtest/gtest.h>

#include "test_helpers.hxx"

#include <tonb/cad2d/validate/shape_checks.hxx>

namespace tonb::cad2d::tests {

    TEST(Cad2dValidateShape, SquareFacePassesShapeChecks)
    {
        topo::Shape shape;
        topo::Tolerance tol;

        auto fxr = build_square_face(shape, tol, /*setNextPrev=*/true, /*setLeftFace=*/true);
        ASSERT_TRUE(fxr) << fxr.error().message;

        validate::ShapeCheckOptions opt{};
        opt.require_closed_wires = true;

        auto r = validate::check_shape(shape, tol, opt);
        EXPECT_TRUE(r) << (r ? "" : r.error().message);
    }

    TEST(Cad2dValidateShape, CanValidatePartialShapeWithoutFaces)
    {
        topo::Shape shape;
        topo::Tolerance tol;

        // Build just a wire and edges, do not add a face.
        auto fxr = build_square_face(shape, tol, /*setNextPrev=*/true, /*setLeftFace=*/false);
        ASSERT_TRUE(fxr) << fxr.error().message;

        // Remove faces from shape if your helper created one; alternatively, build wire only.
        // If Shape owns faces in a registry and does not provide removal yet, then:
        // - set check_faces=false (stage validation).
        validate::ShapeCheckOptions opt{};
        opt.check_faces = false;
        opt.require_closed_wires = true;

        auto r = validate::check_shape(shape, tol, opt);
        EXPECT_TRUE(r) << (r ? "" : r.error().message);
    }

} // namespace tonb::cad2d::tests
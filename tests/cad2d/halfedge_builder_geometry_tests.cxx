//
// Created by amir on 1/25/26.
//
/**
 * @file halfedge_builder_geometry_tests.cxx
 * @brief Tests geometry-aware HalfEdgeBuilder overloads.
 */

#include <gtest/gtest.h>

#include <tonb/cad2d/tools.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/builder/halfedge_builder.hxx>
#include <tonb/cad2d/topo/shape.hxx>

namespace tonb::cad2d::tests {

    TEST(Cad2dBuild, HalfEdgeCreateFromCurveBindsCurveId) {
        topo::Shape shape;
        build::HalfEdgeBuilder b(shape);
        geom::CurveStore store;

        const auto v0 = shape.make_vertex({0, 0});
        const auto v1 = shape.make_vertex({1, 0});
        ASSERT_TRUE(v0);
        ASSERT_TRUE(v1);

        const Curve c = Tools::make_segment({0, 0}, {1, 0});
        ASSERT_TRUE(c.is_valid());

        const auto rng= c.parameter_range();
        ASSERT_TRUE(rng.has_value());
        const real u0 = rng->first;
        const real u1 = rng->second;

        const auto r = b.create_from_curve(store, c, v0, v1, u0, u1, topo::Orientation::forward);
        ASSERT_TRUE(r) << r.error().message;

        const auto& he = r.value();
        ASSERT_TRUE(he);
        EXPECT_NE(he->curve_id(), 0u);
        EXPECT_TRUE(store.contains(he->curve_id()));
    }

    TEST(Cad2dBuild, HalfEdgeCreateFromCurveRejectsWrongOrientationOrdering)
    {
        topo::Shape shape;
        build::HalfEdgeBuilder b(shape);
        geom::CurveStore store;

        const auto v0 = shape.make_vertex({0.0, 0.0});
        const auto v1 = shape.make_vertex({1.0, 0.0});

        const cad2d::Curve c = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
        const auto rng = c.parameter_range();
        ASSERT_TRUE(rng.has_value());

        // Intentionally violate ordering: forward but u0>u1.
        const double u0 = rng->second;
        const double u1 = rng->first;

        auto r = b.create_from_curve(store, c, v0, v1, u0, u1, topo::Orientation::forward);
        ASSERT_FALSE(r);
        EXPECT_EQ(r.error().code, topo::ErrorCode::invalid_input);
    }

    TEST(Cad2dBuild, HalfEdgeCreatePairFromCurveCreatesTwinPair)
    {
        topo::Shape shape;
        build::HalfEdgeBuilder b(shape);
        geom::CurveStore store;

        const auto a = shape.make_vertex({0.0, 0.0});
        const auto bV = shape.make_vertex({1.0, 0.0});

        const cad2d::Curve c = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
        const auto rng = c.parameter_range();
        ASSERT_TRUE(rng.has_value());

        auto r = b.create_pair_from_curve(store, c, a, bV, rng->first, rng->second);
        ASSERT_TRUE(r) << r.error().message;

        auto ab = r.value().first;
        auto ba = r.value().second;

        ASSERT_TRUE(ab);
        ASSERT_TRUE(ba);

        EXPECT_TRUE(ab->twin());
        EXPECT_TRUE(ba->twin());
        EXPECT_EQ(ab->twin()->id(), ba->id());
        EXPECT_EQ(ba->twin()->id(), ab->id());

        EXPECT_EQ(ab->curve_id(), ba->curve_id());
        EXPECT_TRUE(store.contains(ab->curve_id()));
    }
}
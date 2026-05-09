/**
* @file edge_builder_tests.cxx
 * @brief Tests first-class topo::Edge construction.
 */
#include <gtest/gtest.h>

#include <tonb/config.hxx>
#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/edge.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/builder/halfedge_builder.hxx>
#include <tonb/cad2d/validate/edge_checks.hxx>
#include <tonb/cad2d/tools.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>

namespace tonb::cad2d::tests {

    TEST(Cad2dBuild, EdgeCreateFromCurveCreatesTwinOwnedPair)
    {
#if !defined(TONB_WITH_OCCT)
        GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping edge builder tests.";
#else
        topo::Shape shape;
        build::HalfEdgeBuilder hb(shape);
        geom::CurveStore store;

        auto a = shape.make_vertex({0.0, 0.0});
        auto b = shape.make_vertex({1.0, 0.0});
        ASSERT_TRUE(a);
        ASSERT_TRUE(b);

        const cad2d::Curve c = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
        ASSERT_TRUE(c.is_valid());
        const auto rng = c.parameter_range();
        ASSERT_TRUE(rng.has_value());

        auto edge = hb.create_edge_from_curve(store, c, a, b, rng->first, rng->second);
        ASSERT_TRUE(edge) << edge.error().message;

        const auto fwd = edge.value()->forward();
        const auto rev = edge.value()->reverse();
        ASSERT_TRUE(fwd);
        ASSERT_TRUE(rev);
        EXPECT_EQ(fwd->twin()->id(), rev->id());
        EXPECT_EQ(rev->twin()->id(), fwd->id());
        ASSERT_TRUE(fwd->edge());
        ASSERT_TRUE(rev->edge());
        EXPECT_EQ(fwd->edge()->id(), edge.value()->id());
        EXPECT_EQ(rev->edge()->id(), edge.value()->id());

        auto vr = validate::check_edge(edge.value());
        ASSERT_TRUE(vr) << vr.error().message;
#endif
    }

} // namespace tonb::cad2d::tests

/**
* @file edge_validation_tests.cxx
 * @brief Tests validation of topo::Edge invariants.
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

    TEST(Cad2dValidateEdge, BreakingTwinFailsEdgeValidation)
    {
#if !defined(TONB_WITH_OCCT)
        GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping edge validation tests.";
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
        ASSERT_TRUE(fwd);
        fwd->set_twin(std::weak_ptr<topo::HalfEdge>{});

        const auto vr = validate::check_edge(edge.value());
        ASSERT_FALSE(vr);
        EXPECT_EQ(vr.error().code, topo::ErrorCode::topology_error);
        EXPECT_NE(vr.error().message.find("EdgeChecks"), std::string::npos);
#endif
    }

} // namespace tonb::cad2d::tests

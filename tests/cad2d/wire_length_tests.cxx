
/**
 * @file wire_length_tests.cxx
 * @brief Unit tests for cad2d wire-length utilities.
 */
#include <gtest/gtest.h>

#include <tonb/config.hxx>
#include <tonb/cad2d/algo/wire_length.hxx>
#include <tonb/cad2d/tools.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/builder/halfedge_builder.hxx>
#include <tonb/cad2d/builder/wire_builder.hxx>
#include <tonb/cad2d/topo/shape.hxx>

namespace tonb::cad2d::tests {

TEST(Cad2dAlgo, SquareSegmentWireLengthIsFour)
{
#if !TONB_WITH_OCCT
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping wire-length geometry tests.";
#else
    topo::Shape shape;
    geom::CurveStore store;
    build::HalfEdgeBuilder edge_builder(shape);
    build::WireBuilder wire_builder(shape, {});

    auto v0 = shape.make_vertex({0.0, 0.0});
    auto v1 = shape.make_vertex({1.0, 0.0});
    auto v2 = shape.make_vertex({1.0, 1.0});
    auto v3 = shape.make_vertex({0.0, 1.0});

    ASSERT_TRUE(v0);
    ASSERT_TRUE(v1);
    ASSERT_TRUE(v2);
    ASSERT_TRUE(v3);

    const auto c01 = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
    const auto c12 = cad2d::Tools::make_segment({1.0, 0.0}, {1.0, 1.0});
    const auto c23 = cad2d::Tools::make_segment({1.0, 1.0}, {0.0, 1.0});
    const auto c30 = cad2d::Tools::make_segment({0.0, 1.0}, {0.0, 0.0});

    ASSERT_TRUE(c01.is_valid());
    ASSERT_TRUE(c12.is_valid());
    ASSERT_TRUE(c23.is_valid());
    ASSERT_TRUE(c30.is_valid());

    const auto r01 = c01.parameter_range();
    const auto r12 = c12.parameter_range();
    const auto r23 = c23.parameter_range();
    const auto r30 = c30.parameter_range();

    ASSERT_TRUE(r01.has_value());
    ASSERT_TRUE(r12.has_value());
    ASSERT_TRUE(r23.has_value());
    ASSERT_TRUE(r30.has_value());

    auto e01 = edge_builder.create_from_curve(store, c01, v0, v1, r01->first, r01->second, topo::Orientation::forward);
    auto e12 = edge_builder.create_from_curve(store, c12, v1, v2, r12->first, r12->second, topo::Orientation::forward);
    auto e23 = edge_builder.create_from_curve(store, c23, v2, v3, r23->first, r23->second, topo::Orientation::forward);
    auto e30 = edge_builder.create_from_curve(store, c30, v3, v0, r30->first, r30->second, topo::Orientation::forward);

    ASSERT_TRUE(e01) << e01.error().message;
    ASSERT_TRUE(e12) << e12.error().message;
    ASSERT_TRUE(e23) << e23.error().message;
    ASSERT_TRUE(e30) << e30.error().message;

    auto w = wire_builder.create({e01.value(), e12.value(), e23.value(), e30.value()});
    ASSERT_TRUE(w) << w.error().message;

    algo::WireLengthOptions options;
    options.integration.atol = 1.0e-10;
    options.integration.rtol = 1.0e-10;
    options.integration.max_depth = 16;
    options.integration.max_evals = 1 << 14; // 2 ^ 14

    auto L = algo::wire_length(w.value(), store, options);
    ASSERT_TRUE(L) << L.error().message;
    EXPECT_NEAR(L.value(), 4.0, 1.0e-8);
#endif
}

} // namespace tonb::cad2d::tests

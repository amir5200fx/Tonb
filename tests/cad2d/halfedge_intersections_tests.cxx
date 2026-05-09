/**
 * @file halfedge_intersections_tests.cxx
 * @brief Tests for topology-level half-edge span intersection queries.
 */
#include <gtest/gtest.h>

#include <tonb/config.hxx>
#include <tonb/cad2d/algo/halfedge_intersection.hxx>
#include <tonb/cad2d/builder/halfedge_builder.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/tools.hxx>
#include <tonb/cad2d/topo/shape.hxx>

namespace tonb::cad2d::tests {

TEST(Cad2dAlgo, CrossingHalfEdgesReturnCorrectIntersection)
{
#if !TONB_WITH_OCCT
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping half-edge intersection tests.";
#else
    topo::Shape shape;
    build::HalfEdgeBuilder hb(shape);
    geom::CurveStore store;

    const auto a0 = shape.make_vertex({-1.0, 0.0});
    const auto a1 = shape.make_vertex({ 1.0, 0.0});
    const auto b0 = shape.make_vertex({ 0.0,-1.0});
    const auto b1 = shape.make_vertex({ 0.0, 1.0});
    ASSERT_TRUE(a0 && a1 && b0 && b1);

    const auto ca = Tools::make_segment(Point{-1.0, 0.0}, Point{1.0, 0.0});
    const auto cb = Tools::make_segment(Point{0.0, -1.0}, Point{0.0, 1.0});
    const auto ra = ca.parameter_range();
    const auto rb = cb.parameter_range();
    ASSERT_TRUE(ra.has_value());
    ASSERT_TRUE(rb.has_value());

    const auto hea = hb.create_from_curve(store, ca, a0, a1, ra->first, ra->second, topo::Orientation::forward);
    const auto heb = hb.create_from_curve(store, cb, b0, b1, rb->first, rb->second, topo::Orientation::forward);
    ASSERT_TRUE(hea) << hea.error().message;
    ASSERT_TRUE(heb) << heb.error().message;

    const auto r = algo::intersect_halfedge_spans(hea.value(), heb.value(), store);
    ASSERT_TRUE(r) << r.error().message;
    ASSERT_TRUE(r.value().ok());
    ASSERT_EQ(r.value().point_count(), 1u);
    ASSERT_EQ(r.value().overlap_count(), 0u);
    ASSERT_EQ(r.value().items.size(), 1u);
    ASSERT_TRUE(std::holds_alternative<algo::HalfEdgeIntersectionPoint>(r.value().items.front()));

    const auto& ip = std::get<algo::HalfEdgeIntersectionPoint>(r.value().items.front());
    EXPECT_EQ(ip.first_halfedge_id, hea.value()->id());
    EXPECT_EQ(ip.second_halfedge_id, heb.value()->id());
    EXPECT_NEAR(ip.point.x(), 0.0, 1.0e-10);
    EXPECT_NEAR(ip.point.y(), 0.0, 1.0e-10);
#endif
}

TEST(Cad2dAlgo, InvalidCurveIdFailsCleanly)
{
    topo::Shape shape;
    build::HalfEdgeBuilder hb(shape);
    geom::CurveStore store;

    const auto a0 = shape.make_vertex({0.0, 0.0});
    const auto a1 = shape.make_vertex({1.0, 0.0});
    const auto b0 = shape.make_vertex({0.0, 1.0});
    const auto b1 = shape.make_vertex({1.0, 1.0});
    ASSERT_TRUE(a0 && a1 && b0 && b1);

    const auto hea = hb.create(a0, a1, 0, 0.0, 1.0, topo::Orientation::forward);
    const auto heb = hb.create(b0, b1, 0, 0.0, 1.0, topo::Orientation::forward);
    ASSERT_TRUE(hea) << hea.error().message;
    ASSERT_TRUE(heb) << heb.error().message;

    const auto r = algo::intersect_halfedge_spans(hea.value(), heb.value(), store);
    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, topo::ErrorCode::geometry_error);
}

TEST(Cad2dAlgo, SameGeometryWithDisjointParameterSpansReturnsNoIntersection)
{
#if !TONB_WITH_OCCT
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping half-edge intersection tests.";
#else
    topo::Shape shape;
    build::HalfEdgeBuilder hb(shape);
    geom::CurveStore store;

    const auto v0 = shape.make_vertex({0.0, 0.0});
    const auto v1 = shape.make_vertex({1.0, 0.0});
    const auto v2 = shape.make_vertex({2.0, 0.0});
    const auto v3 = shape.make_vertex({3.0, 0.0});
    ASSERT_TRUE(v0 && v1 && v2 && v3);

    const auto c = Tools::make_segment(Point{0.0, 0.0}, Point{3.0, 0.0});
    const auto range = c.parameter_range();
    ASSERT_TRUE(range.has_value());
    const auto curve_id = store.add(c);

    const auto h0 = hb.create(v0, v1, curve_id, range->first, range->first + (range->second - range->first) / 3.0, topo::Orientation::forward);
    const auto h1 = hb.create(v2, v3, curve_id, range->first + 2.0 * (range->second - range->first) / 3.0, range->second, topo::Orientation::forward);
    ASSERT_TRUE(h0) << h0.error().message;
    ASSERT_TRUE(h1) << h1.error().message;

    const auto r = algo::intersect_halfedge_spans(h0.value(), h1.value(), store);
    ASSERT_TRUE(r) << r.error().message;
    ASSERT_TRUE(r.value().ok());
    EXPECT_TRUE(r.value().empty());
    EXPECT_EQ(r.value().point_count(), 0u);
    EXPECT_EQ(r.value().overlap_count(), 0u);
#endif
}

} // namespace tonb::cad2d::tests

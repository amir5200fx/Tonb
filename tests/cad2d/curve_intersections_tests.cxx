//
// Created by amir on 5/7/26.
//
/**
 * @file curve_intersections_tests.cxx
 * @brief Tests for bounded 2D curve-span intersection queries.
 */
#include <gtest/gtest.h>

#include <tonb/config.hxx>
#include <tonb/cad2d/tools.hxx>
#include <tonb/cad2d/geom/intersection.hxx>
#include <tonb/cad2d/geom/intersection_result.hxx>

#include <cmath>

namespace tonb::cad2d::tests {

TEST(Cad2dGeom, OrthogonalSegmentsIntersectCorrectly)
{
#if !TONB_WITH_OCCT
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping curve intersection tests.";
#else
    const auto a = cad2d::Tools::make_segment(Point{-1.0, 0.0}, Point{1.0, 0.0});
    const auto b = cad2d::Tools::make_segment(Point{0.0, -1.0}, Point{0.0, 1.0});

    const auto ra = a.parameter_range();
    const auto rb = b.parameter_range();
    ASSERT_TRUE(ra.has_value());
    ASSERT_TRUE(rb.has_value());

    const auto r = geom::intersect_bounded_spans(a, ra->first, ra->second, b, rb->first, rb->second);
    ASSERT_TRUE(r) << r.error().message;
    ASSERT_TRUE(r.value().ok());
    ASSERT_EQ(r.value().point_count(), 1u);
    ASSERT_EQ(r.value().overlap_count(), 0u);

    ASSERT_EQ(r.value().items.size(), 1u);
    ASSERT_TRUE(std::holds_alternative<geom::IntersectionPoint>(r.value().items.front()));
    const auto& ip = std::get<geom::IntersectionPoint>(r.value().items.front());
    EXPECT_NEAR(ip.point.x(), 0.0, 1.0e-10);
    EXPECT_NEAR(ip.point.y(), 0.0, 1.0e-10);
    EXPECT_EQ(ip.kind, geom::IntersectionPointKind::simple);
#endif
}

TEST(Cad2dGeom, CollinearSeparatedSegmentsReturnNoPointIntersection)
{
#if !TONB_WITH_OCCT
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping curve intersection tests.";
#else
    const auto a = cad2d::Tools::make_segment(Point{0.0, 0.0}, Point{1.0, 0.0});
    const auto b = cad2d::Tools::make_segment(Point{2.0, 0.0}, Point{3.0, 0.0});

    const auto ra = a.parameter_range();
    const auto rb = b.parameter_range();
    ASSERT_TRUE(ra.has_value());
    ASSERT_TRUE(rb.has_value());

    const auto r = geom::intersect_bounded_spans(a, ra->first, ra->second, b, rb->first, rb->second);
    ASSERT_TRUE(r) << r.error().message;
    EXPECT_TRUE(r.value().ok());
    EXPECT_TRUE(r.value().empty());
    EXPECT_EQ(r.value().point_count(), 0u);
    EXPECT_EQ(r.value().overlap_count(), 0u);
#endif
}

TEST(Cad2dGeom, SegmentArcRepresentativeCasePasses)
{
#if !TONB_WITH_OCCT
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping curve intersection tests.";
#else
    const auto seg = cad2d::Tools::make_segment(Point{-2.0, 0.0}, Point{2.0, 0.0});
    const auto arc = cad2d::Tools::make_circle_arc(Point{-1.0, 0.0}, Point{0.0, 1.0}, Point{1.0, 0.0});

    const auto rs = seg.parameter_range();
    const auto ra = arc.parameter_range();
    ASSERT_TRUE(rs.has_value());
    ASSERT_TRUE(ra.has_value());

    const auto r = geom::intersect_bounded_spans(seg, rs->first, rs->second, arc, ra->first, ra->second);
    ASSERT_TRUE(r) << r.error().message;
    ASSERT_TRUE(r.value().ok());
    ASSERT_EQ(r.value().point_count(), 2u);
    ASSERT_EQ(r.value().overlap_count(), 0u);

    const auto& p0 = std::get<geom::IntersectionPoint>(r.value().items[0]);
    const auto& p1 = std::get<geom::IntersectionPoint>(r.value().items[1]);
    EXPECT_NEAR(p0.point.y(), 0.0, 1.0e-10);
    EXPECT_NEAR(p1.point.y(), 0.0, 1.0e-10);
#endif
}

TEST(Cad2dGeom, ArcArcRepresentativeCasePasses)
{
#if !TONB_WITH_OCCT
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping curve intersection tests.";
#else
    const auto a = cad2d::Tools::make_circle_arc(Point{-1.0, 0.0}, Point{0.0, 1.0}, Point{1.0, 0.0});
    const auto b = cad2d::Tools::make_circle_arc(Point{0.0, 0.0}, Point{1.0, 1.0}, Point{2.0, 0.0});

    const auto ra = a.parameter_range();
    const auto rb = b.parameter_range();
    ASSERT_TRUE(ra.has_value());
    ASSERT_TRUE(rb.has_value());

    const auto r = geom::intersect_bounded_spans(a, ra->first, ra->second, b, rb->first, rb->second);
    ASSERT_TRUE(r) << r.error().message;
    ASSERT_TRUE(r.value().ok());
    ASSERT_EQ(r.value().point_count(), 1u);
    ASSERT_EQ(r.value().overlap_count(), 0u);

    const auto& ip = std::get<geom::IntersectionPoint>(r.value().items.front());
    EXPECT_NEAR(ip.point.x(), 0.5, 1.0e-8);
    EXPECT_NEAR(ip.point.y(), std::sqrt(3.0) / 2.0, 1.0e-8);
#endif
}

} // namespace tonb::cad2d::tests

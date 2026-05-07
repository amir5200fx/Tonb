//
// Created by amir on 5/7/26.
//
/**
 * @file intersection_result_tests.cxx
 * @brief Tests for the public 2D intersection result model.
 *
 * These tests intentionally validate the public result types themselves rather
 * than any specific geometry-kernel intersection implementation. The goal of
 * Issue 8 is to establish a stable public result model that can already
 * distinguish:
 * - isolated point intersections,
 * - no-intersection successful queries,
 * - coincident overlap intervals,
 * - unsupported/failure diagnostics.
 */
#include <gtest/gtest.h>

#include <tonb/cad2d/geom/intersection_result.hxx>

namespace tonb::cad2d::tests {

TEST(Cad2dGeomIntersectionResult, LineLineCrossingCanBeRepresentedAsOnePoint)
{
    const auto report = geom::make_point_intersection(
        Point{0.5, 0.5},
        0.5,
        0.5,
        geom::CurveIntersectionPointKind::simple);

    ASSERT_TRUE(report.ok());
    ASSERT_FALSE(report.empty());
    EXPECT_EQ(report.point_count(), 1u);
    EXPECT_EQ(report.overlap_count(), 0u);
    ASSERT_EQ(report.items.size(), 1u);

    ASSERT_TRUE(std::holds_alternative<geom::CurveIntersectionPoint>(report.items.front()));
    const auto& item = std::get<geom::CurveIntersectionPoint>(report.items.front());

    EXPECT_DOUBLE_EQ(item.point.x(), 0.5);
    EXPECT_DOUBLE_EQ(item.point.y(), 0.5);
    EXPECT_DOUBLE_EQ(item.u_on_first, 0.5);
    EXPECT_DOUBLE_EQ(item.u_on_second, 0.5);
    EXPECT_EQ(item.kind, geom::CurveIntersectionPointKind::simple);
}

TEST(Cad2dGeomIntersectionResult, DisjointLineLineCanBeRepresentedAsEmptySuccess)
{
    const auto report = geom::make_no_intersections();

    ASSERT_TRUE(report.ok());
    EXPECT_TRUE(report.empty());
    EXPECT_EQ(report.point_count(), 0u);
    EXPECT_EQ(report.overlap_count(), 0u);
    EXPECT_TRUE(report.diagnostic.empty());
}

TEST(Cad2dGeomIntersectionResult, CoincidentOverlapCanBeRepresentedWithoutAmbiguousPoints)
{
    const auto report = geom::make_overlap_intersection(
        Point{1.0, 0.0},
        Point{2.0, 0.0},
        1.0,
        2.0,
        0.0,
        1.0);

    ASSERT_TRUE(report.ok());
    ASSERT_FALSE(report.empty());
    EXPECT_EQ(report.point_count(), 0u);
    EXPECT_EQ(report.overlap_count(), 1u);
    EXPECT_TRUE(report.has_overlap());
    ASSERT_EQ(report.items.size(), 1u);

    ASSERT_TRUE(std::holds_alternative<geom::CurveIntersectionOverlap>(report.items.front()));
    const auto& item = std::get<geom::CurveIntersectionOverlap>(report.items.front());

    EXPECT_DOUBLE_EQ(item.first_point.x(), 1.0);
    EXPECT_DOUBLE_EQ(item.first_point.y(), 0.0);
    EXPECT_DOUBLE_EQ(item.last_point.x(), 2.0);
    EXPECT_DOUBLE_EQ(item.last_point.y(), 0.0);
    EXPECT_DOUBLE_EQ(item.first_u0, 1.0);
    EXPECT_DOUBLE_EQ(item.first_u1, 2.0);
    EXPECT_DOUBLE_EQ(item.second_u0, 0.0);
    EXPECT_DOUBLE_EQ(item.second_u1, 1.0);
}

TEST(Cad2dGeomIntersectionResult, TangentPointKindIsDistinguishedExplicitly)
{
    const auto report = geom::make_point_intersection(
        Point{1.0, 1.0},
        2.0,
        3.0,
        geom::CurveIntersectionPointKind::tangent);

    ASSERT_TRUE(report.ok());
    ASSERT_EQ(report.items.size(), 1u);
    ASSERT_TRUE(std::holds_alternative<geom::CurveIntersectionPoint>(report.items.front()));

    const auto& item = std::get<geom::CurveIntersectionPoint>(report.items.front());
    EXPECT_EQ(item.kind, geom::CurveIntersectionPointKind::tangent);
}

TEST(Cad2dGeomIntersectionResult, UnsupportedAndFailureDiagnosticsAreExplicit)
{
    const auto unsupported = geom::make_unsupported_intersection(
        "CurveIntersection: curve combination is not supported");
    ASSERT_FALSE(unsupported.ok());
    EXPECT_EQ(unsupported.status, geom::CurveIntersectionStatus::unsupported);
    EXPECT_EQ(unsupported.items.size(), 0u);
    EXPECT_EQ(unsupported.diagnostic, "CurveIntersection: curve combination is not supported");

    const auto failure = geom::make_failed_intersection(
        "CurveIntersection: kernel evaluation failed");
    ASSERT_FALSE(failure.ok());
    EXPECT_EQ(failure.status, geom::CurveIntersectionStatus::failure);
    EXPECT_EQ(failure.items.size(), 0u);
    EXPECT_EQ(failure.diagnostic, "CurveIntersection: kernel evaluation failed");
}

} // namespace tonb::cad2d::tests

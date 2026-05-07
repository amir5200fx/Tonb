/**
 * @file halfedge_geometry_validation_tests.cxx
 * @brief Tests for geometry-aware half-edge validation.
 *
 * This test unit covers:
 * - valid geometry-bound half-edge validation,
 * - endpoint mismatch detection,
 * - missing curve detection,
 * - out-of-domain parameter detection,
 * - diagnostic convention checks for Issue 4.
 */
#include <gtest/gtest.h>

#define TONB_WITH_OCCT
#include <tonb/cad2d/tools.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/validate/halfedge_geometry.hxx>
#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/builder/halfedge_builder.hxx>

namespace tonb::cad2d::tests {

TEST(Cad2dValidate, HalfEdgeGeometryValidEdgePasses)
{
#if !defined(TONB_WITH_OCCT)
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping geometry validation tests.";
#else
    topo::Shape shape;
    build::HalfEdgeBuilder hb(shape);
    geom::CurveStore store;

    auto v0 = shape.make_vertex({0.0, 0.0});
    auto v1 = shape.make_vertex({1.0, 0.0});
    ASSERT_TRUE(v0);
    ASSERT_TRUE(v1);

    const cad2d::Curve c = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
    ASSERT_TRUE(c.is_valid());

    const auto rng = c.parameter_range();
    ASSERT_TRUE(rng.has_value());

    auto e = hb.create_from_curve(
        store, c, v0, v1, rng->first, rng->second, topo::Orientation::forward);
    ASSERT_TRUE(e) << e.error().message;

    topo::Tolerance tol;
    auto r = validate::check_halfedge_geometry(e.value(), store, tol);
    ASSERT_TRUE(r) << r.error().message;
#endif
}

TEST(Cad2dValidate, HalfEdgeGeometryEndpointMismatchFails)
{
#if !defined(TONB_WITH_OCCT)
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping geometry validation tests.";
#else
    topo::Shape shape;
    build::HalfEdgeBuilder hb(shape);
    geom::CurveStore store;

    auto v0 = shape.make_vertex({0.0, 0.0});
    auto v1 = shape.make_vertex({2.0, 0.0}); // intentionally wrong end point
    ASSERT_TRUE(v0);
    ASSERT_TRUE(v1);

    const cad2d::Curve c = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
    ASSERT_TRUE(c.is_valid());

    const auto rng = c.parameter_range();
    ASSERT_TRUE(rng.has_value());

    auto e = hb.create_from_curve(
        store, c, v0, v1, rng->first, rng->second, topo::Orientation::forward);
    ASSERT_TRUE(e) << e.error().message;

    topo::Tolerance tol;
    auto r = validate::check_halfedge_geometry(e.value(), store, tol);

    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, topo::ErrorCode::geometry_error);
    EXPECT_NE(r.error().message.find("HalfEdgeGeometry"), std::string::npos);
    EXPECT_NE(r.error().message.find("does not match the end vertex"), std::string::npos);
#endif
}

TEST(Cad2dValidate, HalfEdgeGeometryMissingCurveFails)
{
#if !defined(TONB_WITH_OCCT)
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping geometry validation tests.";
#else
    topo::Shape shape;
    build::HalfEdgeBuilder hb(shape);
    geom::CurveStore store;

    auto v0 = shape.make_vertex({0.0, 0.0});
    auto v1 = shape.make_vertex({1.0, 0.0});
    ASSERT_TRUE(v0);
    ASSERT_TRUE(v1);

    const cad2d::Curve c = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
    ASSERT_TRUE(c.is_valid());

    const auto rng = c.parameter_range();
    ASSERT_TRUE(rng.has_value());

    auto e = hb.create_from_curve(
        store, c, v0, v1, rng->first, rng->second, topo::Orientation::forward);
    ASSERT_TRUE(e) << e.error().message;

    EXPECT_TRUE(store.remove(e.value()->curve_id()));

    topo::Tolerance tol;
    auto r = validate::check_halfedge_geometry(e.value(), store, tol);

    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, topo::ErrorCode::geometry_error);
    EXPECT_NE(r.error().message.find("HalfEdgeGeometry"), std::string::npos);
    EXPECT_NE(r.error().message.find("is not present in CurveStore"), std::string::npos);
#endif
}

TEST(Cad2dValidate, HalfEdgeGeometryOutOfDomainFails)
{
#if !defined(TONB_WITH_OCCT)
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping geometry validation tests.";
#else
    topo::Shape shape;
    geom::CurveStore store;

    auto v0 = shape.make_vertex({0.0, 0.0});
    auto v1 = shape.make_vertex({1.0, 0.0});
    ASSERT_TRUE(v0);
    ASSERT_TRUE(v1);

    const cad2d::Curve c = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
    ASSERT_TRUE(c.is_valid());

    const auto curve_id = store.add(c);
    ASSERT_NE(curve_id, 0u);

    const auto rng = c.parameter_range();
    ASSERT_TRUE(rng.has_value());

    const auto umin = rng->first;
    const auto umax = rng->second;
    const auto span = umax - umin;

    auto e = std::make_shared<topo::HalfEdge>(
        1001,
        curve_id,
        umin - span,
        umax + span,
        topo::Orientation::forward);

    e->set_start(v0);
    e->set_end(v1);

    topo::Tolerance tol;
    auto r = validate::check_halfedge_geometry(e, store, tol);

    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, topo::ErrorCode::geometry_error);
    EXPECT_NE(r.error().message.find("HalfEdgeGeometry"), std::string::npos);
    EXPECT_NE(r.error().message.find("outside the curve domain"), std::string::npos);
#endif
}

TEST(Cad2dValidate, HalfEdgeGeometryDegenerateSpanFails)
{
#if !defined(TONB_WITH_OCCT)
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping geometry validation tests.";
#else
    topo::Shape shape;
    geom::CurveStore store;

    auto v0 = shape.make_vertex({0.0, 0.0});
    auto v1 = shape.make_vertex({1.0, 0.0});
    ASSERT_TRUE(v0);
    ASSERT_TRUE(v1);

    const cad2d::Curve c = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
    ASSERT_TRUE(c.is_valid());

    const auto curve_id = store.add(c);
    ASSERT_NE(curve_id, 0u);

    const auto rng = c.parameter_range();
    ASSERT_TRUE(rng.has_value());

    const auto u = 0.5 * (rng->first + rng->second);

    auto e = std::make_shared<topo::HalfEdge>(
        1002,
        curve_id,
        u,
        u,
        topo::Orientation::forward);

    e->set_start(v0);
    e->set_end(v1);

    topo::Tolerance tol;
    auto r = validate::check_halfedge_geometry(e, store, tol);

    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, topo::ErrorCode::degenerate);
    EXPECT_NE(r.error().message.find("HalfEdgeGeometry"), std::string::npos);
#endif
}

TEST(Cad2dValidate, HalfEdgeGeometryOrientationMismatchFails)
{
#if !defined(TONB_WITH_OCCT)
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping geometry validation tests.";
#else
    topo::Shape shape;
    geom::CurveStore store;

    auto v0 = shape.make_vertex({0.0, 0.0});
    auto v1 = shape.make_vertex({1.0, 0.0});
    ASSERT_TRUE(v0);
    ASSERT_TRUE(v1);

    const cad2d::Curve c = cad2d::Tools::make_segment({0.0, 0.0}, {1.0, 0.0});
    ASSERT_TRUE(c.is_valid());

    const auto curve_id = store.add(c);
    ASSERT_NE(curve_id, 0u);

    const auto rng = c.parameter_range();
    ASSERT_TRUE(rng.has_value());

    auto e = std::make_shared<topo::HalfEdge>(
        1003,
        curve_id,
        rng->second,
        rng->first,
        topo::Orientation::forward); // wrong ordering for forward

    e->set_start(v0);
    e->set_end(v1);

    topo::Tolerance tol;
    auto r = validate::check_halfedge_geometry(e, store, tol);

    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, topo::ErrorCode::geometry_error);
    EXPECT_NE(r.error().message.find("HalfEdgeGeometry"), std::string::npos);
#endif
}

} // namespace tonb::cad2d::tests
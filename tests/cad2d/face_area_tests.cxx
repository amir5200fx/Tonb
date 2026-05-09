//
// Created by amir on 5/7/26.
//
/**
 * @file face_area_tests.cxx
 * @brief Unit tests for polygonal face-area and orientation utilities.
 */
#include <gtest/gtest.h>

#include <tonb/config.hxx>
#include <tonb/cad2d/algo/face_area.hxx>
#include <tonb/cad2d/tools.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/builder/halfedge_builder.hxx>
#include <tonb/cad2d/builder/wire_builder.hxx>
#include <tonb/cad2d/builder/face_builder.hxx>
#include <tonb/cad2d/topo/shape.hxx>

namespace tonb::cad2d::tests {

TEST(Cad2dAlgo, SquareFaceSignedAreaIsOne)
{
#if !TONB_WITH_OCCT
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping face-area geometry tests.";
#else
    topo::Shape shape;
    geom::CurveStore store;
    build::HalfEdgeBuilder edge_builder(shape);
    build::WireBuilder wire_builder(shape, topo::Tolerance{});
    build::FaceBuilder face_builder(shape, topo::Tolerance{});

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

    auto outer = wire_builder.create({e01.value(), e12.value(), e23.value(), e30.value()}, true, true);
    ASSERT_TRUE(outer) << outer.error().message;

    auto face = face_builder.create(outer.value());
    ASSERT_TRUE(face) << face.error().message;

    algo::FaceAreaOptions options;
    options.linearity_tolerance = 1.0e-10;
    options.area_epsilon = 1.0e-12;

    const auto area = algo::signed_area_of_face_polygon(face.value(), store, options);
    ASSERT_TRUE(area) << area.error().message;
    EXPECT_NEAR(area.value(), 1.0, 1.0e-10);

    const auto orient = algo::face_has_standard_orientation(face.value(), store, options);
    ASSERT_TRUE(orient) << orient.error().message;
    EXPECT_TRUE(orient.value());
#endif
}

TEST(Cad2dAlgo, FaceHoleSubtractsAreaCorrectly)
{
#if !TONB_WITH_OCCT
    GTEST_SKIP() << "TONB_WITH_OCCT disabled; skipping face-area geometry tests.";
#else
    topo::Shape shape;
    geom::CurveStore store;
    build::HalfEdgeBuilder edge_builder(shape);
    build::WireBuilder wire_builder(shape, topo::Tolerance{});
    build::FaceBuilder face_builder(shape, topo::Tolerance{});

    // Outer square: (0,0) -> (2,0) -> (2,2) -> (0,2), CCW, area = +4
    auto o0 = shape.make_vertex({0.0, 0.0});
    auto o1 = shape.make_vertex({2.0, 0.0});
    auto o2 = shape.make_vertex({2.0, 2.0});
    auto o3 = shape.make_vertex({0.0, 2.0});

    // Inner square hole: (0.5,0.5) -> (0.5,1.5) -> (1.5,1.5) -> (1.5,0.5), CW, area = -1
    auto h0 = shape.make_vertex({0.5, 0.5});
    auto h1 = shape.make_vertex({0.5, 1.5});
    auto h2 = shape.make_vertex({1.5, 1.5});
    auto h3 = shape.make_vertex({1.5, 0.5});

    ASSERT_TRUE(o0); ASSERT_TRUE(o1); ASSERT_TRUE(o2); ASSERT_TRUE(o3);
    ASSERT_TRUE(h0); ASSERT_TRUE(h1); ASSERT_TRUE(h2); ASSERT_TRUE(h3);

    auto make_edge = [&](const Point& a, const Point& b,
                         const std::shared_ptr<topo::Vertex>& va,
                         const std::shared_ptr<topo::Vertex>& vb)
            -> topo::Result<std::shared_ptr<topo::HalfEdge>> {
        const auto c = cad2d::Tools::make_segment(a, b);
        const auto r = c.parameter_range();
        if (!r.has_value()) {
            return topo::Result<std::shared_ptr<topo::HalfEdge>>(topo::ResultError{
                "FaceAreaTests: segment has no finite parameter range",
                topo::ErrorCode::geometry_error
            });
        }
        return edge_builder.create_from_curve(store, c, va, vb, r->first, r->second, topo::Orientation::forward);
    };

    auto oe0 = make_edge({0.0, 0.0}, {2.0, 0.0}, o0, o1);
    auto oe1 = make_edge({2.0, 0.0}, {2.0, 2.0}, o1, o2);
    auto oe2 = make_edge({2.0, 2.0}, {0.0, 2.0}, o2, o3);
    auto oe3 = make_edge({0.0, 2.0}, {0.0, 0.0}, o3, o0);

    auto he0 = make_edge({0.5, 0.5}, {0.5, 1.5}, h0, h1);
    auto he1 = make_edge({0.5, 1.5}, {1.5, 1.5}, h1, h2);
    auto he2 = make_edge({1.5, 1.5}, {1.5, 0.5}, h2, h3);
    auto he3 = make_edge({1.5, 0.5}, {0.5, 0.5}, h3, h0);

    ASSERT_TRUE(oe0) << oe0.error().message;
    ASSERT_TRUE(oe1) << oe1.error().message;
    ASSERT_TRUE(oe2) << oe2.error().message;
    ASSERT_TRUE(oe3) << oe3.error().message;

    ASSERT_TRUE(he0) << he0.error().message;
    ASSERT_TRUE(he1) << he1.error().message;
    ASSERT_TRUE(he2) << he2.error().message;
    ASSERT_TRUE(he3) << he3.error().message;

    auto outer = wire_builder.create({oe0.value(), oe1.value(), oe2.value(), oe3.value()}, true, true);
    auto hole  = wire_builder.create({he0.value(), he1.value(), he2.value(), he3.value()}, true, true);

    ASSERT_TRUE(outer) << outer.error().message;
    ASSERT_TRUE(hole) << hole.error().message;

    auto face = face_builder.create(outer.value(), {hole.value()});
    ASSERT_TRUE(face) << face.error().message;

    algo::FaceAreaOptions options;
    options.linearity_tolerance = 1.0e-10;
    options.area_epsilon = 1.0e-12;

    const auto area = algo::signed_area_of_face_polygon(face.value(), store, options);
    ASSERT_TRUE(area) << area.error().message;
    EXPECT_NEAR(area.value(), 3.0, 1.0e-10);

    const auto orient = algo::face_has_standard_orientation(face.value(), store, options);
    ASSERT_TRUE(orient) << orient.error().message;
    EXPECT_TRUE(orient.value());
#endif
}

} // namespace tonb::cad2d::tests

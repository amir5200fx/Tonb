/**
 * @file halfedge_intersection.cxx
 * @brief Implements topology-level half-edge span intersection utilities.
 */
#include <tonb/cad2d/algo/halfedge_intersection.hxx>

#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/geom/intersection.hxx>
#include <tonb/cad2d/geom/intersection_result.hxx>

#include <sstream>
#include <stdexcept>

namespace tonb::cad2d::algo {
    namespace {

        std::string ctx(const std::shared_ptr<topo::HalfEdge>& edge) {
            if (!edge) {
                return "HalfEdgeIntersection";
            }
            return "HalfEdgeIntersection (half-edge id=" + std::to_string(edge->id()) + ")";
        }

        topo::Result<const Curve*> resolve_curve(const std::shared_ptr<topo::HalfEdge>& edge,
                                                 const geom::CurveStore& curves,
                                                 const char* which) {
            if (!edge) {
                return topo::Result<const Curve*>(topo::ResultError{
                    std::string("HalfEdgeIntersection: ") + which + " half-edge pointer is null",
                    topo::ErrorCode::invalid_input
                });
            }

            const auto curve_id = edge->curve_id();
            if (curve_id == 0) {
                return topo::Result<const Curve*>(topo::ResultError{
                    std::string("HalfEdgeIntersection: ") + which + " half-edge stores invalid curve id 0",
                    topo::ErrorCode::geometry_error
                });
            }

            try {
                if (!curves.contains(curve_id)) {
                    return topo::Result<const Curve*>(topo::ResultError{
                        std::string("HalfEdgeIntersection: referenced curve id is not present in CurveStore for ") + which + " half-edge",
                        topo::ErrorCode::geometry_error
                    });
                }

                return topo::ok(&curves.get(curve_id));
            }
            catch (const std::exception& e) {
                return topo::Result<const Curve*>(topo::ResultError{
                    std::string("HalfEdgeIntersection: failed to resolve curve for ") + which + " half-edge (" + e.what() + ")",
                    topo::ErrorCode::geometry_error
                });
            }
        }

        HalfEdgeIntersectionResult translate_result(const topo::HalfEdge& first,
                                                    const topo::HalfEdge& second,
                                                    const geom::IntersectionResult& src) {
            HalfEdgeIntersectionResult out;
            out.status = src.status;
            out.diagnostic = src.diagnostic;
            out.items.reserve(src.items.size());

            for (const auto& item : src.items) {
                if (std::holds_alternative<geom::IntersectionPoint>(item)) {
                    const auto& p = std::get<geom::IntersectionPoint>(item);
                    out.items.emplace_back(HalfEdgeIntersectionPoint{
                        p.point,
                        first.id(),
                        second.id(),
                        p.u_on_first,
                        p.u_on_second,
                        p.kind
                    });
                }
                else {
                    const auto& ov = std::get<geom::IntersectionOverlap>(item);
                    out.items.emplace_back(HalfEdgeIntersectionOverlap{
                        ov.first_point,
                        ov.last_point,
                        first.id(),
                        second.id(),
                        ov.first_u0,
                        ov.first_u1,
                        ov.second_u0,
                        ov.second_u1
                    });
                }
            }

            return out;
        }
    }

    topo::Result<HalfEdgeIntersectionResult> intersect_halfedge_spans(
        const std::shared_ptr<topo::HalfEdge>& first,
        const std::shared_ptr<topo::HalfEdge>& second,
        const geom::CurveStore& curves,
        const HalfEdgeIntersectionOptions& options) {

        const auto first_curve = resolve_curve(first, curves, "first");
        if (!first_curve) {
            return topo::Result<HalfEdgeIntersectionResult>(first_curve.error());
        }

        const auto second_curve = resolve_curve(second, curves, "second");
        if (!second_curve) {
            return topo::Result<HalfEdgeIntersectionResult>(second_curve.error());
        }

        const auto rg = geom::intersect_bounded_spans(
            *first_curve.value(),
            first->u0(),
            first->u1(),
            *second_curve.value(),
            second->u0(),
            second->u1(),
            options.geometry);

        if (!rg) {
            return topo::Result<HalfEdgeIntersectionResult>(topo::ResultError{
                "HalfEdgeIntersection: geometry bounded-span query failed (" + rg.error().message + ")",
                rg.error().code
            });
        }

        return topo::ok(translate_result(*first, *second, rg.value()));
    }
}

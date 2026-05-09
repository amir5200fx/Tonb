/**
 * @file halfedge_intersection.hxx
 * @brief Declares topology-level half-edge span intersection utilities.
 *
 * This module bridges cad2d topology and geometry by resolving the geometric
 * curves referenced by two topology half-edges from a CurveStore and then
 * delegating the actual bounded-span intersection computation to the public
 * geometry intersection API.
 *
 * Architectural intent
 * --------------------
 * - topology ownership and references remain in cad2d/topo,
 * - curve storage and curve evaluation remain in cad2d/geom,
 * - bounded curve-span intersection remains implemented in cad2d/geom,
 * - this module only translates between half-edge span semantics and the
 *   geometry-level API.
 *
 * The result model intentionally reports intersections in half-edge/span terms
 * rather than raw curve-only terms so that later edge splitting, wire
 * fragmentation, and arrangement code can consume the results without needing
 * to reinterpret which topology entity each parameter belongs to.
 */
#pragma once
#ifndef TONB_CAD2D_ALGO_HALFEDGE_INTERSECTION_HXX
#define TONB_CAD2D_ALGO_HALFEDGE_INTERSECTION_HXX

#include <tonb/cad2d/module.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/geom/intersection.hxx>
#include <tonb/cad2d/point.hxx>

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace tonb::cad2d::topo {
    class HalfEdge;
}

namespace tonb::cad2d::geom {
    class CurveStore;
}

namespace tonb::cad2d::algo {

    /**
     * @brief One isolated intersection point reported in half-edge/span terms.
     */
    struct HalfEdgeIntersectionPoint {
        Point point;                                                  ///< Geometric intersection point.
        topo::Id first_halfedge_id = 0;                               ///< Identifier of the first half-edge.
        topo::Id second_halfedge_id = 0;                              ///< Identifier of the second half-edge.
        real u_on_first = 0.0;                                        ///< Parameter on the first half-edge span.
        real u_on_second = 0.0;                                       ///< Parameter on the second half-edge span.
        geom::IntersectionPointKind kind = geom::IntersectionPointKind::simple; ///< Local point-intersection character.
    };

    /**
     * @brief One overlap result reported in half-edge/span terms.
     */
    struct HalfEdgeIntersectionOverlap {
        Point first_point;                                            ///< Geometric start point of the overlap interval.
        Point last_point;                                             ///< Geometric end point of the overlap interval.
        topo::Id first_halfedge_id = 0;                               ///< Identifier of the first half-edge.
        topo::Id second_halfedge_id = 0;                              ///< Identifier of the second half-edge.
        real first_u0 = 0.0;                                          ///< Start parameter on the first half-edge span.
        real first_u1 = 0.0;                                          ///< End parameter on the first half-edge span.
        real second_u0 = 0.0;                                         ///< Start parameter on the second half-edge span.
        real second_u1 = 0.0;                                         ///< End parameter on the second half-edge span.
    };

    /**
     * @brief Variant representing one half-edge intersection item.
     */
    using HalfEdgeIntersectionItem = std::variant<HalfEdgeIntersectionPoint, HalfEdgeIntersectionOverlap>;

    /**
     * @brief Public container for one half-edge span intersection query.
     *
     * This report mirrors the geometry-level intersection report shape while
     * replacing raw curve-only items with half-edge-aware items.
     */
    struct HalfEdgeIntersectionResult {
        geom::IntersectionStatus status = geom::IntersectionStatus::success; ///< Overall query outcome.
        std::vector<HalfEdgeIntersectionItem> items;                        ///< Ordered result items.
        std::string diagnostic;                                             ///< Explicit unsupported/failure diagnostic.

        /**
         * @brief Return true if the query completed successfully.
         */
        TNB_NODISCARD bool ok() const noexcept {
            return status == geom::IntersectionStatus::success;
        }

        /**
         * @brief Return true if the successful query produced no intersections.
         */
        TNB_NODISCARD bool empty() const noexcept {
            return items.empty();
        }

        /**
         * @brief Count isolated point intersections in @ref items.
         */
        TNB_NODISCARD std::size_t point_count() const noexcept {
            std::size_t n = 0;
            for (const auto& item : items) {
                if (std::holds_alternative<HalfEdgeIntersectionPoint>(item)) {
                    ++n;
                }
            }
            return n;
        }

        /**
         * @brief Count overlap intersections in @ref items.
         */
        TNB_NODISCARD std::size_t overlap_count() const noexcept {
            std::size_t n = 0;
            for (const auto& item : items) {
                if (std::holds_alternative<HalfEdgeIntersectionOverlap>(item)) {
                    ++n;
                }
            }
            return n;
        }
    };

    /// @brief Stable short aliases matching the geometry-level intersection API style.
    using HalfEdgeIntersectionItemResult = HalfEdgeIntersectionResult;
    using HalfEdgeIntersectionPointResult = HalfEdgeIntersectionPoint;
    using HalfEdgeIntersectionOverlapResult = HalfEdgeIntersectionOverlap;

    /**
     * @brief Configuration for half-edge span intersection queries.
     */
    struct HalfEdgeIntersectionOptions {
        geom::IntersectionOptions geometry{}; ///< Geometry-level bounded-span intersection controls.
    };

    /**
     * @brief Intersect two topology half-edge spans.
     *
     * The function resolves both half-edge curve ids from @p curves and then
     * calls the public geometry-level bounded-span intersection API using the
     * half-edge parameter ranges.
     *
     * Explicit failure cases include:
     * - null half-edge pointers,
     * - invalid curve ids,
     * - missing curve bindings in the store,
     * - invalid underlying geometry query failures.
     *
     * @param first First half-edge span.
     * @param second Second half-edge span.
     * @param curves Curve registry used to resolve half-edge curve ids.
     * @param options Numerical controls forwarded to the geometry intersection API.
     * @return Half-edge-aware intersection result on success; explicit Result error otherwise.
     */
    TNBCAD2D_ND_EXPORT topo::Result<HalfEdgeIntersectionResult> intersect_halfedge_spans(
        const std::shared_ptr<topo::HalfEdge>& first,
        const std::shared_ptr<topo::HalfEdge>& second,
        const geom::CurveStore& curves,
        const HalfEdgeIntersectionOptions& options = {});
}

#endif // TONB_CAD2D_ALGO_HALFEDGE_INTERSECTION_HXX

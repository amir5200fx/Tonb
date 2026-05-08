//
// Created by amir on 5/7/26.
//
/**
 * @file intersection_result.hxx
 * @brief Declares public kernel-agnostic result types for 2D curve-curve intersections.
 *
 * This header defines the public result model for 2D curve-curve intersection
 * queries in cad2d. The intent is to expose a stable, geometry-kernel-agnostic
 * API surface at the cad2d layer even if the underlying implementation is
 * backed by OCCT or another kernel internally.
 *
 * Design goals
 * ------------
 * - represent isolated point intersections explicitly
 * - represent coincident / overlapping span intersections explicitly
 * - represent tangent intersections without collapsing them into the same
 *   category as ordinary transverse crossings
 * - expose parameters on both input curves
 * - expose explicit diagnostics for unsupported or failed queries
 *
 * Scope
 * -----
 * This file defines public data types only. It does not implement any specific
 * intersection algorithm. Later issues should consume these types from public
 * curve-curve and topology-level intersection APIs.
 */
#pragma once
#ifndef TONB_CAD2D_GEOM_INTERSECTION_RESULT_HXX
#define TONB_CAD2D_GEOM_INTERSECTION_RESULT_HXX

#include <tonb/cad2d/module.hxx>
#include <tonb/cad2d/point.hxx>
#include <tonb/cad2d/topo/result.hxx>

#include <cstdint>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace tonb::cad2d::geom {

    /**
     * @brief Describes the broad outcome class of an intersection query.
     */
    enum class CurveIntersectionStatus : std::uint8_t {
        success = 0,      ///< Query completed successfully; @ref items contains the result set.
        unsupported,      ///< Query combination or geometry type is not supported by the current implementation.
        failure           ///< Query failed due to invalid geometry, kernel failure, or internal error.
    };

    /**
     * @brief Classifies the local character of an isolated intersection point.
     */
    enum class CurveIntersectionPointKind : std::uint8_t {
        simple = 0,       ///< Ordinary isolated crossing.
        tangent           ///< Tangential contact at the reported point.
    };

    /**
     * @brief Describes the kind of one intersection item in the result set.
     */
    enum class CurveIntersectionItemKind : std::uint8_t {
        point = 0,        ///< One isolated point intersection.
        overlap           ///< One coincident / overlapping bounded span.
    };

    /**
     * @brief Represents one isolated point intersection between two bounded curve spans.
     *
     * The same geometric point is described by one parameter value on each input
     * curve. The point kind records whether the local interaction is simple or
     * tangential.
     */
    struct CurveIntersectionPoint {
        Point point;                                      ///< Geometric intersection point.
        real u_on_first = 0.0;                            ///< Parameter on the first curve/span.
        real u_on_second = 0.0;                           ///< Parameter on the second curve/span.
        CurveIntersectionPointKind kind =
            CurveIntersectionPointKind::simple;           ///< Local point-intersection character.
    };

    /**
     * @brief Represents one bounded coincident / overlapping span between two curves.
     *
     * Overlap is expressed through corresponding parameter intervals on both
     * input curves. The geometric endpoints are included explicitly to avoid
     * ambiguity and to keep the public result model convenient for diagnostics,
     * visualisation, and later topology-level splitting code.
     */
    struct CurveIntersectionOverlap {
        Point first_point;                                ///< Geometric start point of the overlap interval.
        Point last_point;                                 ///< Geometric end point of the overlap interval.
        real first_u0 = 0.0;                              ///< Start parameter on the first curve/span.
        real first_u1 = 0.0;                              ///< End parameter on the first curve/span.
        real second_u0 = 0.0;                             ///< Start parameter on the second curve/span.
        real second_u1 = 0.0;                             ///< End parameter on the second curve/span.
    };

    /**
     * @brief Variant representing one element of the intersection result set.
     */
    using CurveIntersectionItem = std::variant<CurveIntersectionPoint, CurveIntersectionOverlap>;

    /**
     * @brief Public result container for one 2D curve-curve intersection query.
     *
     * When @ref status is @ref CurveIntersectionStatus::success, the query
     * completed successfully and @ref items contains zero or more intersection
     * items. A successful query with an empty item set represents the common
     * "no intersections" case.
     *
     * When @ref status is not success, the query did not produce a usable result
     * set and @ref diagnostic should explain why.
     */
    struct CurveIntersectionReport {
        CurveIntersectionStatus status = CurveIntersectionStatus::success; ///< Overall query outcome.
        std::vector<CurveIntersectionItem> items;                         ///< Ordered result items.
        std::string diagnostic;                                           ///< Explicit diagnostic for unsupported/failure cases.

        /**
         * @brief Return true if the query completed successfully.
         */
        TNB_NODISCARD bool ok() const noexcept {
            return status == CurveIntersectionStatus::success;
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
                if (std::holds_alternative<CurveIntersectionPoint>(item)) {
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
                if (std::holds_alternative<CurveIntersectionOverlap>(item)) {
                    ++n;
                }
            }
            return n;
        }

        /**
         * @brief Return true if any overlap item is present.
         */
        TNB_NODISCARD bool has_overlap() const noexcept {
            return overlap_count() > 0;
        }
    };

    /**
     * @name Public shorthand aliases
     * @brief Stable short names intended for direct use by public intersection APIs.
     *
     * The longer `CurveIntersection*` names remain the primary documented model.
     * These aliases provide a cleaner surface for callers and for later
     * bounded-span/topology-level intersection APIs without changing the
     * underlying result model.
     */
    ///@{
    using IntersectionStatus = CurveIntersectionStatus;
    using IntersectionPointKind = CurveIntersectionPointKind;
    using IntersectionItemKind = CurveIntersectionItemKind;
    using IntersectionPoint = CurveIntersectionPoint;
    using IntersectionOverlap = CurveIntersectionOverlap;
    using IntersectionItem = CurveIntersectionItem;
    using IntersectionResult = CurveIntersectionReport;
    ///@}

    /**
     * @brief Construct a successful empty intersection report.
     *
     * This represents a valid query that found no intersections.
     */
    TNB_NODISCARD inline CurveIntersectionReport make_no_intersections() {
        return CurveIntersectionReport{};
    }

    /**
     * @brief Construct a successful report from one isolated point item.
     *
     * @param point Geometric intersection point.
     * @param u_on_first Parameter on the first curve/span.
     * @param u_on_second Parameter on the second curve/span.
     * @param kind Local point-intersection character.
     * @return Successful report containing one point item.
     */
    TNB_NODISCARD inline CurveIntersectionReport make_point_intersection(
        const Point& point,
        const real u_on_first,
        const real u_on_second,
        const CurveIntersectionPointKind kind = CurveIntersectionPointKind::simple) {

        CurveIntersectionReport out;
        out.items.emplace_back(CurveIntersectionPoint{
            point,
            u_on_first,
            u_on_second,
            kind
        });
        return out;
    }

    /**
     * @brief Construct a successful report from one overlap item.
     *
     * @param first_point Geometric start point of the overlap interval.
     * @param last_point Geometric end point of the overlap interval.
     * @param first_u0 Start parameter on the first curve/span.
     * @param first_u1 End parameter on the first curve/span.
     * @param second_u0 Start parameter on the second curve/span.
     * @param second_u1 End parameter on the second curve/span.
     * @return Successful report containing one overlap item.
     */
    TNB_NODISCARD inline CurveIntersectionReport make_overlap_intersection(
        const Point& first_point,
        const Point& last_point,
        const real first_u0,
        const real first_u1,
        const real second_u0,
        const real second_u1) {

        CurveIntersectionReport out;
        out.items.emplace_back(CurveIntersectionOverlap{
            first_point,
            last_point,
            first_u0,
            first_u1,
            second_u0,
            second_u1
        });
        return out;
    }

    /**
     * @brief Construct an unsupported intersection report with explicit diagnostic.
     *
     * @param diagnostic Stable human-readable explanation.
     * @return Unsupported report.
     */
    TNB_NODISCARD inline CurveIntersectionReport make_unsupported_intersection(
        std::string diagnostic) {

        CurveIntersectionReport out;
        out.status = CurveIntersectionStatus::unsupported;
        out.diagnostic = std::move(diagnostic);
        return out;
    }

    /**
     * @brief Construct a failed intersection report with explicit diagnostic.
     *
     * @param diagnostic Stable human-readable explanation.
     * @return Failure report.
     */
    TNB_NODISCARD inline CurveIntersectionReport make_failed_intersection(
        std::string diagnostic) {

        CurveIntersectionReport out;
        out.status = CurveIntersectionStatus::failure;
        out.diagnostic = std::move(diagnostic);
        return out;
    }

    /**
     * @brief Return the item kind of one result item.
     *
     * @param item Item to inspect.
     * @return Point or overlap classification.
     */
    TNB_NODISCARD inline CurveIntersectionItemKind item_kind(const CurveIntersectionItem& item) noexcept {
        return std::holds_alternative<CurveIntersectionPoint>(item)
            ? CurveIntersectionItemKind::point
            : CurveIntersectionItemKind::overlap;
    }
}

#endif // TONB_CAD2D_GEOM_INTERSECTION_RESULT_HXX
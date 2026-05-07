//
// Created by amir on 1/25/26.
//
/**
 * @file geom_consistency.hxx
 * @brief Batch geometry-consistency validation for a full cad2d shape.
 *
 * This module provides a report-oriented validation path for geometry
 * consistency. Unlike check_halfedge_geometry(), which stops at the first error,
 * geom_consistency() traverses the full shape and accumulates all detected
 * issues. This is useful for diagnostics, import checking, CLI reporting, and
 * future editor tooling where a single failing edge is not enough.
 *
 * Design intent
 * -------------
 * - Avoid exceptions for ordinary validation failures.
 * - Collect multiple issues in one run.
 * - Remain independent of a specific geometry kernel by depending only on a
 *   minimal curve-evaluation interface.
 * - Be usable even when the owning application does not use CurveStore
 *   directly, as long as it can provide an evaluator adaptor.
 */
#pragma once
#ifndef TONB_CAD2D_VALIDATE_GEOM_CONSISTENCY_HXX
#define TONB_CAD2D_VALIDATE_GEOM_CONSISTENCY_HXX

#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/point.hxx>
#include <tonb/cad2d/module.hxx>

#include <memory>
#include <optional>
#include <vector>
#include <string>
#include <cstdint>

namespace tonb::cad2d::topo {
    class Shape;
}

namespace tonb::cad2d::validate {

    /**
     * @brief Codes describing geometry-consistency problems discovered in batch mode.
     */
    enum class GeomIssueCode : std::uint32_t {
        curve_missing = 1,          ///< Half-edge stores an invalid or unresolved curve id.
        domain_invalid,             ///< Resolved curve reported a non-finite or reversed domain.
        param_not_finite,           ///< Stored half-edge parameter was NaN or Inf.
        param_out_of_domain,        ///< Stored half-edge parameter lies outside curve domain.
        param_degenerate,           ///< |u1 - u0| is too small for a valid span.
        orientation_mismatch,       ///< Half-edge orientation disagrees with parameter ordering.
        curve_eval_failed,          ///< Curve evaluation failed at one of the required parameters.
        missing_start_vertex,       ///< start() vertex reference was missing.
        missing_end_vertex,         ///< end() vertex reference was missing.
        endpoint_mismatch_start,    ///< Evaluated start point does not match topology start vertex.
        endpoint_mismatch_end,      ///< Evaluated end point does not match topology end vertex.
        twin_endpoint_mismatch,     ///< Half-edge and twin do not reverse the same geometric segment.
        shared_vertex_mismatch      ///< Incident edges disagree with the shared vertex position.
    };

    /**
     * @brief Single issue record emitted by batch geometry validation.
     */
    struct GeomIssue {
        GeomIssueCode code{};
        topo::Id edge{0};
        topo::Id vertex{0};
        real measured{0.0};
        real allowed{0.0};
        std::string message;
    };

    /**
     * @brief Aggregated report of all geometry-consistency issues found.
     */
    class GeomReport {
    public:
        /// @brief True when the report contains no issues.
        TNB_NODISCARD bool ok() const noexcept { return issues_.empty(); }

        /// @brief Access the collected issues.
        TNB_NODISCARD const std::vector<GeomIssue>& issues() const noexcept { return issues_; }

        /// @brief Append one issue to the report.
        void add(GeomIssue issue) { issues_.push_back(std::move(issue)); }

    private:
        std::vector<GeomIssue> issues_;
    };

    /**
     * @brief Configuration for batch geometry-consistency validation.
     */
    struct GeomValidationConfig {
        topo::Tolerance tol_override{};     ///< If non-zero, overrides/augments local tolerances.
        real param_eps = 1.e-14;            ///< Minimum accepted absolute parametric span.
        bool check_twin = true;             ///< Enable twin geometric reversal checks.
        bool check_shared_vertex = true;    ///< Enable shared-vertex consistency checks.
    };

    /**
     * @brief Minimal curve-evaluation interface required by geom_consistency().
     *
     * The interface is intentionally tiny. A caller may implement this over
     * CurveStore, over another internal registry, or over an import adaptor.
     */
    class ICurveEval2d {
    public:
        virtual ~ICurveEval2d() = default;

        /**
         * @brief Evaluate a curve point at parameter u.
         * @param curve_id Opaque curve identifier.
         * @param u Curve parameter.
         * @return Point if evaluation succeeds, std::nullopt otherwise.
         */
        virtual std::optional<Point> eval(topo::Id curve_id, real u) const = 0;

        /**
         * @brief Return the parameter domain of a curve.
         * @param curve_id Opaque curve identifier.
         * @return Domain pair if available, std::nullopt otherwise.
         */
        virtual std::optional<std::pair<real, real>> domain(topo::Id curve_id) const = 0;
    };

    /**
     * @brief Validate geometry consistency for all half-edges in a shape.
     *
     * @param shape Shape whose half-edges will be inspected.
     * @param curves Curve evaluation adaptor used to access geometry.
     * @param cfg Batch-validation configuration.
     * @return Report containing all issues discovered during the traversal.
     */
    TNBCAD2D_EXPORT GeomReport geom_consistency(const topo::Shape& shape,
                                               const ICurveEval2d& curves,
                                               const GeomValidationConfig& cfg = {});
}

#endif // TONB_CAD2D_VALIDATE_GEOM_CONSISTENCY_HXX

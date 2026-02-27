//
// Created by amir on 1/25/26.
//
/**
 * @file geom_consistency.hxx
 * @brief Geometry consistency validation: vertex-curve agreement checks
 *
 * This module validates that topology entities (HalfEdge/Vertex) are geometrically consistent
 * with the bound curve segments referenced by HalfEdge::curve_id.
 *
 * Design principles:
 * - No exceptions for "validation failures": those are returned as issues in the report.
 * - Standard exceptions are appropriate only for programmer errors (invalid IDs, inactive entities),
 *   but this module tries to avoid throwing and instead reports issues wherever possible.
 */
#pragma once
#ifndef TONB_CAD2D_VALIDATE_GEOM_CONSISTENCY_HXX
#define TONB_CAD2D_VALIDATE_GEOM_CONSISTENCY_HXX

#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/point.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/cad2d/topo/shape.hxx>

#include <vector>

namespace tonb::cad2d::validate {

    /**
     * @brief Codes describing geometry consistency problems.
     *
     * Keep these specific. They become test assertions and CLI filters later.
     */
    enum class GeomIssueCode : std::uint32_t {
        curve_missing = 1,              ///< Half-edge has an invalid curve_id (typically 0).
        param_not_finite,               ///< u0 or u1 is NaN/Inf.
        param_degenerate,               ///< |u1-u0| is too small.
        curve_eval_failed,              ///< Curve evaluation failed at u0/u1/mid.
        missing_start_vertex,           ///< start() vertex weak_ptr expired.
        missing_end_vertex,             ///< end() vertex weak_ptr expired.
        endpoint_mismatch_start,        ///< Curve endpoint does not match start vertex position.
        endpoint_mismatch_end,          ///< Curve endpoint does nto match end vertex position.
        twin_endpoint_mismatch,         ///< Twin half-edge do not agree on geometric endpoints.
        shared_vertex_mismatch          ///< Incident curve endpoints do not agree with vertex position.
    };

    struct GeomIssue {
        GeomIssueCode code{};
        topo::Id edge{0};           ///< Primary half-edge id invoked (0 if N/A).
        topo::Id vertex{0};         ///< Vertex id involved (0 if N/A).

        real measured = 0.0;        ///< Measured distance or metric relevant to the issue.
        real allowed = 0.0;         ///< Tolerance threshold used.

        std::string message;        ///< Human-readable message intended for logs/CLI
    };

    class GeomReport {
    public:
        /// @brief  Returns true if no issues were recorded.
        TNB_NODISCARD bool ok() const noexcept {return issues_.empty();}

        /// @brief Access recorded issues.
        TNB_NODISCARD const std::vector<GeomIssue>& issues() const noexcept {return issues_;}

        /// @brief Append ann issue.
        void add(GeomIssue issue) noexcept {issues_.push_back(std::move(issue));}

    private:
        std::vector<GeomIssue> issues_;
    };

    struct GeomValidationConfig {
        topo::Tolerance tol_override{};         ///< If non-zero, can override/augment entity tolerances.
        real param_eps = 1.e-14;                ///< Minimum allowed |u1 - u0|.
        bool check_twin = true;                 ///< Validate twin endpoint consistency when twin exists
        bool check_shared_vertex = true;        ///< Validate shared vertex agreement across incident edges.
    };

    /**
     * @brief Minimal curve evaluation interface expected by this validator.
     *
     * Implement an adaptor over your actual CurveStore / Curve2d wrapper.
     * The validator only needs point evaluation.
     *
     * Contract:
     * - Return std::nullopt if the curve is missing or evaluation fails.
     * - Do not throw for normal evaluation failures; keep exceptions inside adapter.
     */
    class ICurveEval2d {
    public:
        virtual ~ICurveEval2d() = default;

        /// @brief Evaluate curve point at parameter u, Returns std::nullopt if evaluation fails.
        virtual std::optional<Point> eval(topo::Id curve_id, real u) const = 0;
    };

    GeomReport geom_consistency(const topo::Shape& shape, const ICurveEval2d& curves, const GeomValidationConfig& cfg);
}

#endif //TONB_CAD2D_VALIDATE_GEOM_CONSISTENCY_HXX
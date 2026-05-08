/**
 * @file failure_bundle.hxx
 * @brief Deterministic serialisable failure-bundle model.
 *
 * @details
 * A failure bundle is the persisted evidence package for a failure. The model is
 * deliberately data-only and deterministic:
 * - no filesystem access
 * - no logging side effects
 * - no unordered containers
 * - fixed JSON field order
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_BUNDLE_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_BUNDLE_HXX

#include <tonb/foundation/failure/failure_context.hxx>
#include <tonb/foundation/failure/failure_diagnostic.hxx>
#include <tonb/foundation/failure/failure_event.hxx>
#include <tonb/foundation/failure/failure_policy.hxx>
#include <tonb/foundation/module.hxx>

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace tonb::foundation::failure {

    /**
     * @brief Persisted metadata for a bundle root.
     */
    struct FailureBundleMetadata {
        std::string bundle_schema = "foundation.failure.bundle.v1";
        std::string application;
        std::optional<std::string> application_version;
        std::string run_id;
        std::uint32_t sequence = 0;
        std::string code;
        FailureKind kind = FailureKind::unknown;
        FailureSeverity severity = FailureSeverity::error;
        std::string domain;
        std::string created_utc;
        std::string message;
        std::optional<std::string> exception_type;
        std::optional<std::string> correlation_id;
    };

    /**
     * @brief Minimal execution-environment summary.
     */
    struct FailureBundleEnvironment {
        std::optional<std::string> operating_system;
        std::optional<std::string> build_type;
        std::optional<std::string> compiler;
        std::optional<std::string> host;
        std::optional<std::uint64_t> process_id;
        std::optional<std::string> thread_id;
        DiagnosticFields diagnostics;
    };

    /**
     * @brief Reference to a payload file under artefacts/.
     */
    struct FailureArtefact {
        std::string relative_path;
        std::optional<std::string> description;
        std::optional<std::string> content_type;
        bool required = false;
    };

    /**
     * @brief Full persisted bundle model.
     */
    struct FailureBundle {
        FailureBundleMetadata metadata;
        FailureContext context;
        FailureBundleEnvironment environment;
        DiagnosticFields diagnostics;
        FailureCauses causes;
        std::vector<FailureArtefact> artefacts;
    };

    /**
     * @brief JSON serialisation options.
     */
    struct FailureJsonOptions {
        bool pretty = true;
        int indent_spaces = 2;
    };

    TNBFOUND_ND_EXPORT std::string to_json(const FailureBundleMetadata& metadata, const FailureJsonOptions& opt = {});
    TNBFOUND_ND_EXPORT std::string to_json(const FailureContext& context, const FailureJsonOptions& opt = {});
    TNBFOUND_ND_EXPORT std::string to_json(const FailureBundleEnvironment& environment, const FailureJsonOptions& opt = {});
    TNBFOUND_ND_EXPORT std::string to_json(const FailureArtefact& artefact, const FailureJsonOptions& opt = {});
    TNBFOUND_ND_EXPORT std::string to_json(const FailureBundle& bundle, const FailureJsonOptions& opt = {});

    /**
     * @brief Build a deterministic bundle model from a FailureEvent.
     */
    TNBFOUND_ND_EXPORT FailureBundle make_bundle_from_event(
        const FailureEvent& event,
        std::string application,
        std::optional<std::string> application_version,
        std::string run_id,
        std::uint32_t sequence,
        FailurePolicy policy,
        FailureBundleEnvironment environment = {});

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_BUNDLE_HXX

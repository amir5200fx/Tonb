/**
 * @file failure_policy.hxx
 * @brief Policy controlling capture, redaction, and bundle persistence behaviour.
 *
 * @details
 * The foundation failure subsystem separates the logical failure model from the
 * decision of how much evidence should be captured and persisted. This lets a
 * command-line shell, a GUI process, and a test harness all use the same model
 * while applying different operational policies.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_POLICY_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_POLICY_HXX

#include <tonb/foundation/failure/failure_severity.hxx>
#include <tonb/foundation/module.hxx>

#include <cstdint>
#include <optional>

namespace tonb::foundation::failure {

    /**
     * @brief Failure capture and persistence policy.
     */
    struct FailurePolicy {
        /** @brief Lowest severity that should trigger bundle persistence. */
        FailureSeverity bundle_threshold = FailureSeverity::error;

        /** @brief If true, user-facing filesystem paths are redacted in persisted bundles. */
        bool redact_paths = false;

        /** @brief If true, environment information may be persisted. */
        bool capture_environment = false;

        /** @brief Maximum total bundle size in bytes. */
        std::uint64_t max_total_bytes = 50ull * 1024ull * 1024ull;

        /** @brief Optional per-artefact file cap in bytes. */
        std::optional<std::uint64_t> max_file_bytes = 16ull * 1024ull * 1024ull;
    };

    /**
     * @brief Return true if the supplied severity should produce a bundle.
     */
    TNBFOUND_ND_EXPORT bool should_write_bundle(
        const FailurePolicy& policy,
        FailureSeverity severity) noexcept;

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_POLICY_HXX

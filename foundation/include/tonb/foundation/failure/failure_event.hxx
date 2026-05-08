/**
 * @file failure_event.hxx
 * @brief Structured failure-event model used before persistence.
 *
 * @details
 * A FailureEvent is the central in-memory representation of a failure. It is
 * richer than a bundle metadata block and is designed to support future
 * integrations such as logging correlation, telemetry, and exception bridging.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_EVENT_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_EVENT_HXX

#include <tonb/foundation/failure/failure_cause.hxx>
#include <tonb/foundation/failure/failure_code.hxx>
#include <tonb/foundation/failure/failure_context.hxx>
#include <tonb/foundation/failure/failure_diagnostic.hxx>
#include <tonb/foundation/failure/failure_kind.hxx>
#include <tonb/foundation/failure/failure_severity.hxx>
#include <tonb/foundation/module.hxx>

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace tonb::foundation::failure {

    /**
     * @brief Canonical failure event captured at an application boundary.
     */
    struct FailureEvent {
        /** @brief Stable support-facing code. */
        FailureCode code;

        /** @brief Broad failure classification. */
        FailureKind kind = FailureKind::unknown;

        /** @brief Severity assigned to the event. */
        FailureSeverity severity = FailureSeverity::error;

        /** @brief Application-defined logical domain such as "geom" or "shell". */
        std::string domain;

        /** @brief Human-readable message. */
        std::string message;

        /** @brief UTC creation timestamp in ISO-8601 format. */
        std::string created_utc;

        /** @brief Optional type name if the event originated from an exception. */
        std::optional<std::string> exception_type;

        /** @brief Optional correlation identifier for log/API linkage. */
        std::optional<std::string> correlation_id;

        /** @brief Optional process identifier. */
        std::optional<std::uint64_t> process_id;

        /** @brief Optional thread identifier token. */
        std::optional<std::string> thread_id;

        /** @brief Compact structured diagnostics. */
        DiagnosticFields diagnostics;

        /** @brief Ordered cause chain from immediate cause to root cause. */
        FailureCauses causes;

        /** @brief Operation-level context associated with the failure boundary. */
        FailureContext context;
    };

    /**
     * @brief Return the current UTC timestamp in ISO-8601 form.
     */
    TNBFOUND_ND_EXPORT std::string current_utc_timestamp();

    /**
     * @brief Return true if the supplied domain token is valid.
     *
     * @details
     * The domain is intentionally application-defined, but the foundation layer
     * still requires a disciplined token format to keep bundles and logs uniform.
     */
    TNBFOUND_ND_EXPORT bool is_valid_domain_token(std::string_view token) noexcept;

    /**
     * @brief Redact obvious filesystem paths for bundle persistence.
     *
     * @details
     * This is intentionally conservative. It preserves human-readable structure but
     * avoids writing user-specific absolute paths into persisted bundles when the
     * policy requires redaction.
     */
    TNBFOUND_ND_EXPORT std::string redact_paths_copy(std::string value);

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_EVENT_HXX

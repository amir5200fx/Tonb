/**
 * @file failure_severity.hxx
 * @brief Failure severity taxonomy for the foundation failure subsystem.
 *
 * @details
 * Severity is intentionally richer than a simple critical/non-critical flag.
 * The value is used by capture policy, bundle writing policy, escalation logic,
 * and user-facing diagnostics.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_SEVERITY_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_SEVERITY_HXX

#include <tonb/foundation/module.hxx>

#include <string_view>

namespace tonb::foundation::failure {

    /**
     * @brief Severity assigned to a failure event.
     */
    enum class FailureSeverity {
        warning,
        error,
        critical,
        fatal
    };

    /**
     * @brief Return the canonical lowercase token for a severity.
     */
    TNBFOUND_ND_EXPORT std::string_view to_string(FailureSeverity severity) noexcept;

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_SEVERITY_HXX

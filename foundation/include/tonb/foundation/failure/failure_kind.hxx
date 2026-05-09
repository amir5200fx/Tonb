/**
 * @file failure_kind.hxx
 * @brief Canonical high-level failure-kind taxonomy.
 *
 * @details
 * Failure kind is intentionally broad. It classifies the engineering or
 * infrastructure activity that failed, while a dedicated failure code carries
 * the more stable and support-facing identifier.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_KIND_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_KIND_HXX

#include <tonb/foundation/module.hxx>

#include <string_view>

namespace tonb::foundation::failure {

    /**
     * @brief Broad failure categories used across future applications.
     */
    enum class FailureKind {
        user_input,
        configuration,
        filesystem,
        serialisation,
        validation,
        invariant_violation,
        internal_error,
        external_tool,
        geometry,
        meshing,
        topology,
        unknown
    };

    /**
     * @brief Return the canonical lowercase token for a failure kind.
     */
    TNBFOUND_ND_EXPORT std::string_view to_string(FailureKind kind) noexcept;

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_KIND_HXX

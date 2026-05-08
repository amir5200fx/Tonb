/**
 * @file failure_artefact_matrix.hxx
 * @brief Deterministic artefact requirement rules for failure bundles.
 *
 * @details
 * This module intentionally keeps the first version simple. It provides broad
 * default requirements for common infrastructure and engineering failure kinds.
 * Applications may extend bundle content above this baseline.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_ARTEFACT_MATRIX_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_ARTEFACT_MATRIX_HXX

#include <tonb/foundation/failure/failure_kind.hxx>
#include <tonb/foundation/module.hxx>

#include <string_view>
#include <vector>

namespace tonb::foundation::failure {

    /**
     * @brief Return the required artefact names for a failure kind.
     */
    TNBFOUND_ND_EXPORT const std::vector<std::string_view>& required_artefact_names(FailureKind kind);

    /**
     * @brief Return true if the supplied artefact name is required for the kind.
     */
    TNBFOUND_ND_EXPORT bool is_required_artefact(FailureKind kind, std::string_view filename) noexcept;

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_ARTEFACT_MATRIX_HXX

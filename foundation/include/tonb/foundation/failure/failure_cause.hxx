/**
 * @file failure_cause.hxx
 * @brief Failure-cause chain model.
 *
 * @details
 * Professional failure handling benefits from preserving causal structure.
 * A single high-level operation failure may be caused by a lower-level exception,
 * a validation error, or a tool invocation problem. This model is intentionally
 * ordered and deterministic.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_CAUSE_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_CAUSE_HXX

#include <tonb/foundation/failure/failure_diagnostic.hxx>
#include <tonb/foundation/module.hxx>

#include <optional>
#include <string>
#include <vector>

namespace tonb::foundation::failure {

    /**
     * @brief One cause entry in a failure chain.
     */
    struct FailureCause {
        /** @brief Cause classification such as "exception" or "validation". */
        std::string type;

        /** @brief Human-readable causal message. */
        std::string message;

        /** @brief Optional stable code associated with this cause. */
        std::optional<std::string> code;

        /** @brief Ordered structured diagnostics associated with this cause. */
        DiagnosticFields diagnostics;
    };

    /**
     * @brief Ordered list of causes from immediate to root cause.
     */
    using FailureCauses = std::vector<FailureCause>;

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_CAUSE_HXX

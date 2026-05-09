/**
 * @file failure_context.hxx
 * @brief Small contextual model used when capturing a failure.
 *
 * @details
 * This context is intentionally generic. It is suitable for CLI, API, and GUI
 * applications and captures the high-level execution environment without binding
 * the foundation module to one specific shell implementation.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_CONTEXT_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_CONTEXT_HXX

#include <tonb/foundation/failure/failure_diagnostic.hxx>
#include <tonb/foundation/module.hxx>

#include <optional>
#include <string>
#include <vector>

namespace tonb::foundation::failure {

    /**
     * @brief Command or operation context at the failure boundary.
     */
    struct FailureContext {
        /** @brief Human-readable operation path such as a command path or action name. */
        std::string operation;

        /** @brief Ordered raw arguments or tokens associated with the operation. */
        std::vector<std::string> args;

        /** @brief Optional current working directory. */
        std::optional<std::string> cwd;

        /** @brief Optional active workspace root. */
        std::optional<std::string> workspace_root;

        /** @brief Optional correlation identifier shared with logs or API requests. */
        std::optional<std::string> correlation_id;

        /** @brief Additional compact context fields. */
        DiagnosticFields diagnostics;
    };

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_CONTEXT_HXX

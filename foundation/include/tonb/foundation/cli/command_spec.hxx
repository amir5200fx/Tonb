/**
 * @file command_spec.hxx
 * @brief Structured metadata model for reusable command-line interfaces.
 *
 * @details
 * This header defines the canonical descriptive model used by the Tonb
 * foundation CLI layer. The model is intentionally presentation- and
 * execution-neutral:
 *
 * - it does not print anything
 * - it does not parse command lines
 * - it does not execute handlers
 * - it does not depend on application session state
 *
 * It is suitable for command registries, help renderers, API documentation,
 * schema validation, and tooling.
 */
#pragma once
#ifndef TONB_FOUNDATION_CLI_COMMAND_SPEC_HXX
#define TONB_FOUNDATION_CLI_COMMAND_SPEC_HXX

#include <tonb/foundation/cli/command_path.hxx>
#include <tonb/foundation/module.hxx>

#include <optional>
#include <string>
#include <vector>

namespace tonb::foundation::cli {

    /**
     * @brief Visibility policy controlling whether a command appears in ordinary listings.
     */
    enum class CommandVisibility {
        public_command,
        hidden_command,
        internal_command
    };

    /**
     * @brief Stability classification for user-facing commands.
     */
    enum class CommandStability {
        stable,
        experimental,
        deprecated
    };

    /**
     * @brief Metadata describing command deprecation.
     */
    struct DeprecationSpec final {
        /** @brief Canonical replacement command, if any. */
        std::string replacement;

        /** @brief Human-readable migration message, if any. */
        std::string message;
    };

    /**
     * @brief Behavioural capability flags for command metadata.
     *
     * @details
     * These fields are descriptive. They do not enforce application policy by
     * themselves, but they are useful for help output, automation layers, and
     * future safety checks.
     */
    struct CapabilitySpec final {
        bool requires_workspace = false;
        bool mutates_state = false;
        bool destructive = false;
        bool long_running = false;
        bool interactive = false;
        bool script_friendly = true;
    };

    /**
     * @brief Structured description of one option or positional argument.
     */
    struct OptionSpec final {
        /**
         * @brief Display label as shown in help output.
         *
         * Examples:
         * - `--output <file>`
         * - `<mesh-name>`
         * - `--verbose`
         */
        std::string label;

        /** @brief Human-readable description. */
        std::string description;

        /** @brief Optional default value string. */
        std::string default_value;

        /** @brief Optional suggested metavariable or semantic hint. */
        std::string value_hint;

        /** @brief Whether the option/argument is required. */
        bool required = false;

        /** @brief Whether the option may appear multiple times. */
        bool repeatable = false;

        /** @brief Whether this item is positional rather than named. */
        bool positional = false;

        /** @brief Whether this item is a flag with no explicit value. */
        bool flag = false;
    };

    /**
     * @brief Canonical metadata record for one CLI command.
     */
    struct CommandSpec final {
        /** @brief Canonical command path. */
        CommandPath canonical_path;

        /** @brief Domain/category label, e.g. `workspace` or `geom`. */
        std::string domain;

        /** @brief One-line summary suitable for listings. */
        std::string summary;

        /** @brief Optional long-form description paragraphs. */
        std::vector<std::string> description;

        /** @brief One or more usage lines in authored order. */
        std::vector<std::string> usage;

        /** @brief Authored option and positional metadata. */
        std::vector<OptionSpec> options;

        /** @brief Example invocations in authored order. */
        std::vector<std::string> examples;

        /** @brief Additional notes in authored order. */
        std::vector<std::string> notes;

        /** @brief Alternate invokable command paths. */
        std::vector<CommandPath> aliases;

        /** @brief Free-form tags for tooling and diagnostics. */
        std::vector<std::string> tags;

        /** @brief Listing visibility. */
        CommandVisibility visibility = CommandVisibility::public_command;

        /** @brief Stability classification. */
        CommandStability stability = CommandStability::stable;

        /** @brief Optional deprecation metadata. */
        std::optional<DeprecationSpec> deprecation;

        /** @brief Capability metadata. */
        CapabilitySpec capabilities{};
    };

    /**
     * @brief Validate a command specification.
     *
     * @param spec Command specification to validate.
     *
     * @throws std::invalid_argument If the specification is structurally invalid.
     */
    TNBFOUND_EXPORT void validate_command_spec(const CommandSpec& spec);

} // namespace tonb::foundation::cli

#endif // TONB_FOUNDATION_CLI_COMMAND_SPEC_HXX

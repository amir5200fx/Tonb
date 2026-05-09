/**
 * @file command_registry.hxx
 * @brief Deterministic registry for command metadata, namespaces, aliases, and path resolution.
 *
 * @details
 * This registry provides the reusable command-information backbone for command-driven
 * applications. It deliberately stores metadata only. Execution handlers and shell
 * sessions remain the responsibility of the application layer.
 *
 * Supported features:
 * - canonical command registration
 * - namespace registration
 * - deterministic child ordering via std::map
 * - alias registration with conflict detection
 * - longest-prefix command resolution
 * - namespace listing for help systems
 * - validation of duplicate and conflicting paths
 */
#pragma once
#ifndef TONB_FOUNDATION_CLI_COMMAND_REGISTRY_HXX
#define TONB_FOUNDATION_CLI_COMMAND_REGISTRY_HXX

#include <tonb/foundation/cli/command_spec.hxx>
#include <tonb/foundation/module.hxx>

#include <map>
#include <string>
#include <vector>

namespace tonb::foundation::cli {

    /**
     * @brief Summary metadata for a namespace node.
     */
    struct NamespaceSpec final {
        CommandPath path;
        std::string summary;
        CommandVisibility visibility = CommandVisibility::public_command;
        bool experimental = false;
    };

    /**
     * @brief Flat listing entry for namespace-oriented help output.
     */
    struct ListingEntry final {
        CommandPath path;
        std::string summary;
        bool is_namespace = false;
        CommandVisibility visibility = CommandVisibility::public_command;
        CommandStability stability = CommandStability::stable;
        bool alias_entry = false;
        std::string alias_target;
    };

    /**
     * @brief Result of longest-prefix command resolution.
     */
    struct ResolveResult final {
        const CommandSpec* spec = nullptr;
        CommandPath invoked_path;
        CommandPath canonical_path;
        bool used_alias = false;
        std::size_t matched_depth = 0;
        std::vector<std::string> remaining_args;
    };

    /**
     * @brief Deterministic command/namespace registry.
     */
    class CommandRegistry final {
    public:
        CommandRegistry() = default;

        /**
         * @brief Register a namespace path.
         *
         * @param spec Namespace metadata.
         *
         * @throws std::invalid_argument If the namespace path is empty.
         */
        TNBFOUND_EXPORT void add_namespace(NamespaceSpec spec);

        /**
         * @brief Register a command and its aliases.
         *
         * @param spec Command metadata.
         *
         * @throws std::invalid_argument If the command specification is invalid.
         * @throws std::logic_error If the canonical path or any alias conflicts with existing entries.
         */
        TNBFOUND_EXPORT void add_command(CommandSpec spec);

        /**
         * @brief Find a command by exact canonical path.
         */
        TNB_NODISCARD const CommandSpec* find_command(const CommandPath& path) const noexcept;

        /**
         * @brief Find a namespace by exact path.
         */
        TNB_NODISCARD const NamespaceSpec* find_namespace(const CommandPath& path) const noexcept;

        /**
         * @brief Resolve a path that may be a canonical command or an alias.
         */
        TNB_NODISCARD const CommandSpec* resolve_exact(const CommandPath& path) const noexcept;

        /**
         * @brief Resolve the deepest invokable command or alias prefix within a token sequence.
         *
         * @param tokens Full token vector.
         * @return Resolution result.
         */
        TNBFOUND_ND_EXPORT ResolveResult resolve_longest_prefix(const std::vector<std::string>& tokens) const;

        /**
         * @brief List all canonical commands in deterministic order.
         */
        TNBFOUND_ND_EXPORT std::vector<const CommandSpec*> list_commands(bool include_hidden = false) const;

        /**
         * @brief List all namespaces in deterministic order.
         */
        TNBFOUND_ND_EXPORT std::vector<const NamespaceSpec*> list_namespaces(bool include_hidden = false) const;

        /**
         * @brief List direct children under a namespace prefix.
         *
         * @param prefix Prefix namespace.
         * @param include_hidden Whether hidden/internal items should be included.
         * @param include_aliases Whether alias entries should be emitted alongside canonical commands.
         * @return Deterministically ordered listing entries.
         */
        TNBFOUND_ND_EXPORT std::vector<ListingEntry> list_direct_children(
            const CommandPath& prefix,
            bool include_hidden = false,
            bool include_aliases = false) const;

        /**
         * @brief Return the canonical target for an alias, if the supplied path is an alias.
         */
        TNB_NODISCARD std::string alias_target(const CommandPath& alias) const noexcept;

    private:
        std::map<CommandPath, NamespaceSpec> namespaces_;
        std::map<CommandPath, CommandSpec> commands_;
        std::map<CommandPath, CommandPath> aliases_;
    };

} // namespace tonb::foundation::cli

#endif // TONB_FOUNDATION_CLI_COMMAND_REGISTRY_HXX

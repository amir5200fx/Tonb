/**
 * @file help_renderer.hxx
 * @brief Deterministic plain-text renderer for command and namespace help.
 *
 * @details
 * The renderer in this header is the canonical presentation layer for the
 * foundation CLI metadata model. It is intentionally side-effect free: callers
 * receive strings and decide where, when, and how to display them.
 */
#pragma once
#ifndef TONB_FOUNDATION_CLI_HELP_RENDERER_HXX
#define TONB_FOUNDATION_CLI_HELP_RENDERER_HXX

#include <tonb/foundation/cli/command_registry.hxx>
#include <tonb/foundation/module.hxx>

#include <string>
#include <vector>

namespace tonb::foundation::cli {

    /**
     * @brief Colour output mode.
     */
    enum class ColourMode {
        none,
        ansi
    };

    /**
     * @brief Rendering options for command and namespace help.
     */
    struct RenderOptions final {
        int width = 100;
        int section_indent = 2;
        int continuation_indent = 6;
        int listing_name_width = 34;
        bool show_defaults = true;
        bool show_aliases = true;
        bool show_capabilities = true;
        bool show_tags = true;
        bool show_deprecation = true;
        bool show_hidden = false;
        ColourMode colour = ColourMode::none;
    };

    /**
     * @brief Render help for a single command.
     */
    TNBFOUND_ND_EXPORT std::string render_command(const CommandSpec& spec, const RenderOptions& options);

    /**
     * @brief Render a flat listing of commands and/or namespaces.
     */
    TNBFOUND_ND_EXPORT std::string render_listing(const std::vector<ListingEntry>& entries, const RenderOptions& options);

    /**
     * @brief Render namespace help using a registry query.
     *
     * @param registry Source registry.
     * @param prefix Namespace prefix.
     * @param options Render options.
     * @return Rendered namespace help.
     */
    TNBFOUND_ND_EXPORT std::string render_namespace(
        const CommandRegistry& registry,
        const CommandPath& prefix,
        const RenderOptions& options);

} // namespace tonb::foundation::cli

#endif // TONB_FOUNDATION_CLI_HELP_RENDERER_HXX

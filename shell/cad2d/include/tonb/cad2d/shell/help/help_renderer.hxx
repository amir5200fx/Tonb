#pragma once
#ifndef TONB_CAD2D_SHELL_HELP_HELP_RENDERER_HXX
#define TONB_CAD2D_SHELL_HELP_HELP_RENDERER_HXX

#include <tonb/cad2d/shell/help/help_registry.hxx>
#include <tonb/cad2d/shell/module.hxx>

namespace tonb::cad2d::shell::help {

    /**
     * @brief Render top-level shell help using the foundation namespace renderer.
     */
    TNBCAD2DSHELL_ND_EXPORT std::string render_help_root(
        const HelpRegistry& registry,
        const foundation::cli::RenderOptions& options = {});

    /**
     * @brief Render help for a specific command or namespace path.
     */
    TNBCAD2DSHELL_ND_EXPORT HelpResult render_help(
        const HelpRegistry& registry,
        const foundation::cli::CommandPath& path,
        const foundation::cli::RenderOptions& options = {});

    /**
     * @brief Render help for a specific command or namespace path expressed as segments.
     */
    TNBCAD2DSHELL_ND_EXPORT HelpResult render_help(
        const HelpRegistry& registry,
        const std::vector<std::string>& segments,
        const foundation::cli::RenderOptions& options = {});

} // namespace tonb::cad2d::shell::help

#endif // TONB_CAD2D_SHELL_HELP_HELP_RENDERER_HXX

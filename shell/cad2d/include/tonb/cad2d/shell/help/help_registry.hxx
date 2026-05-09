#pragma once
#ifndef TONB_CAD2D_SHELL_HELP_HELP_REGISTRY_HXX
#define TONB_CAD2D_SHELL_HELP_HELP_REGISTRY_HXX

#include <tonb/cad2d/shell/help/command_spec.hxx>
#include <tonb/cad2d/shell/module.hxx>
#include <tonb/foundation/cli/command_path.hxx>
#include <tonb/foundation/cli/help_renderer.hxx>

#include <string>
#include <vector>

namespace tonb::cad2d::shell::help {

    /**
     * @brief Structured result of a help-render query.
     *
     * The shell help subsystem reports success/failure explicitly so future
     * command handlers can surface help failures without relying on exceptions or
     * ad hoc string conventions.
     */
    struct HelpResult {
        bool ok = true;
        std::string text;

        TNB_NODISCARD static HelpResult success(std::string value) {
            return HelpResult{true, std::move(value)};
        }

        TNB_NODISCARD static HelpResult failure(std::string value) {
            return HelpResult{false, std::move(value)};
        }
    };

    /**
     * @brief cad2d shell help registry built on the Tonb foundation CLI registry.
     *
     * This class owns shell-specific help content while delegating the generic
     * command metadata, namespace listing, alias handling, and rendering support
     * to the reusable foundation CLI layer.
     */
    class HelpRegistry {
    public:
        HelpRegistry() = default;

        TNBCAD2DSHELL_EXPORT void add_namespace(NamespaceSpec spec);
        TNBCAD2DSHELL_EXPORT void add_command(CommandSpec spec);

        TNBCAD2DSHELL_ND_EXPORT const foundation::cli::CommandRegistry& foundation_registry() const noexcept;

        TNBCAD2DSHELL_ND_EXPORT std::string render_root(
            const foundation::cli::RenderOptions& options = {}) const;

        TNBCAD2DSHELL_ND_EXPORT HelpResult render_path(
            const foundation::cli::CommandPath& path,
            const foundation::cli::RenderOptions& options = {}) const;

        TNBCAD2DSHELL_ND_EXPORT HelpResult render_path(
            const std::vector<std::string>& segments,
            const foundation::cli::RenderOptions& options = {}) const;

    private:
        foundation::cli::CommandRegistry registry_;
    };

} // namespace tonb::cad2d::shell::help

#endif // TONB_CAD2D_SHELL_HELP_HELP_REGISTRY_HXX

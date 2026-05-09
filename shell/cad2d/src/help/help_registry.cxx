#include <tonb/cad2d/shell/help/help_registry.hxx>

#include <tonb/foundation/cli/help_renderer.hxx>

namespace tonb::cad2d::shell::help {

    void HelpRegistry::add_namespace(NamespaceSpec spec) {
        registry_.add_namespace(std::move(spec));
    }

    void HelpRegistry::add_command(CommandSpec spec) {
        registry_.add_command(std::move(spec));
    }

    const foundation::cli::CommandRegistry& HelpRegistry::foundation_registry() const noexcept {
        return registry_;
    }

    std::string HelpRegistry::render_root(const foundation::cli::RenderOptions& options) const {
        return foundation::cli::render_namespace(registry_, foundation::cli::CommandPath{}, options);
    }

    HelpResult HelpRegistry::render_path(const foundation::cli::CommandPath& path,
                                         const foundation::cli::RenderOptions& options) const {
        if (const auto* spec = registry_.resolve_exact(path); spec != nullptr) {
            return HelpResult::success(foundation::cli::render_command(*spec, options));
        }

        if (const auto* ns = registry_.find_namespace(path); ns != nullptr) {
            (void)ns;
            return HelpResult::success(foundation::cli::render_namespace(registry_, path, options));
        }

        return HelpResult::failure("unknown help path: " + path.to_string());
    }

    HelpResult HelpRegistry::render_path(const std::vector<std::string>& segments,
                                         const foundation::cli::RenderOptions& options) const {
        return render_path(foundation::cli::CommandPath(segments), options);
    }

} // namespace tonb::cad2d::shell::help

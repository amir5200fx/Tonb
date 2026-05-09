#include <tonb/cad2d/shell/help/help_renderer.hxx>

namespace tonb::cad2d::shell::help {

    std::string render_help_root(const HelpRegistry& registry,
                                 const foundation::cli::RenderOptions& options) {
        return registry.render_root(options);
    }

    HelpResult render_help(const HelpRegistry& registry,
                           const foundation::cli::CommandPath& path,
                           const foundation::cli::RenderOptions& options) {
        return registry.render_path(path, options);
    }

    HelpResult render_help(const HelpRegistry& registry,
                           const std::vector<std::string>& segments,
                           const foundation::cli::RenderOptions& options) {
        return registry.render_path(segments, options);
    }

} // namespace tonb::cad2d::shell::help

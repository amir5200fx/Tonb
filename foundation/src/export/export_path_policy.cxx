/**
* @file export_path_policy.cxx
 * @brief Implementation of deterministic export path resolution policy.
 */
#include <tonb/foundation/export/export_path_policy.hxx>

#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <filesystem>

namespace tonb::foundation::exporting {
    std::filesystem::path ExportPathPolicy::resolve_export_bundle_root(
        const workspace::Workspace &ws,
        std::string_view ns,
        const std::optional<std::filesystem::path> &user_path,
        const ExportAutoNameOptions &auto_opt) {
        validate_namespace(ns);

        // If auto_opt provides a namespace, it must match the requested namespace to avoid surprises.
        if (!auto_opt.ns.empty() && auto_opt.ns != ns) {
            throw std::invalid_argument("ExportPathPolicy: auto_opt.ns does not match ns");
        }

        ExportAutoNameOptions effective = auto_opt;
        effective.ns = std::string(ns);

        const std::filesystem::path ns_export_base =
            (ws.dir(effective.area) / std::filesystem::path(std::string(ns))).lexically_normal();

        // No user path: use auto-generated bundle folder under <area>/<namespace>/.
        if (!user_path.has_value() || user_path->empty()) {
            const std::string auto_dir = make_auto_bundle_dir_name(effective);
            return (ns_export_base / auto_dir).lexically_normal();
        }

        const std::filesystem::path p = user_path->lexically_normal();

        // Absolute respected: if it looks like a directory path, append auto folder.
        if (p.is_absolute()) {
            if (has_meaningful_filename(p)) {
                return p;
            }
            const std::string auto_dir = make_auto_bundle_dir_name(effective);
            return (p / auto_dir).lexically_normal();
        }

        // Relative resolved under <area>/<namespace>/ (with traversal protection).
        // If relative path has meaningful filename, treat it as the bundle root itself.
        // If not, treat it as a directory and append the auto-generated bundle folder.
        if (has_meaningful_filename(p)) {
            return ws.resolve_under(ns_export_base, p);
        }

        const std::string auto_dir = make_auto_bundle_dir_name(effective);
        return ws.resolve_under(ns_export_base, p / auto_dir);
    }

    void ExportPathPolicy::validate_namespace(std::string_view ns) {
        if (ns.empty()) {
            throw std::invalid_argument("ExportPathPolicy: namespace must not be empty");
        }

        if (ns == "." || ns == "..") {
            throw std::invalid_argument("ExportPathPolicy: namespace must not be '.' or '..'");
        }

        if (ns.find('/') != std::string_view::npos || ns.find('\\') != std::string_view::npos) {
            throw std::invalid_argument("ExportPathPolicy: namespace must not contain path separators");
        }

        if (ns.find("..") != std::string_view::npos) {
            throw std::invalid_argument("ExportPathPolicy: namespace must not contain traversal segments");
        }
    }

    bool ExportPathPolicy::has_meaningful_filename(const std::filesystem::path &p) {
        const std::filesystem::path f = p.filename();
        if (f.empty())
            return false;

        const std::string s = f.string();
        return !(s.empty() || s == "." || s == "..");
    }

    std::string ExportPathPolicy::make_auto_bundle_dir_name(const ExportAutoNameOptions &opt) {
        std::ostringstream oss;
        oss << std::setw(6) << std::setfill('0') << opt.sequence;

        const std::string ns = sanitise_token(opt.ns);
        const std::string verb = sanitise_token(opt.verb);
        const std::string input_tag = sanitise_token(opt.input_tag);

        oss << "__" << (ns.empty() ? "export" : ns);
        if (!verb.empty())
            oss << "-" << verb;

        if (!input_tag.empty())
            oss << "__" << input_tag;

        return oss.str();
    }

    std::string ExportPathPolicy::sanitise_token(std::string s) {
        for (char &ch: s) {
            if (std::isspace(static_cast<unsigned char>(ch)) || ch == '/' || ch == '\\') {
                ch = '_';
            }
        }

        while (!s.empty() && s.front() == '_')
            s.erase(s.begin());

        while (!s.empty() && s.back() == '_')
            s.pop_back();

        return s;
    }
}
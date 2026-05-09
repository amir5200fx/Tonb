/**
 * @file workspace_persist.cxx
 * @brief Implementation of workspace-root persistence helpers.
 */
#include <tonb/foundation/workspace/workspace_persist.hxx>

#include <tonb/foundation/config/app_config.hxx>
#include <tonb/foundation/util/env.hxx>

#include <algorithm>
#include <cctype>

namespace tonb::foundation::workspace {
    namespace fs = std::filesystem;

    namespace {

        fs::path normalise_root(const fs::path& in) {
            if (in.empty()) {
                return {};
            }
            fs::path p = in;
            if (p.is_relative()) {
                p = fs::absolute(p);
            }
            std::error_code ec;
            const auto wcan = fs::weakly_canonical(p, ec);
            if (!ec) {
                return wcan.lexically_normal();
            }
            return p.lexically_normal();
        }

        std::string workspace_env_var_name(const tonb::foundation::config::AppIdentity& app) {
            std::string out;
            out.reserve(app.app_dir_name.size() + 10);
            for (const char c : app.app_dir_name) {
                if (std::isalnum(static_cast<unsigned char>(c))) {
                    out.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
                } else {
                    out.push_back('_');
                }
            }
            out += "_WORKSPACE";
            return out;
        }

    } // namespace

    void save_workspace_root(const tonb::foundation::config::AppIdentity& app, const fs::path& root) {
        const auto p = normalise_root(root);
        if (p.empty()) {
            throw std::runtime_error("save_workspace_root: empty workspace root");
        }
        config::AppConfig cfg = config::AppConfig::load(app);
        cfg.set_workspace_last_root(p);
        cfg.save(app);
    }

    void clear_workspace_root(const tonb::foundation::config::AppIdentity& app) noexcept {
        try {
            config::AppConfig cfg = config::AppConfig::load(app);
            cfg.clear_workspace_last_root();
            cfg.save(app);
        } catch (...) {
        }
    }

    fs::path load_workspace_root_if_any(const tonb::foundation::config::AppIdentity& app) {
        const config::AppConfig cfg = config::AppConfig::load(app);
        if (const auto p = cfg.workspace_last_root()) {
            return normalise_root(*p);
        }
        return {};
    }

    fs::path resolve_workspace_root_if_any(const tonb::foundation::config::AppIdentity& app) {
        if (const auto env = util::env_path(workspace_env_var_name(app))) {
            const auto p = normalise_root(*env);
            if (!p.empty()) {
                return p;
            }
        }
        return load_workspace_root_if_any(app);
    }

} // namespace tonb::foundation::workspace

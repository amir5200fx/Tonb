/**
 * @file app_config.cxx
 * @brief Implementation of minimal, versioned, per-user foundation configuration.
 */
#include <tonb/foundation/config/app_config.hxx>
#include <tonb/foundation/util/env.hxx>

#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace tonb::foundation::config {
    namespace fs = std::filesystem;

    namespace {

        std::string read_all_text_if_any(const fs::path& p) {
            std::ifstream is(p, std::ios::binary);
            if (!is) {
                return {};
            }
            std::ostringstream oss;
            oss << is.rdbuf();
            return oss.str();
        }

        void write_all_text_or_throw(const fs::path& p, const std::string& text) {
            std::ofstream os(p, std::ios::binary);
            if (!os) {
                throw std::runtime_error("AppConfig::save: cannot write: " + p.string());
            }
            os.write(text.data(), static_cast<std::streamsize>(text.size()));
            if (!os) {
                throw std::runtime_error("AppConfig::save: write failed: " + p.string());
            }
        }

        std::string json_escape(const std::string& s) {
            std::ostringstream oss;
            for (const char c : s) {
                switch (c) {
                    case '\\': oss << "\\\\"; break;
                    case '"':  oss << "\\\""; break;
                    case '\n': oss << "\\n"; break;
                    case '\r': oss << "\\r"; break;
                    case '\t': oss << "\\t"; break;
                    default:   oss << c; break;
                }
            }
            return oss.str();
        }

        std::string json_unescape_minimal(const std::string& s) {
            std::string out;
            out.reserve(s.size());
            for (std::size_t i = 0; i < s.size(); ++i) {
                const char c = s[i];
                if (c != '\\') {
                    out.push_back(c);
                    continue;
                }
                if (i + 1 >= s.size()) {
                    break;
                }
                const char n = s[++i];
                switch (n) {
                    case '\\': out.push_back('\\'); break;
                    case '"': out.push_back('"'); break;
                    case 'n': out.push_back('\n'); break;
                    case 'r': out.push_back('\r'); break;
                    case 't': out.push_back('\t'); break;
                    default: out.push_back(n); break;
                }
            }
            return out;
        }

        std::optional<std::string> extract_json_string_field(const std::string& json, const std::string& key) {
            const std::string needle = "\"" + key + "\"";
            const auto pos = json.find(needle);
            if (pos == std::string::npos) {
                return std::nullopt;
            }
            auto i = json.find(':', pos + needle.size());
            if (i == std::string::npos) {
                return std::nullopt;
            }
            ++i;
            while (i < json.size() && std::isspace(static_cast<unsigned char>(json[i]))) {
                ++i;
            }
            if (i >= json.size() || json[i] != '"') {
                return std::nullopt;
            }
            ++i;
            std::string raw;
            for (; i < json.size(); ++i) {
                const char c = json[i];
                if (c == '"') {
                    break;
                }
                if (c == '\\' && (i + 1) < json.size()) {
                    raw.push_back(c);
                    raw.push_back(json[i + 1]);
                    ++i;
                    continue;
                }
                raw.push_back(c);
            }
            return json_unescape_minimal(raw);
        }

        fs::path normalise_absolute_if_non_empty(const fs::path& p) {
            if (p.empty()) {
                return {};
            }
            fs::path out = p;
            if (out.is_relative()) {
                out = fs::absolute(out);
            }
            std::error_code ec;
            out = fs::weakly_canonical(out, ec);
            if (ec) {
                out = fs::absolute(p).lexically_normal();
            }
            return out;
        }

        fs::path normalise_relative_if_non_empty(const fs::path& p) {
            if (p.empty()) {
                return {};
            }
            if (p.is_absolute()) {
                throw std::invalid_argument("AppConfig: shell cwd must be workspace-relative");
            }
            const fs::path out = p.lexically_normal();
            if (out.is_absolute()) {
                throw std::invalid_argument("AppConfig: shell cwd must remain workspace-relative");
            }
            return out;
        }

        std::string to_json(const AppConfig& cfg) {
            std::ostringstream oss;
            oss << "{\n";
            oss << "  \"schema_version\": " << AppConfig::schema_version() << ",\n";
            oss << "  \"workspace\": {\n";
            if (const auto ws = cfg.workspace_last_root()) {
                oss << "    \"last_root\": \"" << json_escape(ws->string()) << "\"\n";
            } else {
                oss << "    \"last_root\": \"\"\n";
            }
            oss << "  },\n";
            oss << "  \"shell\": {\n";
            if (const auto cwd = cfg.shell_last_cwd()) {
                oss << "    \"last_cwd\": \"" << json_escape(cwd->generic_string()) << "\"\n";
            } else {
                oss << "    \"last_cwd\": \"\"\n";
            }
            oss << "  }\n";
            oss << "}\n";
            return oss.str();
        }

        void validate_app_identity(const AppIdentity& app) {
            if (app.app_name.empty()) {
                throw std::invalid_argument("AppIdentity: app_name is empty");
            }
            if (app.app_dir_name.empty()) {
                throw std::invalid_argument("AppIdentity: app_dir_name is empty");
            }
        }

    } // namespace

    fs::path config_root_dir(const AppIdentity& app) {
        validate_app_identity(app);
    #ifdef _WIN32
        if (const auto appdata = util::env_path("APPDATA")) {
            return *appdata / app.app_dir_name;
        }
        return fs::path(app.app_dir_name);
    #else
        if (const auto xdg = util::env_path("XDG_CONFIG_HOME")) {
            return *xdg / app.app_dir_name;
        }
        if (const auto home = util::env_path("HOME")) {
            return *home / ".config" / app.app_dir_name;
        }
        return fs::path(app.app_dir_name);
    #endif
    }

    fs::path data_root_dir(const AppIdentity& app) {
        validate_app_identity(app);
    #ifdef _WIN32
        if (const auto appdata = util::env_path("APPDATA")) {
            return *appdata / app.app_dir_name;
        }
        return fs::path(app.app_dir_name);
    #else
        if (const auto xdg = util::env_path("XDG_DATA_HOME")) {
            return *xdg / app.app_dir_name;
        }
        if (const auto home = util::env_path("HOME")) {
            return *home / ".local" / "share" / app.app_dir_name;
        }
        return fs::path(app.app_dir_name);
    #endif
    }

    fs::path AppConfig::config_path(const AppIdentity& app) {
        return config_root_dir(app) / "config.json";
    }

    AppConfig AppConfig::load(const AppIdentity& app) {
        AppConfig cfg;
        const auto p = config_path(app);
        const auto text = read_all_text_if_any(p);
        if (text.empty()) {
            return cfg;
        }
        if (const auto v = extract_json_string_field(text, "last_root")) {
            if (!v->empty()) {
                try {
                    cfg.workspace_last_root_ = normalise_absolute_if_non_empty(fs::path(*v));
                } catch (...) {
                }
            }
        }
        if (const auto v = extract_json_string_field(text, "last_cwd")) {
            if (!v->empty()) {
                try {
                    cfg.shell_last_cwd_ = normalise_relative_if_non_empty(fs::path(*v));
                } catch (...) {
                }
            }
        }
        return cfg;
    }

    void AppConfig::save(const AppIdentity& app) const {
        const auto p = config_path(app);
        fs::create_directories(p.parent_path());
        const auto tmp = p.parent_path() / (p.filename().string() + ".tmp");
        const auto json = to_json(*this);
        write_all_text_or_throw(tmp, json);
        std::error_code ec;
        fs::remove(p, ec);
        ec.clear();
        fs::rename(tmp, p, ec);
        if (ec) {
            std::error_code cleanup_ec;
            fs::remove(tmp, cleanup_ec);
            throw std::runtime_error("AppConfig::save: rename failed: " + ec.message());
        }
    }

    std::optional<fs::path> AppConfig::workspace_last_root() const {
        if (!workspace_last_root_ || workspace_last_root_->empty()) {
            return std::nullopt;
        }
        return *workspace_last_root_;
    }

    void AppConfig::set_workspace_last_root(const fs::path& root) {
        workspace_last_root_ = normalise_absolute_if_non_empty(root);
    }

    void AppConfig::clear_workspace_last_root() {
        workspace_last_root_.reset();
    }

    std::optional<fs::path> AppConfig::shell_last_cwd() const {
        if (!shell_last_cwd_ || shell_last_cwd_->empty()) {
            return std::nullopt;
        }
        return *shell_last_cwd_;
    }

    void AppConfig::set_shell_last_cwd(const fs::path& cwd) {
        shell_last_cwd_ = normalise_relative_if_non_empty(cwd);
    }

    void AppConfig::clear_shell_last_cwd() {
        shell_last_cwd_.reset();
    }

} // namespace tonb::foundation::config

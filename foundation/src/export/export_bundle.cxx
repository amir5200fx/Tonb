/**
* @file export_bundle.cxx
 * @brief Implementation of ExportBundle and Manifest deterministic.
 */
#include <tonb/foundation/export/export_bundle.hxx>

#include <stdexcept>
#include <sstream>

namespace tonb::foundation::exporting {
    namespace {
        /**
         * @brief JSON-escape a UTF-8 string minimally for safe embedding in JSON values.
         *
         * @details
         * This escape is intentionally minimal and deterministic:
         * - Escapes backslash and double quote.
         * - Escapes control characters \\n, \\r, \\t.
         *
         * @param s Input string.
         * @return Escaped string.
         */
        std::string json_escape(const std::string& s) {
            std::ostringstream oss;
            for (const char c : s) {
                switch (c) {
                    case '\\': oss << "\\\\"; break;
                    case '"':  oss << "\\\""; break;
                    case '\n': oss << "\\n"; break;
                    case '\r': oss << "\\r"; break;
                    case '\t': oss << "\\t"; break;
                    default:
                        oss << c;
                        break;
                }
            }
            return oss.str();
        }

        /**
         * @brief Return true if a relative path contains traversal escape segments ("..").
         *
         * @details
         * This is a conservative lexical check for traversal attempts.
         * It does not attempt to resolve symlinks or filesystem canonicalisation.
         *
         * @param p Path expected to be relative.
         * @return True if traversal is present, false otherwise.
         */
        bool contains_traversal(const std::filesystem::path& p) {
            for (const auto& seg : p) {
                if (seg == "..")
                    return true;
            }
            return false;
        }
    }
    // -------------------------------------------------------------------------
    // Manifest (schema v0.1)
    // -------------------------------------------------------------------------

    Manifest::Manifest() = default;

    void Manifest::set_schema_version(int v) {
        if (v < 0)
            throw std::invalid_argument("Manifest::set_schema_version: version must be non-negative");
        schema_version_ = v;
    }

    void Manifest::set_created_utc(std::string s) {
        require_non_empty(s, "Manifest::set_created_utc");
        created_utc_ = std::move(s);
    }

    void Manifest::set_tool_name(std::string s) {
        require_non_empty(s, "Manifest::set_tool_name");
        tool_name_ = std::move(s);
    }

    void Manifest::set_tool_version(std::string s) {
        require_non_empty(s, "Manifest::set_tool_version");
        tool_version_ = std::move(s);
    }

    void Manifest::set_git_commit(std::string s) {
        require_non_empty(s, "Manifest::set_git_commit");
        git_commit_ = std::move(s);
    }

    void Manifest::set_namespace(std::string s) {
        require_non_empty(s, "Manifest::set_namespace");
        ns_ = std::move(s);
    }

    void Manifest::set_command(std::string s) {
        require_non_empty(s, "Manifest::set_command");
        command_ = std::move(s);
    }

    void Manifest::set_argv(std::vector<std::string> v) {
        argv_ = std::move(v);
    }

    void Manifest::set_cwd(std::string s) {
        require_non_empty(s, "Manifest::set_cwd");
        cwd_ = std::move(s);
    }

    void Manifest::set_workspace_root(std::string s) {
        require_non_empty(s, "Manifest::set_workspace_root");
        workspace_root_ = std::move(s);
    }

    void Manifest::set_input_provenance(InputProvenance p) {
        require_non_empty(p.id, "input.id");
        require_non_empty(p.kind, "input.kind");
        input_ = std::move(p);
    }

    void Manifest::set_domain_summary(DomainSummary s) {
        require_non_empty(s.domain, "domain.domain");
        require_non_empty(s.status, "domain.status");

        // enforce unique keys deterministically
        for (std::size_t i = 0; i < s.key_values.size(); ++i) {
            require_non_empty(s.key_values[i].key, "domain.key_values.key");
            for (std::size_t j = i + 1; j < s.key_values.size(); ++j) {
                if (s.key_values[i].key == s.key_values[j].key) {
                    throw std::invalid_argument("domain.key_values contains duplicate key: " + s.key_values[i].key);
                }
            }
        }

        domain_ = std::move(s);
    }

    void Manifest::set_outputs(std::vector<ManifestOutput> outs) {
        if (outs.empty())
            throw std::invalid_argument("outputs is empty");

        for (const auto& o : outs) {
            if (o.path.empty())
                throw std::invalid_argument("outputs.path is empty");
            if (o.path.is_absolute())
                throw std::invalid_argument("outputs.path must be relative");
            if (contains_traversal(o.path))
                throw std::logic_error("outputs.path contains traversal '..'");
        }

        outputs_ = std::move(outs);
    }

    void Manifest::sync_outputs_from_bundle(const ExportBundle &bundle) {
        std::vector<ManifestOutput> outs;
        outs.reserve(bundle.outputs().size());

        for (const auto& o : bundle.outputs()) {
            ManifestOutput mo;
            mo.path = o.path;
            mo.kind = o.kind;
            mo.description = o.description;
            mo.bytes = o.bytes;
            mo.sha256 = o.sha256;
            outs.push_back(std::move(mo));
        }

        set_outputs(std::move(outs));
    }

    void Manifest::add_extension(Extension e) {
        require_non_empty(e.key, "extensions.key");
        require_non_empty(e.value_json, "extensions.value_json");

        for (const auto& ex : extensions_) {
            if (ex.key == e.key)
                throw std::logic_error("extensions already contains key: " + e.key);
        }
        extensions_.push_back(std::move(e));
    }

    std::string Manifest::to_json() const {
        validate();

        // Fixed key order for deterministic output (schema v0.1).
        std::ostringstream oss;
        oss << "{\n";

        // 1) schema_version (wire value is string "0.1")
        oss << R"(  "schema_version": ")" << json_escape(schema_version_string()) << "\",\n";

        // 2) created_utc
        oss << R"(  "created_utc": ")" << json_escape(created_utc_) << "\",\n";

        // 3) tool
        oss << "  \"tool\": {\n";
        oss << R"(    "name": ")" << json_escape(tool_name_) << "\",\n";
        oss << R"(    "version": ")" << json_escape(tool_version_) << "\",\n";
        oss << R"(    "git_commit": ")" << json_escape(git_commit_) << "\"\n";
        oss << "  },\n";

        // 4) context
        oss << "  \"context\": {\n";
        oss << R"(    "namespace": ")" << json_escape(ns_) << "\",\n";
        oss << R"(    "command": ")" << json_escape(command_) << "\",\n";
        oss << "    \"argv\": [";
        for (std::size_t i = 0; i < argv_.size(); ++i) {
            if (i) oss << ", ";
            oss << "\"" << json_escape(argv_[i]) << "\"";
        }
        oss << "],\n";
        oss << R"(    "cwd": ")" << json_escape(cwd_) << "\",\n";
        oss << R"(    "workspace_root": ")" << json_escape(workspace_root_) << "\"\n";
        oss << "  },\n";

        // 5) input provenance
        oss << "  \"input\": {\n";
        oss << R"(    "id": ")" << json_escape(input_->id) << "\",\n";
        oss << R"(    "kind": ")" << json_escape(input_->kind) << "\",\n";
        oss << R"(    "sha256": ")" << json_escape(input_->sha256.value_or("")) << "\",\n";
        oss << "    \"bytes\": " << (input_->bytes ? std::to_string(*input_->bytes) : "null") << ",\n";
        oss << R"(    "note": ")" << json_escape(input_->note) << "\"\n";
        oss << "  },\n";

        // 6) domain state summary
        oss << "  \"domain\": {\n";
        oss << R"(    "domain": ")" << json_escape(domain_->domain) << "\",\n";
        oss << R"(    "status": ")" << json_escape(domain_->status) << "\",\n";
        oss << "    \"summary_lines\": [";
        for (std::size_t i = 0; i < domain_->summary_lines.size(); ++i) {
            if (i) oss << ", ";
            oss << "\"" << json_escape(domain_->summary_lines[i]) << "\"";
        }
        oss << "],\n";
        oss << "    \"key_values\": [";
        for (std::size_t i = 0; i < domain_->key_values.size(); ++i) {
            if (i) oss << ", ";
            oss << "{"
                << R"("key":")" << json_escape(domain_->key_values[i].key) << "\","
                << R"("value":")" << json_escape(domain_->key_values[i].value) << "\""
                << "}";
        }
        oss << "]\n";
        oss << "  },\n";

        // 7) outputs
        oss << "  \"outputs\": [\n";
        for (std::size_t i = 0; i < outputs_.size(); ++i) {
            const auto& o = outputs_[i];
            oss << "    {\n";
            oss << R"(      "path": ")" << json_escape(o.path.generic_string()) << "\",\n";
            oss << R"(      "kind": ")" << json_escape(kind_to_string(o.kind)) << "\",\n";
            oss << R"(      "description": ")" << json_escape(o.description) << "\",\n";
            oss << "      \"bytes\": " << (o.bytes ? std::to_string(*o.bytes) : "null") << ",\n";
            oss << R"(      "sha256": ")" << json_escape(o.sha256.value_or("")) << "\"\n";
            oss << "    }" << (i + 1 < outputs_.size() ? "," : "") << "\n";
        }
        oss << "  ],\n";

        // 8) extensions (deterministic insertion order)
        oss << "  \"extensions\": {\n";
        for (std::size_t i = 0; i < extensions_.size(); ++i) {
            const auto& e = extensions_[i];
            oss << "    \"" << json_escape(e.key) << "\": " << e.value_json
                << (i + 1 < extensions_.size() ? "," : "") << "\n";
        }
        oss << "  }\n";

        oss << "}\n";
        return oss.str();
    }

    void Manifest::validate() const {
        if (created_utc_.empty())
            throw std::logic_error("Manifest: created_utc is missing");

        require_non_empty(tool_name_, "tool.name");
        require_non_empty(tool_version_, "tool.version");
        require_non_empty(git_commit_, "tool.git_commit");

        require_non_empty(ns_, "context.namespace");
        require_non_empty(command_, "context.command");
        require_non_empty(cwd_, "context.cwd");
        require_non_empty(workspace_root_, "context.workspace_root");

        if (!input_.has_value())
            throw std::logic_error("Manifest: input provenance is missing");
        if (!domain_.has_value())
            throw std::logic_error("Manifest: domain summary is missing");
        if (outputs_.empty())
            throw std::logic_error("Manifest: outputs list is missing");

        // extensions uniqueness already enforced in add_extension
    }

    void Manifest::require_non_empty(const std::string_view v, const std::string_view what) {
        if (v.empty())
            throw std::invalid_argument(std::string(what) + " is empty");
    }

    bool Manifest::contains_traversal(const std::filesystem::path &p) {
        return ::tonb::foundation::exporting::contains_traversal(p);
    }

    std::string Manifest::kind_to_string(OutputKind k) {
        switch (k) {
            case OutputKind::vtk_polydata: return "vtk_polydata";
            case OutputKind::vtk_unstructured_grid: return "vtk_unstructured_grid";
            case OutputKind::abaqus_inp: return "abaqus_inp";
            case OutputKind::json: return "json";
            case OutputKind::csv: return "csv";
            case OutputKind::txt: return "txt";
            default: return "unknown";
        }
    }

    // -------------------------------------------------------------------------
    // ExportBundle
    // -------------------------------------------------------------------------

    ExportBundle::ExportBundle(BundleKind kind, std::filesystem::path root)
        : kind_(kind), root_(std::move(root)) {
        validate();
    }

    void ExportBundle::add_output(OutputFile out) {
        if (out.path.empty())
            throw std::invalid_argument("ExportBundle: output path is empty");
        if (out.path.is_absolute())
            throw std::invalid_argument("ExportBundle: output path must be relative");
        if (contains_traversal(out.path))
            throw std::logic_error("ExportBundle: output path contains traversal '..'");

        outputs_.push_back(std::move(out));
    }

    void ExportBundle::validate() const {
        if (root_.empty())
            throw std::invalid_argument("ExportBundle: root is empty");
        if (!root_.is_absolute())
            throw std::invalid_argument("ExportBundle: root must be absolute");

        for (const auto& o : outputs_) {
            if (o.path.empty())
                throw std::logic_error("ExportBundle: output path is empty");
            if (o.path.is_absolute())
                throw std::logic_error("ExportBundle: output path must be relative");
            if (contains_traversal(o.path))
                throw std::logic_error("ExportBundle: output path contains traversal '..'");
        }
    }

    BundleWritePlan make_write_plan(const std::filesystem::path &final_root, std::string_view token) {
        if (final_root.empty())
            throw std::invalid_argument("make_write_plan: final_root is empty");
        if (!final_root.is_absolute())
            throw std::invalid_argument("make_write_plan: final_root must be absolute");
        if (token.empty())
            throw std::invalid_argument("make_write_plan: token is empty");

        BundleWritePlan plan;
        plan.final_root = final_root.lexically_normal();

        std::filesystem::path staging = plan.final_root;
        staging += ".tmp.";
        staging += std::string(token);

        plan.staging_root = staging.lexically_normal();
        return plan;
    }
}
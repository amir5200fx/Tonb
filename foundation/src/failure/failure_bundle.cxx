/**
 * @file failure_bundle.cxx
 * @brief Implementation of deterministic failure-bundle serialisation.
 */
#include <tonb/foundation/failure/failure_bundle.hxx>

#include <sstream>
#include <stdexcept>

namespace tonb::foundation::failure {
    namespace {

        std::string json_escape(const std::string_view value) {
            std::string out;
            out.reserve(value.size() + 8);
            for (const char c : value) {
                switch (c) {
                    case '"': out += "\\\""; break;
                    case '\\': out += "\\\\"; break;
                    case '\b': out += "\\b"; break;
                    case '\f': out += "\\f"; break;
                    case '\n': out += "\\n"; break;
                    case '\r': out += "\\r"; break;
                    case '\t': out += "\\t"; break;
                    default:
                        if (static_cast<unsigned char>(c) < 0x20u) {
                            std::ostringstream oss;
                            oss << "\\u" << std::hex << std::uppercase << int(static_cast<unsigned char>(c));
                            out += oss.str();
                        } else {
                            out.push_back(c);
                        }
                }
            }
            return out;
        }

        std::string q(const std::string_view value) {
            return '"' + json_escape(value) + '"';
        }

        std::string q_or_null(const std::optional<std::string>& value) {
            return value.has_value() ? q(*value) : "null";
        }

        std::string json_bool(const bool value) {
            return value ? "true" : "false";
        }

        std::string spaces(const int n) {
            return std::string(static_cast<std::size_t>(n > 0 ? n : 0), ' ');
        }

        struct JsonBuilder {
            const FailureJsonOptions opt;

            [[nodiscard]] std::string indent(const int level) const {
                return opt.pretty ? spaces(level * opt.indent_spaces) : std::string();
            }

            [[nodiscard]] std::string nl() const { return opt.pretty ? "\n" : std::string(); }
            [[nodiscard]] std::string sep() const { return opt.pretty ? " " : std::string(); }
        };

        std::string to_json_array(const DiagnosticFields& values, const JsonBuilder& jb, const int level) {
            std::string s = "[";
            if (!values.empty()) {
                s += jb.nl();
                for (std::size_t i = 0; i < values.size(); ++i) {
                    const auto& v = values[i];
                    s += jb.indent(level + 1) + "{" + jb.nl();
                    s += jb.indent(level + 2) + q("key") + ":" + jb.sep() + q(v.key) + "," + jb.nl();
                    s += jb.indent(level + 2) + q("value") + ":" + jb.sep() + q(v.value) + jb.nl();
                    s += jb.indent(level + 1) + "}";
                    if (i + 1 != values.size()) {
                        s += ",";
                    }
                    s += jb.nl();
                }
                s += jb.indent(level);
            }
            s += "]";
            return s;
        }

        std::string to_json_array(const FailureCauses& values, const JsonBuilder& jb, const int level) {
            std::string s = "[";
            if (!values.empty()) {
                s += jb.nl();
                for (std::size_t i = 0; i < values.size(); ++i) {
                    const auto& v = values[i];
                    s += jb.indent(level + 1) + "{" + jb.nl();
                    s += jb.indent(level + 2) + q("type") + ":" + jb.sep() + q(v.type) + "," + jb.nl();
                    s += jb.indent(level + 2) + q("message") + ":" + jb.sep() + q(v.message) + "," + jb.nl();
                    s += jb.indent(level + 2) + q("code") + ":" + jb.sep() + q_or_null(v.code) + "," + jb.nl();
                    s += jb.indent(level + 2) + q("diagnostics") + ":" + jb.sep() + to_json_array(v.diagnostics, jb, level + 2) + jb.nl();
                    s += jb.indent(level + 1) + "}";
                    if (i + 1 != values.size()) {
                        s += ",";
                    }
                    s += jb.nl();
                }
                s += jb.indent(level);
            }
            s += "]";
            return s;
        }

        std::string to_json_array(const std::vector<std::string>& values, const JsonBuilder& jb, const int level) {
            std::string s = "[";
            if (!values.empty()) {
                s += jb.nl();
                for (std::size_t i = 0; i < values.size(); ++i) {
                    s += jb.indent(level + 1) + q(values[i]);
                    if (i + 1 != values.size()) {
                        s += ",";
                    }
                    s += jb.nl();
                }
                s += jb.indent(level);
            }
            s += "]";
            return s;
        }

    } // namespace

    std::string to_json(const FailureBundleMetadata& metadata, const FailureJsonOptions& opt) {
        JsonBuilder jb{opt};
        std::string s = "{" + jb.nl();
        s += jb.indent(1) + q("bundle_schema") + ":" + jb.sep() + q(metadata.bundle_schema) + "," + jb.nl();
        s += jb.indent(1) + q("application") + ":" + jb.sep() + q(metadata.application) + "," + jb.nl();
        s += jb.indent(1) + q("application_version") + ":" + jb.sep() + q_or_null(metadata.application_version) + "," + jb.nl();
        s += jb.indent(1) + q("run_id") + ":" + jb.sep() + q(metadata.run_id) + "," + jb.nl();
        s += jb.indent(1) + q("sequence") + ":" + jb.sep() + std::to_string(metadata.sequence) + "," + jb.nl();
        s += jb.indent(1) + q("code") + ":" + jb.sep() + q(metadata.code) + "," + jb.nl();
        s += jb.indent(1) + q("kind") + ":" + jb.sep() + q(to_string(metadata.kind)) + "," + jb.nl();
        s += jb.indent(1) + q("severity") + ":" + jb.sep() + q(to_string(metadata.severity)) + "," + jb.nl();
        s += jb.indent(1) + q("domain") + ":" + jb.sep() + q(metadata.domain) + "," + jb.nl();
        s += jb.indent(1) + q("created_utc") + ":" + jb.sep() + q(metadata.created_utc) + "," + jb.nl();
        s += jb.indent(1) + q("message") + ":" + jb.sep() + q(metadata.message) + "," + jb.nl();
        s += jb.indent(1) + q("exception_type") + ":" + jb.sep() + q_or_null(metadata.exception_type) + "," + jb.nl();
        s += jb.indent(1) + q("correlation_id") + ":" + jb.sep() + q_or_null(metadata.correlation_id) + jb.nl();
        s += "}";
        return s;
    }

    std::string to_json(const FailureContext& context, const FailureJsonOptions& opt) {
        JsonBuilder jb{opt};
        std::string s = "{" + jb.nl();
        s += jb.indent(1) + q("operation") + ":" + jb.sep() + q(context.operation) + "," + jb.nl();
        s += jb.indent(1) + q("args") + ":" + jb.sep() + to_json_array(context.args, jb, 1) + "," + jb.nl();
        s += jb.indent(1) + q("cwd") + ":" + jb.sep() + q_or_null(context.cwd) + "," + jb.nl();
        s += jb.indent(1) + q("workspace_root") + ":" + jb.sep() + q_or_null(context.workspace_root) + "," + jb.nl();
        s += jb.indent(1) + q("correlation_id") + ":" + jb.sep() + q_or_null(context.correlation_id) + "," + jb.nl();
        s += jb.indent(1) + q("diagnostics") + ":" + jb.sep() + to_json_array(context.diagnostics, jb, 1) + jb.nl();
        s += "}";
        return s;
    }

    std::string to_json(const FailureBundleEnvironment& environment, const FailureJsonOptions& opt) {
        JsonBuilder jb{opt};
        std::string s = "{" + jb.nl();
        s += jb.indent(1) + q("operating_system") + ":" + jb.sep() + q_or_null(environment.operating_system) + "," + jb.nl();
        s += jb.indent(1) + q("build_type") + ":" + jb.sep() + q_or_null(environment.build_type) + "," + jb.nl();
        s += jb.indent(1) + q("compiler") + ":" + jb.sep() + q_or_null(environment.compiler) + "," + jb.nl();
        s += jb.indent(1) + q("host") + ":" + jb.sep() + q_or_null(environment.host) + "," + jb.nl();
        s += jb.indent(1) + q("process_id") + ":" + jb.sep() + (environment.process_id ? std::to_string(*environment.process_id) : std::string("null")) + "," + jb.nl();
        s += jb.indent(1) + q("thread_id") + ":" + jb.sep() + q_or_null(environment.thread_id) + "," + jb.nl();
        s += jb.indent(1) + q("diagnostics") + ":" + jb.sep() + to_json_array(environment.diagnostics, jb, 1) + jb.nl();
        s += "}";
        return s;
    }

    std::string to_json(const FailureArtefact& artefact, const FailureJsonOptions& opt) {
        JsonBuilder jb{opt};
        std::string s = "{" + jb.nl();
        s += jb.indent(1) + q("relative_path") + ":" + jb.sep() + q(artefact.relative_path) + "," + jb.nl();
        s += jb.indent(1) + q("description") + ":" + jb.sep() + q_or_null(artefact.description) + "," + jb.nl();
        s += jb.indent(1) + q("content_type") + ":" + jb.sep() + q_or_null(artefact.content_type) + "," + jb.nl();
        s += jb.indent(1) + q("required") + ":" + jb.sep() + json_bool(artefact.required) + jb.nl();
        s += "}";
        return s;
    }

    std::string to_json(const FailureBundle& bundle, const FailureJsonOptions& opt) {
        JsonBuilder jb{opt};
        std::string s = "{" + jb.nl();
        s += jb.indent(1) + q("metadata") + ":" + jb.sep() + to_json(bundle.metadata, opt) + "," + jb.nl();
        s += jb.indent(1) + q("context") + ":" + jb.sep() + to_json(bundle.context, opt) + "," + jb.nl();
        s += jb.indent(1) + q("environment") + ":" + jb.sep() + to_json(bundle.environment, opt) + "," + jb.nl();
        s += jb.indent(1) + q("diagnostics") + ":" + jb.sep() + to_json_array(bundle.diagnostics, jb, 1) + "," + jb.nl();
        s += jb.indent(1) + q("causes") + ":" + jb.sep() + to_json_array(bundle.causes, jb, 1) + "," + jb.nl();
        s += jb.indent(1) + q("artefacts") + ":" + jb.sep() + "[";
        if (!bundle.artefacts.empty()) {
            s += jb.nl();
            for (std::size_t i = 0; i < bundle.artefacts.size(); ++i) {
                s += jb.indent(2) + to_json(bundle.artefacts[i], opt);
                if (i + 1 != bundle.artefacts.size()) {
                    s += ",";
                }
                s += jb.nl();
            }
            s += jb.indent(1);
        }
        s += "]" + jb.nl();
        s += "}";
        return s;
    }

    FailureBundle make_bundle_from_event(
        const FailureEvent& event,
        std::string application,
        std::optional<std::string> application_version,
        std::string run_id,
        const std::uint32_t sequence,
        const FailurePolicy policy,
        FailureBundleEnvironment environment) {
        if (!is_valid_domain_token(event.domain)) {
            throw std::invalid_argument("make_bundle_from_event: invalid event domain");
        }
        if (application.empty()) {
            throw std::invalid_argument("make_bundle_from_event: application must not be empty");
        }
        FailureBundle bundle;
        bundle.metadata.application = std::move(application);
        bundle.metadata.application_version = std::move(application_version);
        bundle.metadata.run_id = std::move(run_id);
        bundle.metadata.sequence = sequence;
        bundle.metadata.code = event.code.value();
        bundle.metadata.kind = event.kind;
        bundle.metadata.severity = event.severity;
        bundle.metadata.domain = event.domain;
        bundle.metadata.created_utc = event.created_utc.empty() ? current_utc_timestamp() : event.created_utc;
        bundle.metadata.message = policy.redact_paths ? redact_paths_copy(event.message) : event.message;
        bundle.metadata.exception_type = event.exception_type;
        bundle.metadata.correlation_id = event.correlation_id;

        bundle.context = event.context;
        bundle.environment = std::move(environment);
        if (policy.redact_paths) {
            if (bundle.context.cwd) {
                bundle.context.cwd = redact_paths_copy(*bundle.context.cwd);
            }
            if (bundle.context.workspace_root) {
                bundle.context.workspace_root = redact_paths_copy(*bundle.context.workspace_root);
            }
            for (auto& d : bundle.context.diagnostics) {
                d.value = redact_paths_copy(d.value);
            }
        }
        bundle.diagnostics = event.diagnostics;
        if (policy.redact_paths) {
            for (auto& d : bundle.diagnostics) {
                d.value = redact_paths_copy(d.value);
            }
            if (bundle.environment.host) {
                bundle.environment.host = "<redacted-host>";
            }
        }
        bundle.causes = event.causes;
        if (policy.redact_paths) {
            for (auto& cause : bundle.causes) {
                cause.message = redact_paths_copy(cause.message);
                for (auto& d : cause.diagnostics) {
                    d.value = redact_paths_copy(d.value);
                }
            }
        }
        return bundle;
    }

} // namespace tonb::foundation::failure

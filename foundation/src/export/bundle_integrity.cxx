//
// Created by amir on 05/03/2026.
//
#include <tonb/foundation/export/bundle_integrity.hxx>

#include <tonb/foundation/export/sha256.hxx>

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace tonb::foundation::exporting {
    namespace {
        std::filesystem::path to_payload_abs(const std::filesystem::path& payload_root,
                                             const std::filesystem::path& rel) {
            return (payload_root / rel).lexically_normal();
        }

        void require_abs_root(const std::filesystem::path& p, const char* what) {
            if (p.empty())
                throw std::invalid_argument(std::string(what) + " is empty");
            if (!p.is_absolute())
                throw std::invalid_argument(std::string(what) + " must be absolute");
        }

        std::string json_escape(std::string_view s) {
            std::ostringstream oss;
            for (const auto ch : s) {
                switch (ch) {
                    case '\\': oss << "\\\\"; break;
                    case '"':  oss << "\\\""; break;
                    case '\n': oss << "\\n"; break;
                    case '\r': oss << "\\r"; break;
                    case '\t': oss << "\\t"; break;
                    default:
                        if (static_cast<unsigned char>(ch) < 0x20u) {
                            oss << "\\u";
                            oss << std::hex << std::uppercase;
                            oss.width(4);
                            oss.fill('0');
                            oss << (static_cast<int>(static_cast<unsigned char>(ch)));
                            oss << std::dec;
                        } else {
                            oss << ch;
                        }
                }
            }
            return oss.str();
        }
    }

    void compute_output_integrity_metadata(ExportBundle &bundle, const std::filesystem::path &payload_root) {
        require_abs_root(payload_root, "compute_output_integrity_metadata: payload_root");
        bundle.validate();

        auto& outs = bundle.outputs_mut();
        for (auto& o : outs) {
            const auto abs_path = to_payload_abs(payload_root, o.path);
            if (!std::filesystem::exists(abs_path))
                throw std::runtime_error("compute_output_integrity_metadata: payload file does not exist");

            const auto bytes = std::filesystem::file_size(abs_path);
            const auto hash = sha256_hex_file(abs_path);

            o.bytes = static_cast<std::uint64_t>(bytes);
            o.sha256 = hash;
        }
    }

    std::string bundle_aggregate_sha256(const ExportBundle &bundle) {
        bundle.validate();

        std::string canonical;
        // Conservative reserve to avoid repeated reallocations.
        canonical.reserve(bundle.outputs().size() * 128u);

        for (const auto& o : bundle.outputs()) {
            if (!o.sha256.has_value())
                throw std::logic_error("bundle_aggregate_sha256: missing OutputFile.sha256");
            if (!o.bytes.has_value())
                throw std::logic_error("bundle_aggregate_sha256: missing OutputFile.bytes");

            canonical += o.path.generic_string();
            canonical += "\n";
            canonical += *o.sha256;
            canonical += "\n";
            canonical += std::to_string(*o.bytes);
            canonical += "\n";
        }

        const auto* p = reinterpret_cast<const std::uint8_t*>(canonical.data());
        return sha256_hex(p, canonical.size());
    }

    std::string make_bundle_integrity_extension_json(std::string_view bundle_sha256) {
        if (bundle_sha256.empty())
            throw std::invalid_argument("make_bundle_integrity_extension_json: bundle_sha256 is empty");

        // Fixed key order for deterministic output.
        std::ostringstream oss;
        oss << "{";
        oss << "\"algorithm\":\"SHA-256\",";
        oss << "\"bundle_sha256\":\"" << json_escape(bundle_sha256) << "\",";
        oss << "\"aggregate_rule\":\"sha256(concat(path\\nsha256\\nbytes\\n...))\"";
        oss << "}";
        return oss.str();
    }
}
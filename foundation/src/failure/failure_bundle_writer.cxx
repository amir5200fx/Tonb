/**
 * @file failure_bundle_writer.cxx
 * @brief Implementation of atomic failure-bundle writing.
 */
#include <tonb/foundation/failure/failure_bundle_writer.hxx>
#include <tonb/foundation/failure/failure_artefact_matrix.hxx>

#include <fstream>
#include <iomanip>
#include <set>
#include <sstream>
#include <stdexcept>
#include <system_error>

namespace tonb::foundation::failure {
    namespace {

        bool is_absolute_dir(const std::filesystem::path& p) {
            return !p.empty() && p.is_absolute();
        }

        bool is_safe_relative_path(const std::filesystem::path& p) {
            if (p.empty() || p.is_absolute()) {
                return false;
            }
            for (const auto& part : p) {
                if (part == "..") {
                    return false;
                }
            }
            return true;
        }

        void remove_all_nothrow(const std::filesystem::path& p) noexcept {
            try {
                std::error_code ec;
                std::filesystem::remove_all(p, ec);
            } catch (...) {
            }
        }

        void ensure_parent_dir_or_throw(const std::filesystem::path& abs_file_path) {
            const auto parent = abs_file_path.parent_path();
            if (!parent.empty()) {
                std::error_code ec;
                std::filesystem::create_directories(parent, ec);
                if (ec) {
                    throw std::runtime_error("FailureBundleWriter: failed to create parent directory");
                }
            }
        }

        void write_text_file_or_throw(const std::filesystem::path& abs_path, const std::string& content) {
            ensure_parent_dir_or_throw(abs_path);
            std::ofstream ofs(abs_path, std::ios::binary);
            if (!ofs) {
                throw std::runtime_error("FailureBundleWriter: failed to open file for write");
            }
            ofs.write(content.data(), static_cast<std::streamsize>(content.size()));
            if (!ofs) {
                throw std::runtime_error("FailureBundleWriter: failed to write file");
            }
        }

        std::uint64_t file_size_or_throw(const std::filesystem::path& path) {
            std::error_code ec;
            const auto size = std::filesystem::file_size(path, ec);
            if (ec) {
                throw std::runtime_error("FailureBundleWriter: failed to measure file size");
            }
            return static_cast<std::uint64_t>(size);
        }

        std::string zero_pad(const std::uint32_t value) {
            std::ostringstream oss;
            oss << std::setw(6) << std::setfill('0') << value;
            return oss.str();
        }

        const FailurePayloadWriteFn* find_payload(const std::vector<FailurePayloadItem>& items, const std::size_t artefact_index) {
            for (const auto& item : items) {
                if (item.artefact_index == artefact_index) {
                    return &item.write;
                }
            }
            return nullptr;
        }

        void validate_payload_mapping_or_throw(const std::size_t artefact_count, const std::vector<FailurePayloadItem>& items) {
            std::set<std::size_t> seen;
            for (const auto& item : items) {
                if (item.artefact_index >= artefact_count) {
                    throw std::invalid_argument("FailureBundleWriter: payload artefact index out of range");
                }
                if (!seen.insert(item.artefact_index).second) {
                    throw std::invalid_argument("FailureBundleWriter: duplicate payload artefact index");
                }
            }
        }

    } // namespace

    std::filesystem::path FailureBundleWriter::make_final_root(
        const std::filesystem::path& failure_root,
        const std::string_view run_id,
        const std::uint32_t sequence,
        const std::string_view code) {
        if (!is_absolute_dir(failure_root)) {
            throw std::invalid_argument("FailureBundleWriter: failure_root must be absolute");
        }
        if (run_id.empty() || code.empty() || sequence < 1) {
            throw std::invalid_argument("FailureBundleWriter: invalid final-root inputs");
        }
        const auto run_dir = (failure_root / ("run_" + std::string(run_id))).lexically_normal();
        return (run_dir / ("bundle_" + zero_pad(sequence) + "_" + std::string(code))).lexically_normal();
    }

    FailureWriteResult FailureBundleWriter::write_bundle_noexcept(
        const std::filesystem::path& failure_root,
        const FailureBundle& bundle,
        const std::vector<FailurePayloadItem>& artefact_payloads,
        const FailurePolicy& policy) noexcept {
        FailureWriteResult result;
        try {
            if (!is_absolute_dir(failure_root)) {
                throw std::invalid_argument("FailureBundleWriter: failure_root must be an absolute path");
            }
            if (bundle.metadata.run_id.empty() || bundle.metadata.sequence < 1 || bundle.metadata.code.empty()) {
                throw std::invalid_argument("FailureBundleWriter: bundle metadata is incomplete");
            }
            validate_payload_mapping_or_throw(bundle.artefacts.size(), artefact_payloads);

            for (const auto& artefact : bundle.artefacts) {
                if (!is_safe_relative_path(std::filesystem::path(artefact.relative_path))) {
                    throw std::invalid_argument("FailureBundleWriter: artefact path must be safe and relative");
                }
            }

            for (const auto name : required_artefact_names(bundle.metadata.kind)) {
                bool found = false;
                for (std::size_t i = 0; i < bundle.artefacts.size(); ++i) {
                    if (bundle.artefacts[i].relative_path == name) {
                        found = true;
                        if (find_payload(artefact_payloads, i) == nullptr) {
                            throw std::logic_error("FailureBundleWriter: missing payload for required artefact");
                        }
                        break;
                    }
                }
                if (!found) {
                    throw std::logic_error("FailureBundleWriter: missing required artefact declaration");
                }
            }

            result.final_root = make_final_root(
                failure_root,
                bundle.metadata.run_id,
                bundle.metadata.sequence,
                bundle.metadata.code);
            result.staging_root = (result.final_root.string() + ".staging");

            if (std::filesystem::exists(result.final_root)) {
                throw std::logic_error("FailureBundleWriter: final bundle root already exists");
            }
            if (std::filesystem::exists(result.staging_root)) {
                remove_all_nothrow(result.staging_root);
            }

            std::error_code ec;
            std::filesystem::create_directories(result.staging_root, ec);
            if (ec) {
                throw std::runtime_error("FailureBundleWriter: failed to create staging root");
            }

            const auto metadata_path = result.staging_root / "metadata.json";
            const auto context_path = result.staging_root / "context.json";
            const auto environment_path = result.staging_root / "environment.json";
            const auto diagnostics_path = result.staging_root / "diagnostics.json";
            const auto causes_path = result.staging_root / "causes.json";

            write_text_file_or_throw(metadata_path, to_json(bundle.metadata));
            write_text_file_or_throw(context_path, to_json(bundle.context));
            write_text_file_or_throw(environment_path, to_json(bundle.environment));

            {
                FailureBundle only_diag;
                only_diag.diagnostics = bundle.diagnostics;
                write_text_file_or_throw(diagnostics_path, to_json(bundle));
            }
            {
                FailureBundle only_causes;
                only_causes.causes = bundle.causes;
                write_text_file_or_throw(causes_path, to_json(bundle));
            }

            std::uint64_t total_bytes = 0;
            for (const auto& p : {metadata_path, context_path, environment_path, diagnostics_path, causes_path}) {
                total_bytes += file_size_or_throw(p);
            }

            for (std::size_t i = 0; i < bundle.artefacts.size(); ++i) {
                const auto* writer = find_payload(artefact_payloads, i);
                const auto& artefact = bundle.artefacts[i];
                const auto abs_dst = (result.staging_root / "artefacts" / artefact.relative_path).lexically_normal();

                if (writer == nullptr) {
                    if (artefact.required || is_required_artefact(bundle.metadata.kind, artefact.relative_path)) {
                        throw std::logic_error("FailureBundleWriter: missing writer for required artefact");
                    }
                    continue;
                }

                ensure_parent_dir_or_throw(abs_dst);
                (*writer)(abs_dst);
                if (!std::filesystem::exists(abs_dst)) {
                    throw std::runtime_error("FailureBundleWriter: payload callback did not create file");
                }
                const auto file_size = file_size_or_throw(abs_dst);
                if (policy.max_file_bytes && file_size > *policy.max_file_bytes) {
                    throw std::runtime_error("FailureBundleWriter: artefact exceeds per-file size cap");
                }
                total_bytes += file_size;
                if (total_bytes > policy.max_total_bytes) {
                    throw std::runtime_error("FailureBundleWriter: bundle exceeds total size cap");
                }
            }

            std::filesystem::rename(result.staging_root, result.final_root, ec);
            if (ec) {
                throw std::runtime_error("FailureBundleWriter: failed to promote staging bundle");
            }

            result.ok = true;
            result.total_bytes = total_bytes;
        } catch (const std::exception& ex) {
            result.ok = false;
            result.error = ex.what();
            remove_all_nothrow(result.staging_root);
        } catch (...) {
            result.ok = false;
            result.error = "FailureBundleWriter: unknown failure";
            remove_all_nothrow(result.staging_root);
        }
        return result;
    }

} // namespace tonb::foundation::failure

/**
* @file atomic_bundle_writer.cxx
 * @brief Implementation of atomic export bundle writer.
 */

#include <tonb/foundation/export/atomic_bundle_writer.hxx>

#include <tonb/foundation/export/bundle_integrity.hxx>
#include <tonb/foundation/export/sha256.hxx>

#include <fstream>
#include <stdexcept>

namespace tonb::foundation::exporting {
    namespace {
        /**
         * @brief Build absolute staging path for a bundle-relative output.
         *
         * @param staging_root Absolute staging root directory.
         * @param rel Relative path inside bundle.
         * @return Absolute destination path.
         */
        std::filesystem::path to_staging_abs(const std::filesystem::path& staging_root, const std::filesystem::path& rel) {
            return (staging_root / rel).lexically_normal();
        }

        /**
         * @brief Return true if two paths are on the same filesystem root.
         *
         * @details
         * This is a conservative check for preventing cross-filesystem rename issues.
         * - On Windows: compare root_name (drive) and root_directory.
         * - On POSIX: compare root_directory ("/") only.
         */
        bool same_filesystem_root(const std::filesystem::path& a, const std::filesystem::path& b) {
            const auto an = a.root_name().string();
            const auto bn = b.root_name().string();
            if (an != bn)
                return false;

            const auto ad = a.root_directory().string();
            const auto bd = b.root_directory().string();
            return ad == bd;
        }
    }


    void AtomicBundleWriter::write_bundle_atomic(ExportBundle &bundle, const BundleWritePlan &plan,
        const std::vector<PayloadItem> &payloads, const Options &opt) {
        // ---- Validate plan and bundle roots
        if (plan.final_root.empty() || plan.staging_root.empty())
            throw std::invalid_argument("AtomicBundleWriter: plan roots are empty");
        if (!plan.final_root.is_absolute() || !plan.staging_root.is_absolute())
            throw std::invalid_argument("AtomicBundleWriter: plan roots must be absolute");

        if (bundle.root() != plan.final_root.lexically_normal())
            throw std::invalid_argument("AtomicBundleWriter: bundle.root must equal plan.final_root");

        if (!same_filesystem_root(plan.final_root, plan.staging_root))
            throw std::invalid_argument("AtomicBundleWriter: staging and final must share filesystem root");

        // Refuse to overwrite existing final root (professional safety default).
        if (opt.refuse_if_final_exists && std::filesystem::exists(plan.final_root)) {
            throw std::logic_error("AtomicBundleWriter: final bundle root already exists");
        }

        // ---- Ensure staging does not already exist
        if (std::filesystem::exists(plan.staging_root)) {
            throw std::logic_error("AtomicBundleWriter: staging root already exists");
        }

        // ---- Validate payload mapping completeness and uniqueness
        const auto n_out = bundle.outputs().size();
        if (n_out == 0)
            throw std::logic_error("AtomicBundleWriter: bundle has no outputs");

        std::vector<bool> has_writer(n_out, false);
        for (const auto& item : payloads) {
            if (item.output_index >= n_out)
                throw std::invalid_argument("AtomicBundleWriter: payload output_index out of range");
            if (!item.write)
                throw std::invalid_argument("AtomicBundleWriter: payload write callback is null");
            if (has_writer[item.output_index])
                throw std::invalid_argument("AtomicBundleWriter: duplicate payload mapping for an output_index");
            has_writer[item.output_index] = true;
        }
        for (std::size_t i = 0; i < n_out; ++i) {
            if (!has_writer[i])
                throw std::logic_error("AtomicBundleWriter: missing payload writer for an output");
        }

        // ---- Lifecycle with cleanup on failure
        try {
            // 1) Create staging directory
            std::error_code ec;
            std::filesystem::create_directories(plan.staging_root, ec);
            if (ec)
                throw std::runtime_error("AtomicBundleWriter: failed to create staging root");

            // 2) Write payload files (deterministic order: output index ascending)
            for (std::size_t i = 0; i < n_out; ++i) {
                const auto& out = bundle.outputs()[i];

                const auto abs_dst = to_staging_abs(plan.staging_root, out.path);
                ensure_parent_dir(abs_dst);

                // Find the writer for i
                for (const auto& item : payloads) {
                    if (item.output_index == i) {
                        item.write(abs_dst);
                        break;
                    }
                }

                if (!std::filesystem::exists(abs_dst))
                    throw std::runtime_error("AtomicBundleWriter: payload writer did not produce file");
            }

            // 3) Compute file hashes + sizes (optional)
            if (opt.compute_integrity) {
                compute_integrity_metadata(bundle, plan.staging_root);
            }

            // 4) Write manifest.json LAST (optional)
            if (opt.write_manifest) {
                // Populate manifest outputs deterministically from bundle before serialisation.
                bundle.manifest().sync_outputs_from_bundle(bundle);
                write_manifest_last(bundle, plan.staging_root, opt);
            }

            // 5) Atomically rename staging -> final
            std::filesystem::rename(plan.staging_root, plan.final_root, ec);
            if (ec)
                throw std::runtime_error("AtomicBundleWriter: failed to rename staging -> final");

            // Success: staging no longer exists as path; final exists.
        } catch (...) {
            remove_all_nothrow(plan.staging_root);
            throw;
        }
    }

    void AtomicBundleWriter::remove_all_nothrow(const std::filesystem::path &p) noexcept {
        try {
            if (!p.empty() && std::filesystem::exists(p)) {
                std::error_code ec;
                std::filesystem::remove_all(p, ec);
            }
        } catch (...) {
            // swallow
        }
    }

    void AtomicBundleWriter::ensure_parent_dir(const std::filesystem::path &abs_file_path) {
        const auto parent = abs_file_path.parent_path();
        if (parent.empty())
            return;

        std::error_code ec;
        std::filesystem::create_directories(parent, ec);
        if (ec) {
            throw std::runtime_error("AtomicBundleWriter: failed to create parent directory");
        }
    }

    void AtomicBundleWriter::write_manifest_last(const ExportBundle &bundle, const std::filesystem::path &staging_root,
        const Options &opt) {
        const auto out_path = (staging_root / opt.manifest_filename).lexically_normal();
        ensure_parent_dir(out_path);

        std::ofstream ofs(out_path, std::ios::binary);
        if (!ofs)
            throw std::runtime_error("AtomicBundleWriter: failed to open manifest for write");

        const std::string json = bundle.manifest().to_json();
        ofs.write(json.data(), static_cast<std::streamsize>(json.size()));
        if (!ofs)
            throw std::runtime_error("AtomicBundleWriter: failed to write manifest");
    }

    void AtomicBundleWriter::compute_integrity_metadata(ExportBundle &bundle, const std::filesystem::path &staging_root) {
        bundle.validate();

        auto& outs = bundle.outputs_mut();
        for (auto& o : outs) {
            const auto abs_path = (staging_root / o.path).lexically_normal();

            const auto bytes = std::filesystem::file_size(abs_path);
            const auto hash = sha256_hex_file(abs_path);

            o.bytes = static_cast<std::uint64_t>(bytes);
            o.sha256 = hash;
        }
    }
}
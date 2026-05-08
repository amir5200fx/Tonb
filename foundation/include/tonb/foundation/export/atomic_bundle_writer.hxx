/**
* @file atomic_bundle_writer.hxx
 * @brief Atomic export bundle writer implementing no-partial-artefacts lifecycle.
 *
 * @details
 * This writer implements the atomic writer layer lifecycle:
 *
 * 1) Create temporary bundle folder (staging root)
 * 2) Write payload files into staging
 * 3) Compute file hashes (SHA-256) and sizes
 * 4) Write manifest.json LAST
 * 5) Atomically rename staging folder to final location
 *
 * No partial artefacts guarantee:
 * - The final bundle directory path does not exist until the final rename succeeds.
 * - On any error, the staging directory is removed best-effort.
 *
 * Determinism:
 * - No randomness, timestamps, or filesystem enumeration.
 * - Payload ordering is the order specified by ExportBundle::outputs().
 * - Manifest is written last, always.
 *
 * Export vs dump separation:
 * - This writer operates on ExportBundle regardless of kind.
 * - Callers choose root directories via policy (workspace export vs dump roots).
 *
 * Platform notes:
 * - Atomicity relies on std::filesystem::rename when staging and final are on the same filesystem.
 * - Staging roots are created as sibling paths near final_root by BundleWritePlan.
 * - Cross-filesystem renames are rejected deterministically.
 */
#pragma once
#ifndef TONB_FOUNDATION_EXPORT_ATOMIC_BUNDLE_WRITER_HXX
#define TONB_FOUNDATION_EXPORT_ATOMIC_BUNDLE_WRITER_HXX

#include <tonb/foundation/export/export_bundle.hxx>
#include <tonb/foundation/module.hxx>

#include <filesystem>
#include <functional>
#include <string>
#include <vector>

namespace tonb::foundation::exporting {
    /**
     * @brief Payload writer callback for producing a single output file.
     *
     * @details
     * The writer provides the absolute destination path under staging root.
     * The callback must write the file content to that path.
     *
     * The callback must throw on failure. Returning normally indicates success.
     */
    using PayloadWriteFn = std::function<void(const std::filesystem::path& abs_dst_path)>;

    /**
     * @brief Mapping entry connecting an OutputFile to a payload writer.
     *
     * @details
     * This separates the bundle model (metadata) from the actual file generation.
     */
    struct PayloadItem {
        /**
         * @brief Index into ExportBundle::outputs() that this payload writes.
         */
        std::size_t output_index = 0;

        /**
         * @brief Callback that writs the payload file into staging root.
         */
        PayloadWriteFn write;
    };

    /**
     * @brief Atomic bundle writer implementing the the atomic writer layer lifecycle.
     *
     * @details
     * Typical usage:
     *  - Build ExportBundle with root = final_root.
     *  - Add OutputFile entries (relative paths).
     *  - Provide PayloadItem list mapping each output entry to a write callback.
     *  - Call AtomicBundleWriter::write_bundle_atomic.
     *
     * The writer will:
     *  - create staging directory (plan.staging_root)
     *  - write all payload files
     *  - compute sha256 and sizes and populate OutputFile metadata
     *  - write manifest.json last
     *  - rename staging_root -> final_root atomically
     *
     * If any step fails:
     *  - staging_root is removed best-effort
     *  - final_root remains absent
     */
    class AtomicBundleWriter {
    public:
        /**
         * @brief Options controlling writer behaviour.
         */
        struct Options {
            /**
             * @brief If false, skip writing the manifest file.
             */
            bool write_manifest = true;

            /**
             * @brief If false, skip computing per-file hashes and sizes.
             */
            bool compute_integrity = true;

            /**
             * @brief Manifest filename written inside the bundle root.
             */
            std::string manifest_filename = "manifest.json";

            /**
             * @brief If true, refuse to overwrite an existing final bundle directory.
             *
             * @note
             * This should remain true for professional-grade safety.
             */
            bool refuse_if_final_exists = true;
        };

        /**
         * @brief Write a bundle atomically according to the atomic writer layer lifecycle.
         *
         * @param bundle ExportBundle (root is final_root).
         * @param plan BundleWritePlan containing staging_root and final_root.
         * @param payloads Payload items mapping outputs to actual file writers.
         * @param opt Writer options.
         *
         * @throws std::invalid_argument If plan or payload mapping is invalid.
         * @throws std::runtime_error For filesystem errors (create, write, rename).
         * @throws std::logic_error For invariant violationsor incomplete payload mapping.
         *
         * @post On success:
         *  - final_root exists and contains all payload files and manifest.json.
         *  - staging_root does not exist.
         *
         * @post On failure:
         *  - final_root does not exist (or remains untouched if it existed and refuse_if_final_exists is true).
         *  - staging_root is removed best-effort.
         */
        static TNBFOUND_EXPORT void write_bundle_atomic(ExportBundle &bundle, const BundleWritePlan &plan,
                                                      const std::vector<PayloadItem> &payloads, const Options &opt);

    private:

        /**
         * @brief Best-effort recursive removal for staging directories.
         *
         * @details
         * Never throws. Used to uphold "no corrupted artefacts" guarantee when errors occur.
         */
        static void remove_all_nothrow(const std::filesystem::path& p) noexcept;

        /**
         * @brief Ensure parent directory exists for a target file path under staging.
         *
         * @throws std::runtime_error on failure.
         */
        static void ensure_parent_dir(const std::filesystem::path& abs_file_path);

        /**
         * @brief Write manifest.json last inside staging root.
         *
         * @throws std::runtime_error on write failures.
         */
        static void write_manifest_last(const ExportBundle& bundle, const std::filesystem::path& staging_root, const Options& opt);

        /**
         * @brief Compute sha256 and byte size for each output file under staging root.
         *
         * @details
         * Populates OutputFile.sha256 and OutputFile.bytes.
         *
         * @throws std::runtime_error on read failures.
         */
        static void compute_integrity_metadata(ExportBundle& bundle, const std::filesystem::path& staging_root);
    };
}

#endif // TONB_FOUNDATION_EXPORT_ATOMIC_BUNDLE_WRITER_HXX
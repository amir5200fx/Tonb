/**
* @file bundle_integrity.hxx
 * @brief Deterministic integrity metadata and aggregate hashing for export bundles.
 *
 * @details
 * This module implements the integrity layer (Cryptographic Integrity Layer) for Tonb export
 * bundles.
 *
 * Responsibilities:
 * - Compute per-output SHA-256 and byte sizes for payload files.
 * - Compute a deterministic bundle-level aggregate hash from the output list.
 *
 * Design rules:
 * - Uses Tonb's internal SHA-256 implementation (no OpenSSL).
 * - Deterministic by construction: ordering is always the authored order of
 *   ExportBundle::outputs().
 * - Does not enumerate the filesystem.
 * - Does not depend on timestamps, file metadata (other than file bytes), or
 *   platform-specific path separators.
 *
 * Aggregate hash definition:
 * The bundle aggregate hash is computed as:
 *
 *   SHA256( concat( record(i) for i in outputs_in_order ) )
 *
 * where record(i) is the UTF-8 text:
 *
 *   <path_generic> "\n" <sha256_hex> "\n" <bytes_decimal> "\n"
 *
 * Notes:
 * - path_generic is OutputFile::path rendered using generic_string(), ensuring
 *   stable '/' separators.
 * - sha256_hex must be populated for each output before computing the aggregate.
 * - bytes_decimal must be populated for each output before computing the aggregate.
 *
 * This definition is intentionally simple, stable, and fully reproducible.
 */
#pragma once
#ifndef TONB_FOUNDATION_EXPORT_BUNDLE_INTEGRITY_HXX
#define TONB_FOUNDATION_EXPORT_BUNDLE_INTEGRITY_HXX

#include <tonb/foundation/export/export_bundle.hxx>
#include <tonb/foundation/module.hxx>

#include <filesystem>
#include <string>

namespace tonb::foundation::exporting {
    struct OutputFile;

    /**
     * @brief Compute per-output integrity metadata (SHA-256 + byte size).
     *
     * @details
     * This function computes and populates:
     * - OutputFile::sha256 (lower-case hex)
     * - OutputFile::bytes
     *
     * The payload bytes are read from disk.
     *
     * Determinism:
     * - The output ordering is preserved.
     * - Hash results depend only on file content bytes.
     *
     * @param bundle Bundle whose outputs will be populated.
     * @param payload_root Absolute directory containing the payload files.
     *   For atomic writing, this is typically the staging root.
     *
     * @throws std::invalid_argument If payload_root is empty or not absolute.
     * @throws std::runtime_error If any payload file is missing or unreadable.
     */
    TNBFOUND_EXPORT void compute_output_integrity_metadata(ExportBundle& bundle, const std::filesystem::path& payload_root);

    /**
     * @brief Compute deterministic bundle-level aggregate SHA-256.
     *
     * @details
     * This hashes the ordered list of outputs (path + per-file sha256 + bytes).
     *
     * Preconditions:
     * - For each output:
     *   - OutputFile::sha256 is populated
     *   - OutputFile::bytes is populated
     *
     * @param bundle Bundle whose outputs determine the aggregate.
     * @return 64-character lower-case hex SHA-256 string.
     *
     * @throws std::logic_error If required integrity metadata is missing.
     */
    TNBFOUND_ND_EXPORT std::string bundle_aggregate_sha256(const ExportBundle& bundle);

    /**
     * @brief Build deterministic JSON extension value describing bundle integrity.
     *
     * @details
     * The returned string is a JSON value (object) with fixed key order:
     *  - algorithm
     *  - bundle_sha256
     *  - aggregate_rule
     *
     * Callers typically attach this under Manifest::add_extension with an
     * agreed key (e.g. "bundle_integrity").
     *
     * @param bundle_sha256 Aggregate hash string (hex).
     * @return JSON object as a string (no trailing newline).
     */
    TNBFOUND_ND_EXPORT std::string make_bundle_integrity_extension_json(std::string_view bundle_sha256);
}

#endif // TONB_FOUNDATION_EXPORT_BUNDLE_INTEGRITY_HXX
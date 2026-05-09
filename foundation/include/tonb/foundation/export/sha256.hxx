/**
* @file sha256.hxx
 * @brief Minimal SHA-256 hashing utility for Tonb foundation export bundles.
 *
 * @details
 * This module provides SHA-256 hashing required by the atomic bundle writer (the atomic writer layer).
 * It is implemented without external dependencies to keep builds self-contained.
 *
 * Scope:
 * - Compute SHA-256 for in-memory buffers.
 * - Compute SHA-256 for files (streaming).
 *
 * Determinism:
 * - Hash results depend only on input bytes.
 * - No global state, no randomness, no filesystem metadata usage.
 *
 * Security note:
 * - This is a standard SHA-256 implementation intended for integrity verification.
 * - It is not intended as a password hashing mechanism.
 */
#pragma once
#ifndef TONB_FOUNDATION_EXPORT_SHA256_HXX
#define TONB_FOUNDATION_EXPORT_SHA256_HXX

#include <tonb/foundation/module.hxx>

#include <cstdint>
#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>

namespace tonb::foundation::exporting {
    /**
     * @brief Compute SHA-256 digest for a byte buffer and return lower-case hex string.
     *
     * @param data Input bytes.
     * @return 64-character lower-case hex string.
     */
    TNBFOUND_ND_EXPORT std::string sha256_hex(const std::vector<std::uint8_t>& data);

    /**
     * @brief Compute SHA-256 digest for a byte span and return lower-case hex string.
     *
     * @param data Pointer to bytes (may be null only if size == 0).
     * @param size Number of bytes.
     * @return 64-character lower-case hex string.
     */
    TNBFOUND_ND_EXPORT std::string sha256_hex(const std::uint8_t* data, std::size_t size);

    /**
     * @brief Compute SHA-256 digest for a file and return lower-case hex string.
     *
     * @details
     * This reads the file in fixed-size chunks and hashes streaming.
     *
     * @param path Path to the file.
     * @return 64-character lower-case hex string.
     *
     * @throws std::runtime_error If the file cannot be opened or read.
     */
    TNBFOUND_ND_EXPORT std::string sha256_hex_file(const std::filesystem::path& path);
}

#endif // TONB_FOUNDATION_EXPORT_SHA256_HXX
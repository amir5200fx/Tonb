/**
* @file bundle_naming.hxx
 * @brief Deterministic bundle naming engine (the naming layer).
 *
 * @details
 * Generates self-describing bundle directory names using a strict format:
 *
 *   <UTC>_<namespace>-<command>_<input-tag>__<extra-tags>
 *
 * Deterministic behaviour:
 * - No randomness.
 * - ISO8601 UTC timestamp (YYYYMMDDTHHMMSSZ).
 * - All tokens sanitised.
 * - Extra tags sorted lexicographically.
 * - Maximum length enforced with deterministic truncation.
 */
#pragma once
#ifndef TONB_FOUNDATION_EXPORT_BUNDLE_NAMING_HXX
#define TONB_FOUNDATION_EXPORT_BUNDLE_NAMING_HXX

#include <tonb/foundation/module.hxx>

#include <string>
#include <vector>

namespace tonb::foundation::exporting {
    /**
     * @brief Configuration for deterministic naming.
     */
    struct NamingConfig {
        std::size_t max_length = 128;  ///< Hard cap on resulting name.
    };

    /**
     * @brief Generate deterministic bundle name.
     *
     * @param utc_iso8601_compact Timestamp in form YYYYMMDDTHHMMSSZ.
     * @param ns Namespace (e.g. "inp", "surf").
     * @param command Canonical command (e.g. "export", "apply").
     * @param input_tag Short input identifier.
     * @param extra_tags Additional tags (unordered input; sorted internally).
     * @param cfg Naming configuration.
     *
     * @return Sanitised deterministic bundle name.
     *
     * @throws std::invalid_argument On invalid inputs.
     */
    TNBFOUND_ND_EXPORT std::string make_bundle_name(std::string utc_iso8601_compact, std::string ns, std::string command, std::string input_tag, std::vector<std::string> extra_tags, NamingConfig cfg = {});
}

#endif // TONB_FOUNDATION_EXPORT_BUNDLE_NAMING_HXX
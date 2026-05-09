/**
* @file export_profile.hxx
 * @brief Export profile policy for controlling layout and metadata depth (the export-profile layer).
 *
 * @details
 * Export profiles are a deterministic policy layer that configures:
 *  - layout: bundle (atomic directory) vs flat (single file)
 *  - manifest inclusion
 *  - metadata depth (minimal/full/audit)
 *
 * This module performs no filesystem IO.
 */
#pragma once
#ifndef TONB_FOUNDATION_EXPORT_EXPORT_PROFILE_HXX
#define TONB_FOUNDATION_EXPORT_EXPORT_PROFILE_HXX

#include <tonb/foundation/module.hxx>

#include <string_view>

namespace tonb::foundation::exporting {
    enum class ExportLayout {
        bundle,
        flat
    };

    enum class ExportProfileKind {
        minimal,
        full,
        audit
    };

    struct ExportProfile {
        ExportLayout layout = ExportLayout::bundle;
        ExportProfileKind kind = ExportProfileKind::full;

        bool include_manifest = true;

        bool include_domain_summary = true;
        bool include_integrity = true;
        bool include_workspace_info = true;
        bool include_input_provenance = true;

        // Audit-only toggles (may be implemented incrementally).
        bool include_environment = false;
        bool include_diagnostics = false;

        /**
         * @brief Validate profile invariants and illegal combinations.
         *
         * @throws std::invalid_argument on invalid configuration.
         */
        TNBFOUND_EXPORT void validate() const;
    };

    /**
     * @brief Parse profile token.
     *
     * @param s "minimal" | "full" | "audit"
     * @throws std::invalid_argument on unknown token.
     */
    TNBFOUND_EXPORT ExportProfileKind parse_profile_kind(std::string_view s);

    /**
     * @brief Build a validated ExportProfile from layout/kind and flags.
     *
     * Rules:
     * - Defaults: layout=bundle, kind=full, include_manifest=true.
     * - no_manifest disables manifest and any manifest-dependent metadata.
     */
    TNBFOUND_EXPORT ExportProfile make_profile(ExportLayout layout, ExportProfileKind kind, bool no_manifest);
}

#endif // TONB_FOUNDATION_EXPORT_EXPORT_PROFILE_HXX
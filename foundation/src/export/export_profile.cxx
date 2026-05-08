/**
* @file export_profile.cxx
 * @brief Implementation of export profile policy (the export-profile layer).
 */
#include <tonb/foundation/export/export_profile.hxx>

#include <string>
#include <stdexcept>

namespace tonb::foundation::exporting {
    void ExportProfile::validate() const {
        // If manifest is disabled, all manifest-dependent metadata must be disabled.
        if (!include_manifest) {
            if (include_domain_summary || include_workspace_info || include_input_provenance) {
                throw std::invalid_argument("ExportProfile: manifest-disabled profile cannot include manifest-dependent metadata");
            }
        }

        // Integrity currently flows through writer->manifest outputs. If manifest is disabled,
        // integrity is meaningless in the current architecture (no place to record it).
        if (!include_manifest && include_integrity) {
            throw std::invalid_argument("ExportProfile: integrity requires manifest");
        }

        // Flat exports cannot provide no-partial-artefacts guarantees.
        // We still allow manifest and integrity, but writers must not claim atomic directory promotion.
        // (Handled by command layer until a dedicated flat writer exists.)
    }

    ExportProfileKind parse_profile_kind(const std::string_view s) {
        if (s == "minimal") return ExportProfileKind::minimal;
        if (s == "full")    return ExportProfileKind::full;
        if (s == "audit")   return ExportProfileKind::audit;
        throw std::invalid_argument("Unknown export profile: " + std::string(s));
    }

    ExportProfile make_profile(const ExportLayout layout, const ExportProfileKind kind, const bool no_manifest) {
        ExportProfile p;
        p.layout = layout;
        p.kind = kind;

        // Base by kind
        switch (kind) {
            case ExportProfileKind::minimal:
                p.include_manifest = true;
                p.include_domain_summary = true;
                p.include_integrity = false;
                p.include_workspace_info = true;
                p.include_input_provenance = true;
                p.include_environment = false;
                p.include_diagnostics = false;
                break;

            case ExportProfileKind::full:
                p.include_manifest = true;
                p.include_domain_summary = true;
                p.include_integrity = true;
                p.include_workspace_info = true;
                p.include_input_provenance = true;
                p.include_environment = false;
                p.include_diagnostics = false;
                break;

            case ExportProfileKind::audit:
                p.include_manifest = true;
                p.include_domain_summary = true;
                p.include_integrity = true;
                p.include_workspace_info = true;
                p.include_input_provenance = true;
                p.include_environment = true;
                p.include_diagnostics = true;
                break;
        }

        // Apply no-manifest override
        if (no_manifest) {
            p.include_manifest = false;
            p.include_domain_summary = false;
            p.include_integrity = false;
            p.include_workspace_info = false;
            p.include_input_provenance = false;
            p.include_environment = false;
            p.include_diagnostics = false;
        }

        p.validate();
        return p;
    }
}
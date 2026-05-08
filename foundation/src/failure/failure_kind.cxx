/**
 * @file failure_kind.cxx
 * @brief Implementation of canonical failure-kind mapping.
 */
#include <tonb/foundation/failure/failure_kind.hxx>

namespace tonb::foundation::failure {

    std::string_view to_string(const FailureKind kind) noexcept {
        switch (kind) {
            case FailureKind::user_input: return "user_input";
            case FailureKind::configuration: return "configuration";
            case FailureKind::filesystem: return "filesystem";
            case FailureKind::serialisation: return "serialisation";
            case FailureKind::validation: return "validation";
            case FailureKind::invariant_violation: return "invariant_violation";
            case FailureKind::internal_error: return "internal_error";
            case FailureKind::external_tool: return "external_tool";
            case FailureKind::geometry: return "geometry";
            case FailureKind::meshing: return "meshing";
            case FailureKind::topology: return "topology";
            case FailureKind::unknown: return "unknown";
        }
        return "unknown";
    }

} // namespace tonb::foundation::failure

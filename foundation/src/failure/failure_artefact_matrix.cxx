/**
 * @file failure_artefact_matrix.cxx
 * @brief Implementation of deterministic artefact requirement rules.
 */
#include <tonb/foundation/failure/failure_artefact_matrix.hxx>

#include <algorithm>

namespace tonb::foundation::failure {
    namespace {
        const std::vector<std::string_view>& empty_required() {
            static const std::vector<std::string_view> values{};
            return values;
        }

        const std::vector<std::string_view>& geometry_required() {
            static const std::vector<std::string_view> values{
                "inputs.json",
                "state_summary.json"
            };
            return values;
        }

        const std::vector<std::string_view>& meshing_required() {
            static const std::vector<std::string_view> values{
                "inputs.json",
                "state_summary.json",
                "tool_output.log"
            };
            return values;
        }

        const std::vector<std::string_view>& filesystem_required() {
            static const std::vector<std::string_view> values{
                "inputs.json"
            };
            return values;
        }

        const std::vector<std::string_view>& topology_required() {
            static const std::vector<std::string_view> values{
                "inputs.json",
                "state_summary.json"
            };
            return values;
        }
    }

    const std::vector<std::string_view>& required_artefact_names(const FailureKind kind) {
        switch (kind) {
            case FailureKind::geometry: return geometry_required();
            case FailureKind::meshing: return meshing_required();
            case FailureKind::filesystem: return filesystem_required();
            case FailureKind::topology: return topology_required();
            default: return empty_required();
        }
    }

    bool is_required_artefact(const FailureKind kind, const std::string_view filename) noexcept {
        const auto& values = required_artefact_names(kind);
        return std::find(values.begin(), values.end(), filename) != values.end();
    }

} // namespace tonb::foundation::failure

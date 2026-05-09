/**
 * @file command_spec.cxx
 * @brief Validation helpers for foundation CLI command specifications.
 */
#include <tonb/foundation/cli/command_spec.hxx>

#include <stdexcept>

namespace tonb::foundation::cli {

    void validate_command_spec(const CommandSpec& spec) {
        if (spec.canonical_path.empty()) {
            throw std::invalid_argument("validate_command_spec: canonical_path must not be empty");
        }
        if (spec.domain.empty()) {
            throw std::invalid_argument("validate_command_spec: domain must not be empty");
        }
        if (spec.summary.empty()) {
            throw std::invalid_argument("validate_command_spec: summary must not be empty");
        }
        for (const auto& alias : spec.aliases) {
            if (alias.empty()) {
                throw std::invalid_argument("validate_command_spec: alias path must not be empty");
            }
            if (alias == spec.canonical_path) {
                throw std::invalid_argument("validate_command_spec: alias must differ from canonical_path");
            }
        }
        for (const auto& option : spec.options) {
            if (option.label.empty()) {
                throw std::invalid_argument("validate_command_spec: option label must not be empty");
            }
        }
        if (spec.stability == CommandStability::deprecated && !spec.deprecation.has_value()) {
            throw std::invalid_argument("validate_command_spec: deprecated commands must provide deprecation metadata");
        }
    }

} // namespace tonb::foundation::cli

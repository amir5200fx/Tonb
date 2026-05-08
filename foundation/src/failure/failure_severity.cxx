/**
 * @file failure_severity.cxx
 * @brief Implementation of failure-severity token mapping.
 */
#include <tonb/foundation/failure/failure_severity.hxx>

namespace tonb::foundation::failure {

    std::string_view to_string(const FailureSeverity severity) noexcept {
        switch (severity) {
            case FailureSeverity::warning: return "warning";
            case FailureSeverity::error: return "error";
            case FailureSeverity::critical: return "critical";
            case FailureSeverity::fatal: return "fatal";
        }
        return "error";
    }

} // namespace tonb::foundation::failure

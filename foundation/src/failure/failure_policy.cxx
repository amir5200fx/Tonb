/**
 * @file failure_policy.cxx
 * @brief Implementation of failure-policy helpers.
 */
#include <tonb/foundation/failure/failure_policy.hxx>

namespace tonb::foundation::failure {

    bool should_write_bundle(const FailurePolicy& policy, const FailureSeverity severity) noexcept {
        return static_cast<int>(severity) >= static_cast<int>(policy.bundle_threshold);
    }

} // namespace tonb::foundation::failure

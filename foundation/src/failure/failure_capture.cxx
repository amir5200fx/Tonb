/**
 * @file failure_capture.cxx
 * @brief Implementation of exception-to-failure capture helpers.
 */
#include <tonb/foundation/failure/failure_capture.hxx>

#include <typeinfo>

namespace tonb::foundation::failure {

    FailureEvent capture_failure(const FailureException& ex, FailureContext context) {
        FailureEvent event{
            FailureCode(ex.code()),
            ex.kind(),
            ex.severity(),
            ex.domain(),
            ex.what(),
            current_utc_timestamp(),
            std::string(typeid(ex).name()),
            context.correlation_id,
            std::nullopt,
            std::nullopt,
            ex.diagnostics(),
            {},
            std::move(context)
        };
        return event;
    }

    FailureEvent capture_failure(
        const std::exception& ex,
        std::string code,
        std::string domain,
        FailureContext context,
        const FailureSeverity severity,
        const FailureKind kind) {
        FailureEvent event{
            FailureCode(std::move(code)),
            kind,
            severity,
            std::move(domain),
            ex.what(),
            current_utc_timestamp(),
            std::string(typeid(ex).name()),
            context.correlation_id,
            std::nullopt,
            std::nullopt,
            {},
            {FailureCause{"exception", ex.what(), std::nullopt, {}}},
            std::move(context)
        };
        return event;
    }

} // namespace tonb::foundation::failure

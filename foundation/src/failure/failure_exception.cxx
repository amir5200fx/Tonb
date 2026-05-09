/**
 * @file failure_exception.cxx
 * @brief Implementation of structured failure exception.
 */
#include <tonb/foundation/failure/failure_exception.hxx>
#include <tonb/foundation/failure/failure_code.hxx>
#include <tonb/foundation/failure/failure_event.hxx>

#include <stdexcept>
#include <utility>

namespace tonb::foundation::failure {

    FailureException::FailureException(
        std::string code,
        const FailureKind kind,
        const FailureSeverity severity,
        std::string domain,
        std::string message,
        DiagnosticFields diagnostics)
        : std::runtime_error(message),
          code_(std::move(code)),
          kind_(kind),
          severity_(severity),
          domain_(std::move(domain)),
          diagnostics_(std::move(diagnostics)) {
        if (!FailureCode::is_valid(code_)) {
            throw std::invalid_argument("FailureException: invalid code");
        }
        if (!is_valid_domain_token(domain_)) {
            throw std::invalid_argument("FailureException: invalid domain token");
        }
    }

} // namespace tonb::foundation::failure

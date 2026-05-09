/**
 * @file failure_exception.hxx
 * @brief Structured exception type carrying foundation failure metadata.
 *
 * @details
 * Future applications can throw this exception at subsystem boundaries and then
 * translate it directly into a FailureEvent without losing the stable code,
 * classification, or diagnostics.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_EXCEPTION_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_EXCEPTION_HXX

#include <tonb/foundation/failure/failure_diagnostic.hxx>
#include <tonb/foundation/failure/failure_kind.hxx>
#include <tonb/foundation/failure/failure_severity.hxx>
#include <tonb/foundation/module.hxx>

#include <stdexcept>
#include <string>
#include <vector>

namespace tonb::foundation::failure {

    /**
     * @brief Base structured exception carrying failure metadata.
     */
    class FailureException final : public std::runtime_error {
    public:
        /**
         * @brief Construct a structured failure exception.
         */
        TNBFOUND_EXPORT FailureException(
            std::string code,
            FailureKind kind,
            FailureSeverity severity,
            std::string domain,
            std::string message,
            DiagnosticFields diagnostics = {});

        /** @brief Return the stable failure code. */
        TNB_NODISCARD const std::string& code() const noexcept { return code_; }

        /** @brief Return the broad failure kind. */
        TNB_NODISCARD FailureKind kind() const noexcept { return kind_; }

        /** @brief Return the failure severity. */
        TNB_NODISCARD FailureSeverity severity() const noexcept { return severity_; }

        /** @brief Return the application-defined domain token. */
        TNB_NODISCARD const std::string& domain() const noexcept { return domain_; }

        /** @brief Return the attached diagnostics. */
        TNB_NODISCARD const DiagnosticFields& diagnostics() const noexcept { return diagnostics_; }

    private:
        std::string code_;
        FailureKind kind_;
        FailureSeverity severity_;
        std::string domain_;
        DiagnosticFields diagnostics_;
    };

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_EXCEPTION_HXX

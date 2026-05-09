/**
 * @file failure_capture.hxx
 * @brief Helpers that translate exceptions and context into structured failure events.
 *
 * @details
 * This module gives applications one canonical place to build a FailureEvent at
 * a boundary such as a shell command dispatcher, API entry point, or worker-job
 * execution wrapper.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_CAPTURE_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_CAPTURE_HXX

#include <tonb/foundation/failure/failure_event.hxx>
#include <tonb/foundation/failure/failure_exception.hxx>
#include <tonb/foundation/module.hxx>

#include <exception>
#include <string>

namespace tonb::foundation::failure {

    /**
     * @brief Build a FailureEvent from a structured FailureException.
     */
    TNBFOUND_ND_EXPORT FailureEvent capture_failure(
        const FailureException& ex,
        FailureContext context);

    /**
     * @brief Build a generic internal-error FailureEvent from a std::exception.
     */
    TNBFOUND_ND_EXPORT FailureEvent capture_failure(
        const std::exception& ex,
        std::string code,
        std::string domain,
        FailureContext context,
        FailureSeverity severity = FailureSeverity::error,
        FailureKind kind = FailureKind::internal_error);

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_CAPTURE_HXX

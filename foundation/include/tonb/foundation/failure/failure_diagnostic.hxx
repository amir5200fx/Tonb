/**
 * @file failure_diagnostic.hxx
 * @brief Structured diagnostic fields attached to failure events.
 *
 * @details
 * Diagnostics provide compact structured context that can be serialised directly
 * into bundle metadata or sidecar JSON files without requiring heavyweight file
 * artefacts for every small piece of evidence.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_DIAGNOSTIC_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_DIAGNOSTIC_HXX

#include <tonb/foundation/module.hxx>

#include <string>
#include <vector>

namespace tonb::foundation::failure {

    /**
     * @brief Single structured diagnostic field.
     */
    struct DiagnosticField {
        std::string key;
        std::string value;
    };

    /**
     * @brief Ordered collection of structured diagnostics.
     */
    using DiagnosticFields = std::vector<DiagnosticField>;

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_DIAGNOSTIC_HXX

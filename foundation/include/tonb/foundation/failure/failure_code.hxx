/**
 * @file failure_code.hxx
 * @brief Stable support-facing failure code model and validation helpers.
 *
 * @details
 * A failure code is intended to be stable across releases and documentation.
 * Example formats include:
 * - GF-GEOM-0001
 * - GF-MESH-0042
 * - IX-CORE-0100
 *
 * The foundation layer does not impose one specific application prefix, but it
 * does enforce a disciplined uppercase-with-dashes format so codes remain easy
 * to search, document, and communicate.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_CODE_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_CODE_HXX

#include <tonb/foundation/module.hxx>

#include <string>
#include <string_view>

namespace tonb::foundation::failure {

    /**
     * @brief Stable failure code wrapper.
     */
    class FailureCode {
    public:
        /**
         * @brief Construct a validated failure code.
         * @param value Canonical failure code text.
         * @throws std::invalid_argument If the code format is invalid.
         */
        explicit TNBFOUND_EXPORT FailureCode(std::string value);

        /** @brief Return the canonical code text. */
        const std::string& value() const noexcept { return value_; }

        /** @brief Return true if the supplied text is a valid canonical code. */
        static bool is_valid(std::string_view value) noexcept;

    private:
        std::string value_;
    };

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_CODE_HXX

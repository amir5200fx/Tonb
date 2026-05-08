/**
 * @file failure_code.cxx
 * @brief Implementation of failure-code validation.
 */
#include <tonb/foundation/failure/failure_code.hxx>

#include <cctype>
#include <stdexcept>

namespace tonb::foundation::failure {

    namespace {
        bool is_valid_char(const char c) noexcept {
            return std::isupper(static_cast<unsigned char>(c)) != 0 ||
                   std::isdigit(static_cast<unsigned char>(c)) != 0 ||
                   c == '-';
        }
    }

    FailureCode::FailureCode(std::string value)
        : value_(std::move(value)) {
        if (!is_valid(value_)) {
            throw std::invalid_argument("FailureCode: invalid canonical failure code");
        }
    }

    bool FailureCode::is_valid(const std::string_view value) noexcept {
        if (value.size() < 5) {
            return false;
        }
        if (value.front() == '-' || value.back() == '-') {
            return false;
        }
        bool has_dash = false;
        bool has_digit = false;
        for (const char c : value) {
            if (!is_valid_char(c)) {
                return false;
            }
            if (c == '-') {
                has_dash = true;
            }
            if (std::isdigit(static_cast<unsigned char>(c)) != 0) {
                has_digit = true;
            }
        }
        return has_dash && has_digit;
    }

} // namespace tonb::foundation::failure

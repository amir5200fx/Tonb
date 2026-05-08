/**
 * @file parse_utils.cxx
 * @brief Implementation of generic scalar parsing helpers for CLI code.
 */
#include <tonb/foundation/cli/parse_utils.hxx>

#include <charconv>
#include <stdexcept>

namespace tonb::foundation::cli {

    namespace {
        template <typename T>
        T parse_integral_impl(std::string_view text, const char* label) {
            T value{};
            const auto* begin = text.data();
            const auto* end = text.data() + text.size();
            const auto [ptr, ec] = std::from_chars(begin, end, value);
            if (ec != std::errc{} || ptr != end) {
                throw std::invalid_argument(std::string(label) + ": invalid integer: " + std::string(text));
            }
            return value;
        }
    }

    bool parse_bool_strict(const std::string_view text) {
        if (text == "true" || text == "1" || text == "yes" || text == "on") return true;
        if (text == "false" || text == "0" || text == "no" || text == "off") return false;
        throw std::invalid_argument("parse_bool_strict: invalid boolean: " + std::string(text));
    }

    int parse_int_strict(const std::string_view text) {
        return parse_integral_impl<int>(text, "parse_int_strict");
    }

    long long parse_long_long_strict(const std::string_view text) {
        return parse_integral_impl<long long>(text, "parse_long_long_strict");
    }

    double parse_double_strict(const std::string_view text) {
        std::size_t offset = 0;
        try {
            const double value = std::stod(std::string(text), &offset);
            if (offset != text.size()) {
                throw std::invalid_argument("parse_double_strict: invalid floating-point value: " + std::string(text));
            }
            return value;
        } catch (const std::exception&) {
            throw std::invalid_argument("parse_double_strict: invalid floating-point value: " + std::string(text));
        }
    }

    std::optional<bool> try_parse_bool(const std::string_view text) noexcept {
        try {
            return parse_bool_strict(text);
        } catch (...) {
            return std::nullopt;
        }
    }

} // namespace tonb::foundation::cli

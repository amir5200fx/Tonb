/**
 * @file parse_utils.hxx
 * @brief Generic value-parsing helpers for CLI-oriented foundation code.
 *
 * @details
 * These helpers are intentionally lightweight and application-neutral. They are
 * suitable for parsing common scalar arguments after command dispatch has already
 * selected the appropriate command.
 */
#pragma once
#ifndef TONB_FOUNDATION_CLI_PARSE_UTILS_HXX
#define TONB_FOUNDATION_CLI_PARSE_UTILS_HXX

#include <tonb/foundation/module.hxx>

#include <optional>
#include <string>
#include <string_view>

namespace tonb::foundation::cli {

    TNBFOUND_ND_EXPORT bool parse_bool_strict(std::string_view text);
    TNBFOUND_ND_EXPORT int parse_int_strict(std::string_view text);
    TNBFOUND_ND_EXPORT long long parse_long_long_strict(std::string_view text);
    TNBFOUND_ND_EXPORT double parse_double_strict(std::string_view text);
    TNBFOUND_ND_EXPORT std::optional<bool> try_parse_bool(std::string_view text) noexcept;

} // namespace tonb::foundation::cli

#endif // TONB_FOUNDATION_CLI_PARSE_UTILS_HXX

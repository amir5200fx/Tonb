/**
 * @file shell_tokenise.hxx
 * @brief Shell command-line tokenisation and positional parse helpers for cad2d shell.
 *
 * @details
 * This layer provides shell-specific command-line tokenisation on top of the shared
 * Tonb foundation CLI parsing helpers. Generic scalar parsing remains in
 * `tonb::foundation::cli::parse_utils`, while this module handles shell command-line
 * concerns such as whitespace splitting, quoted tokens, and positional argument access.
 */
#pragma once
#ifndef TONB_CAD2D_SHELL_SHELL_TOKENISE_HXX
#define TONB_CAD2D_SHELL_SHELL_TOKENISE_HXX

#include <tonb/cad2d/shell/module.hxx>
#include <tonb/foundation/cli/parse_utils.hxx>

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace tonb::cad2d::shell {

    /**
     * @brief Result of tokenising one shell command line.
     */
    struct TokeniseResult {
        bool ok = true;
        std::vector<std::string> tokens;
        std::string error;
    };

    /**
     * @brief Tokenise one shell command line.
     *
     * @details
     * The tokenizer performs whitespace-based splitting while preserving quoted strings
     * as single tokens. Double quotes are supported. A malformed unterminated quote
     * produces an explicit failure.
     */
    TNBCAD2DSHELL_ND_EXPORT TokeniseResult tokenise_command_line(std::string_view line);

    /**
     * @brief Lightweight positional argument view for token vectors.
     *
     * @details
     * This helper is intentionally simple and intended for shell command handlers after
     * command dispatch has already identified the command path. Scalar conversion is
     * delegated to the shared foundation CLI parse helpers.
     */
    class PositionalArgsView {
    public:
        explicit TNBCAD2DSHELL_EXPORT PositionalArgsView(const std::vector<std::string>& tokens) noexcept;

        TNBCAD2DSHELL_ND_EXPORT std::size_t size() const noexcept;
        TNBCAD2DSHELL_ND_EXPORT bool has(std::size_t index) const noexcept;
        TNBCAD2DSHELL_ND_EXPORT std::optional<std::string_view> get(std::size_t index) const noexcept;

        TNBCAD2DSHELL_ND_EXPORT std::string_view require(std::size_t index, std::string_view label) const;
        TNBCAD2DSHELL_ND_EXPORT int parse_int(std::size_t index, std::string_view label) const;
        TNBCAD2DSHELL_ND_EXPORT long long parse_long_long(std::size_t index, std::string_view label) const;
        TNBCAD2DSHELL_ND_EXPORT double parse_double(std::size_t index, std::string_view label) const;
        TNBCAD2DSHELL_ND_EXPORT bool parse_bool(std::size_t index, std::string_view label) const;

    private:
        const std::vector<std::string>* tokens_ = nullptr;
    };

} // namespace tonb::cad2d::shell

#endif // TONB_CAD2D_SHELL_SHELL_TOKENISE_HXX

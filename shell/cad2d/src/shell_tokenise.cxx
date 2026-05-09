/**
 * @file shell_tokenise.cxx
 * @brief Implementation of shell command-line tokenisation and positional parse helpers.
 */
#include <tonb/cad2d/shell/shell_tokenise.hxx>

#include <stdexcept>

namespace tonb::cad2d::shell {

    TokeniseResult tokenise_command_line(const std::string_view line) {
        TokeniseResult result{};
        std::string current;
        bool in_quotes = false;

        auto flush_current = [&]() {
            if (!current.empty()) {
                result.tokens.push_back(current);
                current.clear();
            }
        };

        for (char ch : line) {
            if (ch == '"') {
                in_quotes = !in_quotes;
                continue;
            }

            if (!in_quotes && (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')) {
                flush_current();
                continue;
            }

            current.push_back(ch);
        }

        if (in_quotes) {
            result.ok = false;
            result.tokens.clear();
            result.error = "tokenise_command_line: unterminated quoted string";
            return result;
        }

        flush_current();
        return result;
    }

    PositionalArgsView::PositionalArgsView(const std::vector<std::string>& tokens) noexcept
        : tokens_(&tokens) {
    }

    std::size_t PositionalArgsView::size() const noexcept {
        return tokens_ ? tokens_->size() : 0u;
    }

    bool PositionalArgsView::has(const std::size_t index) const noexcept {
        return tokens_ && index < tokens_->size();
    }

    std::optional<std::string_view> PositionalArgsView::get(const std::size_t index) const noexcept {
        if (!has(index)) return std::nullopt;
        return std::string_view((*tokens_)[index]);
    }

    std::string_view PositionalArgsView::require(const std::size_t index, const std::string_view label) const {
        if (const auto value = get(index)) {
            return *value;
        }
        throw std::invalid_argument(std::string("PositionalArgsView::require: missing argument: ") + std::string(label));
    }

    int PositionalArgsView::parse_int(const std::size_t index, const std::string_view label) const {
        return foundation::cli::parse_int_strict(require(index, label));
    }

    long long PositionalArgsView::parse_long_long(const std::size_t index, const std::string_view label) const {
        return foundation::cli::parse_long_long_strict(require(index, label));
    }

    double PositionalArgsView::parse_double(const std::size_t index, const std::string_view label) const {
        return foundation::cli::parse_double_strict(require(index, label));
    }

    bool PositionalArgsView::parse_bool(const std::size_t index, const std::string_view label) const {
        return foundation::cli::parse_bool_strict(require(index, label));
    }

} // namespace tonb::cad2d::shell

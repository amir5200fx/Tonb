#pragma once
#ifndef TONB_CAD2D_SHELL_COMMAND_COMMAND_ARGS_HXX
#define TONB_CAD2D_SHELL_COMMAND_COMMAND_ARGS_HXX

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <tonb/cad2d/shell/module.hxx>

namespace tonb::cad2d::shell::command {

    /**
     * @brief Non-owning-style command-argument container for dispatched shell handlers.
     *
     * The command registry consumes the matched command path and passes the remaining
     * user tokens to the command handler through this lightweight value container.
     */
    class CommandArgs {
    public:
        CommandArgs() = default;
        CommandArgs(std::initializer_list<std::string> values)
            : tokens_(values) {
        }
        explicit CommandArgs(std::vector<std::string> values)
            : tokens_(std::move(values)) {
        }

        TNB_NODISCARD std::size_t size() const noexcept {
            return tokens_.size();
        }

        TNB_NODISCARD bool empty() const noexcept {
            return tokens_.empty();
        }

        TNB_NODISCARD const std::vector<std::string>& tokens() const noexcept {
            return tokens_;
        }

        TNB_NODISCARD std::string_view operator[](const std::size_t index) const {
            return tokens_.at(index);
        }

        TNB_NODISCARD std::string_view at(const std::size_t index) const {
            return tokens_.at(index);
        }

    private:
        std::vector<std::string> tokens_;
    };

    /**
     * @brief Structured command-handler result.
     */
    struct CommandResult {
        bool ok = true;
        std::string message;

        TNB_NODISCARD static CommandResult success(std::string message = {}) {
            return CommandResult{true, std::move(message)};
        }

        TNB_NODISCARD static CommandResult failure(std::string message) {
            return CommandResult{false, std::move(message)};
        }
    };

} // namespace tonb::cad2d::shell::command

#endif // TONB_CAD2D_SHELL_COMMAND_COMMAND_ARGS_HXX

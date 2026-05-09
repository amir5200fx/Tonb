#pragma once
#ifndef TONB_CAD2D_SHELL_COMMAND_COMMAND_NODE_HXX
#define TONB_CAD2D_SHELL_COMMAND_COMMAND_NODE_HXX

#include <cstddef>
#include <initializer_list>
#include <string>
#include <vector>

#include <tonb/cad2d/shell/module.hxx>

namespace tonb::cad2d::shell::command {

    /**
     * @brief Canonical command path value type.
     */
    class CommandPath {
    public:
        CommandPath() = default;
        explicit CommandPath(std::vector<std::string> segments);
        CommandPath(std::initializer_list<std::string> segments);

        TNB_NODISCARD const std::vector<std::string>& segments() const noexcept {
            return segments_;
        }

        TNB_NODISCARD std::size_t size() const noexcept {
            return segments_.size();
        }

        TNB_NODISCARD bool empty() const noexcept {
            return segments_.empty();
        }

        TNB_NODISCARD std::string to_string() const;

        TNB_NODISCARD bool operator==(const CommandPath& other) const noexcept {
            return segments_ == other.segments_;
        }

        TNB_NODISCARD bool operator<(const CommandPath& other) const noexcept {
            return segments_ < other.segments_;
        }

    private:
        std::vector<std::string> segments_;
    };

    /**
     * @brief Lightweight description of a registered command path.
     */
    struct CommandNode {
        CommandPath canonical_path;
        std::vector<CommandPath> aliases;
    };

} // namespace tonb::cad2d::shell::command

#endif // TONB_CAD2D_SHELL_COMMAND_COMMAND_NODE_HXX

#pragma once
#ifndef TONB_CAD2D_SHELL_COMMAND_COMMAND_CONTEXT_HXX
#define TONB_CAD2D_SHELL_COMMAND_COMMAND_CONTEXT_HXX

#include <iosfwd>

#include <tonb/cad2d/shell/module.hxx>

namespace tonb::cad2d::shell {
    class ShellSession;
}

namespace tonb::cad2d::shell::command {

    /**
     * @brief Lightweight runtime context passed to command handlers.
     *
     * The context intentionally stays small and non-owning. It is designed to
     * mirror the iXFract-style shell command context without embedding registry,
     * parsing, or CAD algorithm state into handlers themselves.
     */
    class CommandContext {
    public:
        explicit CommandContext(shell::ShellSession* session = nullptr,
                                std::ostream* out = nullptr,
                                std::ostream* err = nullptr) noexcept
            : session_(session), out_(out), err_(err) {
        }

        TNB_NODISCARD shell::ShellSession* session() const noexcept {
            return session_;
        }

        TNB_NODISCARD std::ostream* out() const noexcept {
            return out_;
        }

        TNB_NODISCARD std::ostream* err() const noexcept {
            return err_;
        }

    private:
        shell::ShellSession* session_ = nullptr;
        std::ostream* out_ = nullptr;
        std::ostream* err_ = nullptr;
    };

} // namespace tonb::cad2d::shell::command

#endif // TONB_CAD2D_SHELL_COMMAND_COMMAND_CONTEXT_HXX

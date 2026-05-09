#pragma once
#ifndef TONB_CAD2D_SHELL_SHELL_APP_HXX
#define TONB_CAD2D_SHELL_SHELL_APP_HXX

#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>

#include <tonb/cad2d/shell/command/command_args.hxx>
#include <tonb/cad2d/shell/command/command_registry.hxx>
#include <tonb/cad2d/shell/help/help_registry.hxx>
#include <tonb/cad2d/shell/module.hxx>
#include <tonb/cad2d/shell/shell_session.hxx>

namespace tonb::cad2d::shell {

/**
 * @brief Public façade for the cad2d shell runtime.
 *
 * @details
 * The shell app owns the shell session plus the command and help registries.
 * It provides a minimal execution entry point for tokenised or line-based
 * shell commands while keeping the higher-level CAD logic in dedicated command
 * handlers.
 */
class TNBCAD2DSHELL_EXPORT ShellApp {
public:
    ShellApp();

    [[nodiscard]] static std::string_view module_name() noexcept;
    [[nodiscard]] bool has_foundation_support() const noexcept;

    [[nodiscard]] command::CommandRegistry& commands() noexcept;
    [[nodiscard]] const command::CommandRegistry& commands() const noexcept;

    [[nodiscard]] help::HelpRegistry& help() noexcept;
    [[nodiscard]] const help::HelpRegistry& help() const noexcept;

    [[nodiscard]] ShellSession& session() noexcept;
    [[nodiscard]] const ShellSession& session() const noexcept;

    /**
     * @brief Execute one already-tokenised shell command.
     */
    TNBCAD2DSHELL_ND_EXPORT command::CommandResult execute_tokens(
        const std::vector<std::string>& tokens,
        std::ostream* out = nullptr,
        std::ostream* err = nullptr);

    /**
     * @brief Tokenise and execute one shell command line.
     */
    TNBCAD2DSHELL_ND_EXPORT command::CommandResult execute_line(
        std::string_view line,
        std::ostream* out = nullptr,
        std::ostream* err = nullptr);

private:
    void register_core_commands_();

    ShellSession session_;
    command::CommandRegistry commands_;
    help::HelpRegistry help_;
};

} // namespace tonb::cad2d::shell

#endif // TONB_CAD2D_SHELL_SHELL_APP_HXX

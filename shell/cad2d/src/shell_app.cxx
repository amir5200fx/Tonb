#include <tonb/cad2d/shell/shell_app.hxx>

#include <utility>

#include <tonb/cad2d/shell/command/command_context.hxx>
#include <tonb/cad2d/shell/commands/shell_cmd_core.hxx>
#include <tonb/cad2d/shell/shell_tokenise.hxx>

namespace tonb::cad2d::shell {

    ShellApp::ShellApp() {
        register_core_commands_();
    }

    std::string_view ShellApp::module_name() noexcept {
        return "TonbCAD2dShell";
    }

    bool ShellApp::has_foundation_support() const noexcept {
#if defined(TNB_CAD2D_SHELL_HAS_FOUNDATION) && TNB_CAD2D_SHELL_HAS_FOUNDATION
        return true;
#else
        return false;
#endif
    }

    command::CommandRegistry& ShellApp::commands() noexcept {
        return commands_;
    }

    const command::CommandRegistry& ShellApp::commands() const noexcept {
        return commands_;
    }

    help::HelpRegistry& ShellApp::help() noexcept {
        return help_;
    }

    const help::HelpRegistry& ShellApp::help() const noexcept {
        return help_;
    }

    ShellSession& ShellApp::session() noexcept {
        return session_;
    }

    const ShellSession& ShellApp::session() const noexcept {
        return session_;
    }

    command::CommandResult ShellApp::execute_tokens(
        const std::vector<std::string>& tokens,
        std::ostream* out,
        std::ostream* err) {
        const command::CommandContext context{&session_, out, err};
        return commands_.dispatch(tokens, context);
    }

    command::CommandResult ShellApp::execute_line(
        std::string_view line,
        std::ostream* out,
        std::ostream* err) {
        const auto tokenised = tokenise_command_line(line);
        if (!tokenised.ok) {
            return command::CommandResult::failure(tokenised.error);
        }
        return execute_tokens(tokenised.tokens, out, err);
    }

    void ShellApp::register_core_commands_() {
        commands::register_core_commands(commands_, help_);
    }

} // namespace tonb::cad2d::shell

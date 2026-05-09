#include <tonb/cad2d/shell/commands/shell_cmd_core.hxx>

#include <sstream>
#include <string>
#include <vector>

#include <tonb/cad2d/shell/command/command_context.hxx>
#include <tonb/cad2d/shell/help/help_renderer.hxx>
#include <tonb/cad2d/shell/shell_session.hxx>
#include <tonb/foundation/cli/command_path.hxx>
#include <tonb/foundation/cli/help_renderer.hxx>

namespace tonb::cad2d::shell::commands {
    namespace {

        using command::CommandArgs;
        using command::CommandContext;
        using command::CommandResult;

        std::string render_status_text(const ShellSession& session) {
            const auto st = session.status();

            std::ostringstream out;
            out << "curve stores: " << st.curve_store_count << '\n';
            out << "active curve store: " << (st.active_curve_store ? *st.active_curve_store : std::string{"<none>"}) << '\n';
            out << "shapes: " << st.shape_count << '\n';
            out << "active shape: " << (st.active_shape ? *st.active_shape : std::string{"<none>"}) << '\n';
            out << "active shape curve store: "
                << (st.active_shape_curve_store ? *st.active_shape_curve_store : std::string{"<none>"}) << '\n';
            out << "primary selection: ";
            if (st.primary_selection) {
                out << st.primary_selection->shape_name << ':' << static_cast<int>(st.primary_selection->kind) << ':' << st.primary_selection->id;
            } else {
                out << "<none>";
            }
            out << '\n';
            out << "exit requested: " << (st.runtime.exit_requested ? "true" : "false") << '\n';
            out << "verbose: " << (st.runtime.verbose ? "true" : "false") << '\n';
            out << "echo commands: " << (st.runtime.echo_commands ? "true" : "false");
            return out.str();
        }

        CommandResult cmd_status(const CommandContext& context, const CommandArgs& args) {
            if (!args.empty()) {
                return CommandResult::failure("status: unexpected arguments");
            }
            if (context.session() == nullptr) {
                return CommandResult::failure("status: missing shell session");
            }
            return CommandResult::success(render_status_text(*context.session()));
        }

        CommandResult cmd_reset(const CommandContext& context, const CommandArgs& args) {
            if (!args.empty()) {
                return CommandResult::failure("reset: unexpected arguments");
            }
            if (context.session() == nullptr) {
                return CommandResult::failure("reset: missing shell session");
            }
            context.session()->reset();
            return CommandResult::success("session reset");
        }

        CommandResult cmd_quit(const CommandContext& context, const CommandArgs& args) {
            if (!args.empty()) {
                return CommandResult::failure("quit: unexpected arguments");
            }
            if (context.session() == nullptr) {
                return CommandResult::failure("quit: missing shell session");
            }
            context.session()->runtime().exit_requested = true;
            return CommandResult::success("exit requested");
        }

    } // namespace

    void register_core_commands(command::CommandRegistry& commands,
                                help::HelpRegistry& help_registry) {
        using foundation::cli::CommandPath;
        using help::CommandSpec;

        commands.add_command(command::CommandPath{"help"},
            [&help_registry](const CommandContext&, const CommandArgs& args) -> CommandResult {
                foundation::cli::RenderOptions options{};
                if (args.empty()) {
                    return CommandResult::success(help::render_help_root(help_registry, options));
                }
                std::vector<std::string> segs;
                segs.reserve(args.size());
                for (const auto& t : args.tokens()) {
                    segs.push_back(t);
                }
                const auto result = help::render_help(help_registry, segs, options);
                if (!result.ok) {
                    return CommandResult::failure(result.text);
                }
                return CommandResult::success(result.text);
            });
        help_registry.add_command(CommandSpec{
            .canonical_path = CommandPath{"help"},
            .domain = "core",
            .summary = "Show shell help",
            .usage = {"help", "help <command...>"},
            .examples = {"help", "help status"}
        });

        commands.add_command(command::CommandPath{"status"}, cmd_status);
        help_registry.add_command(CommandSpec{
            .canonical_path = CommandPath{"status"},
            .domain = "core",
            .summary = "Show current shell session status",
            .usage = {"status"}
        });

        commands.add_command(command::CommandPath{"reset"}, cmd_reset);
        help_registry.add_command(CommandSpec{
            .canonical_path = CommandPath{"reset"},
            .domain = "core",
            .summary = "Reset the shell session to its default empty state",
            .usage = {"reset"}
        });

        commands.add_command(command::CommandPath{"quit"}, cmd_quit);
        commands.add_alias(command::CommandPath{"exit"}, command::CommandPath{"quit"});
        help_registry.add_command(CommandSpec{
            .canonical_path = CommandPath{"quit"},
            .domain = "core",
            .summary = "Request shell termination",
            .usage = {"quit", "exit"},
            .notes = {"The alias 'exit' is equivalent to quit."},
            .aliases = {CommandPath{"exit"}}
        });
    }

} // namespace tonb::cad2d::shell::commands

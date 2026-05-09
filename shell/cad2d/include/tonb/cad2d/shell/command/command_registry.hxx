#pragma once
#ifndef TONB_CAD2D_SHELL_COMMAND_COMMAND_REGISTRY_HXX
#define TONB_CAD2D_SHELL_COMMAND_COMMAND_REGISTRY_HXX

#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include <tonb/cad2d/shell/command/command_args.hxx>
#include <tonb/cad2d/shell/command/command_context.hxx>
#include <tonb/cad2d/shell/command/command_node.hxx>
#include <tonb/cad2d/shell/module.hxx>

namespace tonb::cad2d::shell::command {

    using CommandHandler = std::function<CommandResult(const CommandContext&, const CommandArgs&)>;

    /**
     * @brief Resolved command-dispatch information.
     */
    struct CommandLookup {
        CommandPath invoked_path;
        CommandPath canonical_path;
        bool used_alias = false;
        std::size_t consumed_tokens = 0;
    };

    /**
     * @brief Hierarchical command registry and dispatcher for the cad2d shell.
     *
     * The registry stores canonical command paths plus optional aliases, resolves
     * the longest matching registered path against user tokens, and dispatches the
     * remaining tokens to the matching command handler.
     */
    class CommandRegistry {
    public:
        TNBCAD2DSHELL_EXPORT void add_command(CommandPath path, CommandHandler handler);
        TNBCAD2DSHELL_EXPORT void add_alias(CommandPath alias, const CommandPath& target);

        TNBCAD2DSHELL_ND_EXPORT std::vector<CommandNode> nodes() const;
        TNBCAD2DSHELL_ND_EXPORT std::vector<CommandPath> command_paths() const;
        TNBCAD2DSHELL_ND_EXPORT std::vector<CommandPath> aliases_for(const CommandPath& canonical) const;

        TNBCAD2DSHELL_ND_EXPORT std::optional<CommandLookup> resolve(const std::vector<std::string>& tokens) const;

        TNBCAD2DSHELL_ND_EXPORT CommandResult dispatch(const std::vector<std::string>& tokens,
                                                    const CommandContext& context) const;

    private:
        struct RegisteredCommand {
            CommandHandler handler;
        };

        static std::string key_from(const CommandPath& path);
        static bool starts_with(const std::vector<std::string>& tokens, const CommandPath& path);

        std::map<CommandPath, RegisteredCommand> commands_;
        std::map<CommandPath, CommandPath> aliases_;
    };

} // namespace tonb::cad2d::shell::command

#endif // TONB_CAD2D_SHELL_COMMAND_COMMAND_REGISTRY_HXX

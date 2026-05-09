#pragma once
#ifndef TONB_CAD2D_SHELL_COMMANDS_SHELL_CMD_CORE_HXX
#define TONB_CAD2D_SHELL_COMMANDS_SHELL_CMD_CORE_HXX

#include <tonb/cad2d/shell/command/command_registry.hxx>
#include <tonb/cad2d/shell/help/help_registry.hxx>
#include <tonb/cad2d/shell/module.hxx>

namespace tonb::cad2d::shell::commands {

/**
 * @brief Register the core shell commands and their help metadata.
 *
 * @details
 * This family provides the first user-facing shell commands: `help`, `status`,
 * `reset`, `quit`, and `exit`.
 */
TNBCAD2DSHELL_EXPORT void register_core_commands(
    command::CommandRegistry& commands,
    help::HelpRegistry& help);

} // namespace tonb::cad2d::shell::commands

#endif // TONB_CAD2D_SHELL_COMMANDS_SHELL_CMD_CORE_HXX

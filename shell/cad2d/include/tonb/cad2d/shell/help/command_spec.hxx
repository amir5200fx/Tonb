#pragma once
#ifndef TONB_CAD2D_SHELL_HELP_COMMAND_SPEC_HXX
#define TONB_CAD2D_SHELL_HELP_COMMAND_SPEC_HXX

#include <tonb/foundation/cli/command_spec.hxx>
#include <tonb/foundation/cli/command_registry.hxx>

namespace tonb::cad2d::shell::help {

    using CommandSpec = foundation::cli::CommandSpec;
    using CommandVisibility = foundation::cli::CommandVisibility;
    using CommandStability = foundation::cli::CommandStability;
    using DeprecationSpec = foundation::cli::DeprecationSpec;
    using CapabilitySpec = foundation::cli::CapabilitySpec;
    using OptionSpec = foundation::cli::OptionSpec;
    using NamespaceSpec = foundation::cli::NamespaceSpec;
    using ListingEntry = foundation::cli::ListingEntry;

} // namespace tonb::cad2d::shell::help

#endif // TONB_CAD2D_SHELL_HELP_COMMAND_SPEC_HXX

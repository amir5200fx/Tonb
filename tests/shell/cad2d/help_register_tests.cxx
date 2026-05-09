#include <gtest/gtest.h>

#include <tonb/cad2d/shell/help/help_registry.hxx>
#include <tonb/cad2d/shell/help/help_renderer.hxx>

namespace shell_help = tonb::cad2d::shell::help;
namespace fcli = tonb::foundation::cli;

namespace {
    shell_help::HelpRegistry make_registry() {
        shell_help::HelpRegistry reg;

        reg.add_namespace(fcli::NamespaceSpec{
            .path = fcli::CommandPath({"curve"}),
            .summary = "Curve commands"
        });
        reg.add_namespace(fcli::NamespaceSpec{
            .path = fcli::CommandPath({"shape"}),
            .summary = "Shape commands"
        });

        fcli::CommandSpec help_spec;
        help_spec.canonical_path = fcli::CommandPath({"help"});
        help_spec.domain = "shell";
        help_spec.summary = "Show command help";
        help_spec.usage = {"help", "help <command...>"};
        help_spec.examples = {"help", "help curve add"};
        reg.add_command(std::move(help_spec));

        fcli::CommandSpec curve_add_spec;
        curve_add_spec.canonical_path = fcli::CommandPath({"curve", "add"});
        curve_add_spec.domain = "curve";
        curve_add_spec.summary = "Add a curve to the active or named store";
        curve_add_spec.usage = {"curve add segment <store> <curve-id> x0 y0 x1 y1"};
        curve_add_spec.examples = {"curve add segment C1 1 0 0 1 0"};
        reg.add_command(std::move(curve_add_spec));

        return reg;
    }
}

TEST(cad2d_shell_help_registry, root_help_lists_top_level_groups) {
    const auto reg = make_registry();
    const std::string text = shell_help::render_help_root(reg);

    EXPECT_NE(text.find("root"), std::string::npos);
    EXPECT_NE(text.find("curve"), std::string::npos);
    EXPECT_NE(text.find("shape"), std::string::npos);
}

TEST(cad2d_shell_help_registry, command_help_renders_specific_command) {
    const auto reg = make_registry();
    const auto result = shell_help::render_help(reg, fcli::CommandPath({"curve", "add"}));

    ASSERT_TRUE(result.ok);
    EXPECT_NE(result.text.find("curve add"), std::string::npos);
    EXPECT_NE(result.text.find("Add a curve to the active or named store"), std::string::npos);
    EXPECT_NE(result.text.find("Usage"), std::string::npos);
}

TEST(cad2d_shell_help_registry, unknown_command_help_fails_cleanly) {
    const auto reg = make_registry();
    const auto result = shell_help::render_help(reg, fcli::CommandPath({"mesh", "build"}));

    EXPECT_FALSE(result.ok);
    EXPECT_NE(result.text.find("unknown help path"), std::string::npos);
}

#include <gtest/gtest.h>

#include <tonb/cad2d/shell/command/command_registry.hxx>

namespace {

    using tonb::cad2d::shell::command::CommandContext;
    using tonb::cad2d::shell::command::CommandPath;
    using tonb::cad2d::shell::command::CommandRegistry;
    using tonb::cad2d::shell::command::CommandResult;

    TEST(CommandRegistryTests, DispatchesSimpleCommand) {
        CommandRegistry registry;
        registry.add_command(CommandPath{"ping"},
                             [](const CommandContext&, const auto& args) {
                                 EXPECT_TRUE(args.empty());
                                 return CommandResult::success("pong");
                             });

        const auto result = registry.dispatch({"ping"}, CommandContext{});
        EXPECT_TRUE(result.ok);
        EXPECT_EQ(result.message, "pong");
    }

    TEST(CommandRegistryTests, DispatchesNestedCommandByLongestPrefix) {
        CommandRegistry registry;
        registry.add_command(CommandPath{"shape"},
                             [](const CommandContext&, const auto&) {
                                 return CommandResult::success("shape-root");
                             });
        registry.add_command(CommandPath{"shape", "create"},
                             [](const CommandContext&, const auto& args) {
                                 EXPECT_EQ(args.size(), 1u);
                                 EXPECT_EQ(args.at(0), "S1");
                                 return CommandResult::success("shape-create");
                             });

        const auto result = registry.dispatch({"shape", "create", "S1"}, CommandContext{});
        EXPECT_TRUE(result.ok);
        EXPECT_EQ(result.message, "shape-create");
    }

    TEST(CommandRegistryTests, UnknownCommandFailsCleanly) {
        CommandRegistry registry;
        registry.add_command(CommandPath{"ping"},
                             [](const CommandContext&, const auto&) {
                                 return CommandResult::success("pong");
                             });

        const auto result = registry.dispatch({"missing"}, CommandContext{});
        EXPECT_FALSE(result.ok);
        EXPECT_EQ(result.message, "unknown command");
    }

    TEST(CommandRegistryTests, AliasDispatchesDeterministically) {
        CommandRegistry registry;
        registry.add_command(CommandPath{"quit"},
                             [](const CommandContext&, const auto&) {
                                 return CommandResult::success("bye");
                             });
        registry.add_alias(CommandPath{"q"}, CommandPath{"quit"});

        const auto result = registry.dispatch({"q"}, CommandContext{});
        EXPECT_TRUE(result.ok);
        EXPECT_EQ(result.message, "bye");
    }

    TEST(CommandRegistryTests, ConflictingAliasRegistrationIsRejected) {
        CommandRegistry registry;
        registry.add_command(CommandPath{"shape", "create"},
                             [](const CommandContext&, const auto&) {
                                 return CommandResult::success();
                             });

        EXPECT_THROW(registry.add_alias(CommandPath{"shape", "create"}, CommandPath{"shape", "create"}), std::invalid_argument);
    }

} // namespace

#include <gtest/gtest.h>

#include <tonb/cad2d/shell/shell_tokenise.hxx>

namespace {

    using tonb::cad2d::shell::PositionalArgsView;
    using tonb::cad2d::shell::tokenise_command_line;

    TEST(ShellTokeniseTests, SimpleCommandTokenisesCorrectly) {
        const auto result = tokenise_command_line("shape create S1");
        ASSERT_TRUE(result.ok);
        ASSERT_EQ(result.tokens.size(), 3u);
        EXPECT_EQ(result.tokens[0], "shape");
        EXPECT_EQ(result.tokens[1], "create");
        EXPECT_EQ(result.tokens[2], "S1");
    }

    TEST(ShellTokeniseTests, QuotedTokenRemainsIntact) {
        const auto result = tokenise_command_line("shape create \"main shape\"");
        ASSERT_TRUE(result.ok);
        ASSERT_EQ(result.tokens.size(), 3u);
        EXPECT_EQ(result.tokens[2], "main shape");
    }

    TEST(ShellTokeniseTests, UnterminatedQuoteFailsCleanly) {
        const auto result = tokenise_command_line("shape create \"main shape");
        EXPECT_FALSE(result.ok);
        EXPECT_TRUE(result.tokens.empty());
        EXPECT_FALSE(result.error.empty());
    }

    TEST(ShellTokeniseTests, PositionalParseHelpersWorkDeterministically) {
        const auto result = tokenise_command_line("set count 42 3.5 yes");
        ASSERT_TRUE(result.ok);
        PositionalArgsView args(result.tokens);
        EXPECT_EQ(args.require(0, "command"), "set");
        EXPECT_EQ(args.parse_int(2, "count"), 42);
        EXPECT_DOUBLE_EQ(args.parse_double(3, "value"), 3.5);
        EXPECT_TRUE(args.parse_bool(4, "flag"));
    }

} // namespace

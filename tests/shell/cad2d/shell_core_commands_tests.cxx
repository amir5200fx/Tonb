#include <gtest/gtest.h>

#include <tonb/cad2d/shell/shell_app.hxx>

namespace tonb::cad2d::shell {
namespace {

TEST(ShellCoreCommandsTests, StatusReportsEmptySessionCorrectly) {
    ShellApp app;

    const auto result = app.execute_line("status");

    ASSERT_TRUE(result.ok);
    EXPECT_NE(result.message.find("curve stores: 0"), std::string::npos);
    EXPECT_NE(result.message.find("shapes: 0"), std::string::npos);
    EXPECT_NE(result.message.find("active shape: <none>"), std::string::npos);
    EXPECT_NE(result.message.find("active curve store: <none>"), std::string::npos);
}

TEST(ShellCoreCommandsTests, ResetClearsExistingObjects) {
    ShellApp app;
    app.session().curves().create("C1");
    app.session().curves().set_active("C1");
    app.session().shapes().create("S1");
    app.session().shapes().set_active("S1");
    app.session().shapes().bind_curve_store("S1", "C1");

    const auto result = app.execute_line("reset");

    ASSERT_TRUE(result.ok);
    EXPECT_EQ(app.session().curves().size(), 0u);
    EXPECT_EQ(app.session().shapes().size(), 0u);
    EXPECT_FALSE(app.session().curves().active_name().has_value());
    EXPECT_FALSE(app.session().shapes().active_name().has_value());
    EXPECT_FALSE(app.session().runtime().exit_requested);
}

TEST(ShellCoreCommandsTests, QuitSetsExitRequestedState) {
    ShellApp app;
    EXPECT_FALSE(app.session().runtime().exit_requested);

    const auto result = app.execute_line("quit");

    ASSERT_TRUE(result.ok);
    EXPECT_TRUE(app.session().runtime().exit_requested);
}

TEST(ShellCoreCommandsTests, ExitSetsExitRequestedState) {
    ShellApp app;
    EXPECT_FALSE(app.session().runtime().exit_requested);

    const auto result = app.execute_line("exit");

    ASSERT_TRUE(result.ok);
    EXPECT_TRUE(app.session().runtime().exit_requested);
}

TEST(ShellCoreCommandsTests, HelpExecutesThroughRegistry) {
    ShellApp app;

    const auto result = app.execute_line("help status");

    ASSERT_TRUE(result.ok);
    EXPECT_NE(result.message.find("status"), std::string::npos);
}

} // namespace
} // namespace tonb::cad2d::shell

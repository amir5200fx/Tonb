#include <gtest/gtest.h>

#include <tonb/cad2d/shell/shell_session.hxx>

namespace {

    using tonb::cad2d::shell::ShellSession;
    using tonb::cad2d::shell::session::EntityRef;

    TEST(Cad2dShellSessionTests, EmptySessionStatusIsDeterministic) {
        ShellSession session;

        const auto st = session.status();
        EXPECT_EQ(st.curve_store_count, 0u);
        EXPECT_FALSE(st.active_curve_store.has_value());
        EXPECT_EQ(st.shape_count, 0u);
        EXPECT_FALSE(st.active_shape.has_value());
        EXPECT_FALSE(st.active_shape_curve_store.has_value());
        EXPECT_FALSE(st.primary_selection.has_value());
        EXPECT_FALSE(st.runtime.exit_requested);
        EXPECT_FALSE(st.runtime.verbose);
        EXPECT_FALSE(st.runtime.echo_commands);
    }

    TEST(Cad2dShellSessionTests, ActiveContextsCanBeAssigned) {
        ShellSession session;

        session.curves().create("C1");
        session.curves().create("C2");
        session.curves().set_active("C2");

        session.shapes().create("S1");
        session.shapes().create("S2");
        session.shapes().set_active("S1");

        const auto st = session.status();
        ASSERT_TRUE(st.active_curve_store.has_value());
        EXPECT_EQ(*st.active_curve_store, "C2");
        ASSERT_TRUE(st.active_shape.has_value());
        EXPECT_EQ(*st.active_shape, "S1");
    }

    TEST(Cad2dShellSessionTests, ShapeToCurveBindingIsStoredAndReported) {
        ShellSession session;

        session.curves().create("CurvesA");
        session.shapes().create("ShapeA");
        session.shapes().bind_curve_store("ShapeA", "CurvesA");
        session.shapes().set_active("ShapeA");

        const auto st = session.status();
        ASSERT_TRUE(st.active_shape_curve_store.has_value());
        EXPECT_EQ(*st.active_shape_curve_store, "CurvesA");

        const auto& entry = session.shapes().require_entry("ShapeA");
        ASSERT_TRUE(entry.curve_store_name.has_value());
        EXPECT_EQ(*entry.curve_store_name, "CurvesA");
    }

    TEST(Cad2dShellSessionTests, ResetClearsDomainsDeterministically) {
        ShellSession session;

        session.curves().create("C1");
        session.curves().set_active("C1");

        session.shapes().create("S1");
        session.shapes().bind_curve_store("S1", "C1");
        session.shapes().set_active("S1");

        session.selection().set_primary(EntityRef{"S1", EntityRef::Kind::wire, tonb::cad2d::topo::Id{7}});
        session.runtime().exit_requested = true;
        session.runtime().verbose = true;
        session.runtime().echo_commands = true;

        session.reset();

        const auto st = session.status();
        EXPECT_EQ(st.curve_store_count, 0u);
        EXPECT_FALSE(st.active_curve_store.has_value());
        EXPECT_EQ(st.shape_count, 0u);
        EXPECT_FALSE(st.active_shape.has_value());
        EXPECT_FALSE(st.active_shape_curve_store.has_value());
        EXPECT_FALSE(st.primary_selection.has_value());
        EXPECT_FALSE(st.runtime.exit_requested);
        EXPECT_FALSE(st.runtime.verbose);
        EXPECT_FALSE(st.runtime.echo_commands);
    }

} // namespace

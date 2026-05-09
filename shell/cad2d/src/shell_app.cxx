#include <tonb/cad2d/shell/shell_app.hxx>

namespace tonb::cad2d::shell {

    std::string_view ShellApp::module_name() noexcept {
        return "TonbCAD2dShell";
    }

    bool ShellApp::has_foundation_support() noexcept {
#if defined(TNB_CAD2D_SHELL_HAS_FOUNDATION) && TNB_CAD2D_SHELL_HAS_FOUNDATION
        return true;
#else
        return false;
#endif
    }

} // namespace tonb::cad2d::shell

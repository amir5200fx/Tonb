#pragma once
#ifndef TONB_CAD2D_SHELL_SHELL_APP_HXX
#define TONB_CAD2D_SHELL_SHELL_APP_HXX

#include <string_view>

#include <tonb/cad2d/shell/module.hxx>

namespace tonb::cad2d::shell {

    /**
     * @brief Minimal public façade for the cad2d shell module.
     *
     * Issue 1 only establishes the root-level shell module, its public include
     * layout, and its build integration. Higher-level shell runtime features such
     * as session state, command dispatch, help registries, and CAD workflows are
     * intentionally deferred to later issues.
     */
    class ShellApp {
    public:
        ShellApp() = default;

        /**
         * @brief Return the public module name for the cad2d shell library.
         */
        static TNBCAD2DSHELL_EXPORT std::string_view module_name() noexcept;

        /**
         * @brief Report whether the shell was built with the Tonb foundation layer
         * available as a linked dependency.
         */
        static TNBCAD2DSHELL_EXPORT bool has_foundation_support() noexcept;
    };

} // namespace tonb::cad2d::shell

#endif // TONB_CAD2D_SHELL_SHELL_APP_HXX

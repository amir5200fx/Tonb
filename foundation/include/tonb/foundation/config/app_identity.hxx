/**
* @file app_identity.hxx
 * @brief Application identity used to derive platform-conventional config and data paths.
 *
 * @details
 * Foundation modules should not hardcode a specific product name such as
 * iXfract or Tonb. Instead they consume an AppIdentity value describing the
 * host application. This makes the foundation layer reusable across multiple
 * command-line tools, desktop applications, and Python-backed front ends.
 */
#pragma once
#ifndef TONB_FOUNDATION_CONFIG_APP_IDENTITY_HXX
#define TONB_FOUNDATION_CONFIG_APP_IDENTITY_HXX

#include <string>

namespace tonb::foundation::config {

    /**
     * @brief Stable application identity for config/data path resolution.
     *
     * @details
     * The @c app_dir_name field should be filesystem-safe and stable across
     * releases. It is used in platform-standard directories such as
     * %APPDATA%/<app_dir_name> and ~/.config/<app_dir_name>.
     */
    struct AppIdentity {
        /** Human-readable product name used in diagnostics and documentation. */
        std::string app_name;

        /** Stable lowercase-or-safe directory name used on disk. */
        std::string app_dir_name;
    };

} // namespace tonb::foundation::config

#endif // TONB_FOUNDATION_CONFIG_APP_IDENTITY_HXX

/**
* @file workspace_default.hxx
 * @brief Platform-conventional default workspace root resolution.
 *
 * @details
 * This module derives the default workspace root from an explicit AppIdentity.
 * That generalises the old iXfract-specific default location into a reusable
 * foundation service.
 */
#pragma once
#ifndef TONB_FOUNDATION_WORKSPACE_WORKSPACE_DEFAULT_HXX
#define TONB_FOUNDATION_WORKSPACE_WORKSPACE_DEFAULT_HXX

#include <tonb/foundation/config/app_identity.hxx>
#include <tonb/foundation/module.hxx>

#include <filesystem>

namespace tonb::foundation::workspace {

    /**
     * @brief Return the platform-default workspace root path for the given app.
     *
     * @param app Host application identity.
     * @return Data-root/<app>/workspace on the current platform.
     */
    TNBFOUND_ND_EXPORT std::filesystem::path default_workspace_root(
        const tonb::foundation::config::AppIdentity& app);

} // namespace tonb::foundation::workspace

#endif // TONB_FOUNDATION_WORKSPACE_WORKSPACE_DEFAULT_HXX

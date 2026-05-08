/**
* @file workspace_persist.hxx
 * @brief Persistence helpers for resolving and storing the active workspace root.
 *
 * @details
 * This module keeps workspace-root persistence outside the Workspace path model
 * itself. It allows shell or GUI front ends to remember the last active
 * workspace while keeping the core path logic deterministic and side-effect free.
 */
#pragma once
#ifndef TONB_FOUNDATION_WORKSPACE_WORKSPACE_PERSIST_HXX
#define TONB_FOUNDATION_WORKSPACE_WORKSPACE_PERSIST_HXX

#include <tonb/foundation/config/app_identity.hxx>
#include <tonb/foundation/module.hxx>

#include <filesystem>

namespace tonb::foundation::workspace {

    /**
     * @brief Save the last active workspace root for the given app.
     * @param app Host application identity.
     * @param root Workspace root to persist.
     */
    TNBFOUND_EXPORT void save_workspace_root(
        const tonb::foundation::config::AppIdentity& app,
        const std::filesystem::path& root);

    /**
     * @brief Clear the persisted last workspace root for the given app.
     */
    TNBFOUND_EXPORT void clear_workspace_root(
        const tonb::foundation::config::AppIdentity& app) noexcept;

    /**
     * @brief Load the persisted last workspace root, if any.
     */
    TNBFOUND_ND_EXPORT std::filesystem::path load_workspace_root_if_any(
        const tonb::foundation::config::AppIdentity& app);

    /**
     * @brief Resolve the active workspace root using environment override then config.
     *
     * @details
     * Resolution order:
     * - <APP_DIR_NAME>_WORKSPACE environment variable, uppercased and sanitised
     * - persisted user config
     *
     * For example, app_dir_name="tonb" resolves environment variable
     * TONB_WORKSPACE.
     */
    TNBFOUND_ND_EXPORT std::filesystem::path resolve_workspace_root_if_any(
        const tonb::foundation::config::AppIdentity& app);

} // namespace tonb::foundation::workspace

#endif // TONB_FOUNDATION_WORKSPACE_WORKSPACE_PERSIST_HXX

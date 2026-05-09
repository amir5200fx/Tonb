/**
 * @file app_config.hxx
 * @brief Minimal, versioned, per-user foundation configuration.
 *
 * @details
 * This module generalises the persistence pattern previously used by iXfract so
 * it can serve future applications such as Tonb. The configuration remains
 * intentionally narrow:
 * - last workspace root
 * - last shell current working directory relative to the workspace
 *
 * The configuration location is derived from an explicit AppIdentity rather
 * than hardcoded product names.
 */
#pragma once
#ifndef TONB_FOUNDATION_CONFIG_APP_CONFIG_HXX
#define TONB_FOUNDATION_CONFIG_APP_CONFIG_HXX

#include <tonb/foundation/config/app_identity.hxx>
#include <tonb/foundation/module.hxx>

#include <filesystem>
#include <optional>

namespace tonb::foundation::config {

    /**
     * @brief Small value type representing persisted user-level configuration.
     *
     * @details
     * Invariants:
     * - workspace_last_root_, when set, is stored as a normalised absolute path.
     * - shell_last_cwd_, when set, is stored as a normalised relative path.
     */
    class AppConfig {
    public:
        /** @brief Return the schema version written by save(). */
        static constexpr int schema_version() noexcept { return 1; }

        /**
         * @brief Compute the per-user config file path for the given application.
         *
         * @param app Host application identity.
         * @return Config file path, typically ending in config.json.
         */
        static TNBFOUND_EXPORT std::filesystem::path config_path(const AppIdentity& app);

        /**
         * @brief Load persisted config for the given application.
         *
         * @param app Host application identity.
         * @return Loaded config, or a default config when absent or malformed.
         */
        static TNBFOUND_EXPORT AppConfig load(const AppIdentity& app);

        /**
         * @brief Persist this configuration for the given application.
         *
         * @param app Host application identity.
         * @throws std::runtime_error If the config cannot be written.
         */
        TNBFOUND_EXPORT void save(const AppIdentity& app) const;

        /** @brief Return the last persisted workspace root, if any. */
        TNBFOUND_ND_EXPORT std::optional<std::filesystem::path> workspace_last_root() const;

        /**
         * @brief Set the last persisted workspace root.
         * @param root Absolute or relative path that will be stored as absolute.
         */
        TNBFOUND_EXPORT void set_workspace_last_root(const std::filesystem::path& root);

        /** @brief Clear the persisted workspace root. */
        TNBFOUND_EXPORT void clear_workspace_last_root();

        /** @brief Return the last persisted shell cwd, if any. */
        TNBFOUND_ND_EXPORT std::optional<std::filesystem::path> shell_last_cwd() const;

        /**
         * @brief Set the last persisted shell cwd.
         * @param cwd Workspace-relative path.
         * @throws std::invalid_argument If @p cwd is absolute.
         */
        TNBFOUND_EXPORT void set_shell_last_cwd(const std::filesystem::path& cwd);

        /** @brief Clear the persisted shell cwd. */
        TNBFOUND_EXPORT void clear_shell_last_cwd();

    private:
        std::optional<std::filesystem::path> workspace_last_root_;
        std::optional<std::filesystem::path> shell_last_cwd_;
    };

    /**
     * @brief Return the platform-conventional per-user config root directory.
     *
     * @param app Host application identity.
     * @return Root config directory, not the config file path.
     */
    TNBFOUND_ND_EXPORT std::filesystem::path config_root_dir(const AppIdentity& app);

    /**
     * @brief Return the platform-conventional per-user data root directory.
     *
     * @param app Host application identity.
     * @return Root data directory suitable for workspaces and caches.
     */
    TNBFOUND_EXPORT std::filesystem::path data_root_dir(const AppIdentity& app);

} // namespace tonb::foundation::config

#endif // TONB_FOUNDATION_CONFIG_APP_CONFIG_HXX

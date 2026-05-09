/**
 * @file workspace_lifecycle.hxx
 * @brief Session-level workspace lifecycle management.
 *
 * @details
 * This module manages the active workspace for an application session. It is a
 * foundation-grade version of the iXfract workspace lifecycle helper, but it no
 * longer hardcodes iXfract-specific config or path conventions.
 */
#pragma once
#ifndef TONB_FOUNDATION_WORKSPACE_WORKSPACE_LIFECYCLE_HXX
#define TONB_FOUNDATION_WORKSPACE_WORKSPACE_LIFECYCLE_HXX

#include <tonb/foundation/config/app_identity.hxx>
#include <tonb/foundation/workspace/workspace.hxx>

#include <filesystem>
#include <optional>
#include <string>

namespace tonb::foundation::workspace {

/**
 * @brief Session-level workspace lifecycle state machine.
 *
 * @details
 * State:
 * - unset: no workspace active
 * - set: Workspace model exists and a canonical root string is cached for status
 */
class WorkspaceLifecycle {
public:
    /**
     * @brief Construct a lifecycle helper bound to a host application identity.
     * @param app Host application identity used for persistence.
     */
    explicit WorkspaceLifecycle(tonb::foundation::config::AppIdentity app);

    /** @brief Return true if a workspace is active. */
    TNB_NODISCARD bool has_workspace() const noexcept { return ws_.has_value(); }

    /** @brief Return the active workspace model. */
    TNBFOUND_ND_EXPORT const Workspace& workspace() const;

    /** @brief Return the canonical root string cached at init time. */
    TNBFOUND_ND_EXPORT const std::string& canonical_root_string() const;

    /**
     * @brief Initialise the workspace at the given root.
     *
     * @details
     * Creates the root and required area directories, persists the root, and
     * rejects silent overrides of an already active but different workspace.
     */
    TNBFOUND_EXPORT void init(const std::filesystem::path& root);

    /**
     * @brief Try to initialise from environment override or persisted config.
     * @return True if a workspace was loaded; false otherwise.
     */
    TNBFOUND_ND_EXPORT bool init_from_saved_or_environment();

    /**
     * @brief Reset the session workspace state and clear persisted root.
     *
     * @details
     * The method is noexcept by design and does not delete any on-disk
     * workspace contents.
     */
    TNBFOUND_EXPORT void reset() noexcept;

private:
    static void create_required_dirs(const Workspace& ws);
    static std::string compute_canonical_root_string(const std::filesystem::path& root);

    tonb::foundation::config::AppIdentity app_;
    std::optional<Workspace> ws_;
    std::string canonical_root_;
};

} // namespace tonb::foundation::workspace

#endif // TONB_FOUNDATION_WORKSPACE_WORKSPACE_LIFECYCLE_HXX

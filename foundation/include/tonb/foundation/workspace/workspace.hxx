/**
 * @file workspace.hxx
 * @brief Deterministic workspace path model and traversal-safe path resolution.
 *
 * @details
 * This module is the geometry/application-neutral successor to the iXfract
 * workspace path model. It defines a stable directory layout rooted at a user-
 * selected workspace directory and provides lexical path resolution utilities
 * without performing implicit filesystem writes.
 */
#pragma once
#ifndef TONB_FOUNDATION_WORKSPACE_WORKSPACE_HXX
#define TONB_FOUNDATION_WORKSPACE_WORKSPACE_HXX

#include <tonb/foundation/module.hxx>

#include <filesystem>

namespace tonb::foundation::workspace {

    /**
     * @brief Standard storage areas inside a workspace root.
     */
    enum class Area {
        export_,
        dump_,
        logs_,
        session_
    };

    /**
     * @brief Deterministic workspace path model.
     *
     * @details
     * Invariants:
     * - root_ is not empty.
     * - root_ is absolute.
     * - root_ is lexically normalised.
     * - constructing the model does not create directories on disk.
     */
    class Workspace {
    public:
        /**
         * @brief Construct a workspace rooted at the provided path.
         * @param root Absolute or relative root path.
         * @throws std::invalid_argument If the path is empty or invalid.
         */
        explicit TNBFOUND_EXPORT Workspace(const std::filesystem::path& root);

        /** @brief Return the normalised absolute workspace root path. */
        TNB_NODISCARD const std::filesystem::path& root() const noexcept { return root_; }

        /**
         * @brief Return the directory for a standard workspace area.
         * @param a Workspace area.
         * @return Absolute, lexically normalised area path.
         */
        TNBFOUND_ND_EXPORT std::filesystem::path dir(Area a) const;

        TNB_NODISCARD std::filesystem::path export_dir() const { return dir(Area::export_); }
        TNB_NODISCARD std::filesystem::path dump_dir() const { return dir(Area::dump_); }
        TNB_NODISCARD std::filesystem::path logs_dir() const { return dir(Area::logs_); }
        TNB_NODISCARD std::filesystem::path session_dir() const { return dir(Area::session_); }

        /**
         * @brief Return the default failure-bundle directory under dump/.
         */
        TNBFOUND_ND_EXPORT std::filesystem::path failure_bundles_dir() const;

        /**
         * @brief Resolve a path under the given workspace area.
         *
         * @details
         * If @p p is absolute, it is returned in normalised form. If @p p is
         * relative, the result must stay under the chosen area directory.
         */
        TNBFOUND_ND_EXPORT std::filesystem::path resolve_under(Area a, const std::filesystem::path& p) const;

        /**
         * @brief Resolve a path under an explicit base directory.
         *
         * @param base Absolute base directory.
         * @param p Absolute or relative user path.
         * @throws std::invalid_argument If @p base is not absolute or @p p is empty.
         * @throws std::logic_error If a relative path escapes the base directory.
         */
        TNBFOUND_ND_EXPORT std::filesystem::path resolve_under(const std::filesystem::path& base, const std::filesystem::path& p) const;

    private:
        void validate() const;
        std::filesystem::path root_;
    };

} // namespace tonb::foundation::workspace

#endif // TONB_FOUNDATION_WORKSPACE_WORKSPACE_HXX

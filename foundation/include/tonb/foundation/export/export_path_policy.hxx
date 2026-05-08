/**
* @file export_path_policy.hxx
 * @brief Deterministic export path resolution policy for Tonb workspace exports.
 *
 * @details
 * This module defines a deterministic export path resolution policy used by Tonb
 * exporters and shell commands to resolve user-provided output paths into a single
 * unambiguous target bundle root directory.
 *
 * Resolution priority:
 * (1) Absolute path respected:
 *     - If the user supplies an absolute path, it is used as the base location.
 * (2) Relative path resolved under <workspace>/<area>/<namespace>/:
 *     - If the user supplies a relative path, it is resolved under:
 *       <workspace.root>/<area>/<namespace>/...
 * (3) Missing filename triggers auto-generated bundle:
 *     - If the user does not supply a path, or supplies a directory-like path
 *       (no meaningful filename), a deterministic bundle folder name is generated
 *       and appended.
 *
 * Determinism policy:
 * - No timestamps, random IDs, filesystem enumeration, or global mutable state.
 * - Auto-generated names must be derived solely from explicit inputs.
 *
 * Security policy:
 * - Namespace is validated to prevent path traversal or directory injection.
 * - Relative user paths are subject to traversal protection via Workspace::resolve_under.
 *
 * Non-goals:
 * - Directory creation on disk.
 * - Bundle payload file naming.
 * - Manifest writing.
 * - Hashing.
 */
#pragma once
#ifndef TONB_FOUNDATION_EXPORT_EXPORT_PATH_POLICY_HXX
#define TONB_FOUNDATION_EXPORT_EXPORT_PATH_POLICY_HXX

#include <tonb/foundation/workspace/workspace.hxx>

#include <optional>
#include <string>
#include <string_view>

namespace tonb::foundation::exporting {
    /**
     * @brief Options for deterministic auto-generation of bundle directory names.
     *
     * @details
     * Auto-generation must be deterministic. To ensure deterministic uniqueness inside
     * a single session, callers should supply a stable sequence number (for example,
     * the shell command sequence id or a recorder index).
     *
     * This type does not access the filesystem and does not attempt to avoid collisions.
     * Collision avoidance can be handled at a higher layer if needed.
     */
    struct ExportAutoNameOptions {
        /**
         * @brief Deterministic sequence number for the export request.
         *
         * @details
         * This is expected to be stable for a given command line execution.
         * For example, the shell command log sequence number.
         */
        std::uint64_t sequence = 0;

        /**
         * @brief Namespace identifier (e.g., "inp", "surf", "crack", "blade").
         *
         * @details
         * This is used as a semantic tag in the auto-generated directory name
         * and must match the namespace passed to resolve_export_bundle_root.
         */
        std::string ns;

        /**
         * @brief Verb tag to include in the auto-generated directory name.
         *
         * @details
         * Typical values: "export", "dump", "vtk", "bundle".
         * Must be ASCII-safe; sanitisation is applied.
         */
        std::string verb = "export";

        /**
         * @brief Optional short input tag (e.g., model name without extension).
         *
         * @details
         * This must be a short human-readable identifier only. It is not a path.
         * Example: "model", "case17".
         */
        std::string input_tag;

        /**
         * @brief Workspace area under which the bundle root should be resolved.
         *
         * @details
         * Relative bundle roots are resolved under:
         *   <workspace.root>/<area>/<namespace>/
         *
         * Default is the user-facing export area.
         */
        workspace::Area area = workspace::Area::export_;
    };

    /**
     * @brief Deterministic export bundle resolution policy.
     *
     * @details
     * This is a pure policy component. It:
     * - validates namespace
     * - resolves relative paths under <workspace>/<area>/<namespace>/
     * - treats directory-like paths as requiring an auto-generated leaf folder
     * - enforces traversal protection for relative paths
     *
     * It does not create any directories.
     */
    class ExportPathPolicy {
    public:

        /**
         * @brief Resolve the bundle root directory for an export operation.
         *
         * @details
         * Inputs:
         *  - Workspace: provides workspace area roots and traversal protection helpers.
         *  - namespace: determines namespace subdirectory when resolving relative paths.
         *  - user_path:
         *      - if absent -> auto bundle folder name under <area>/<namespace>/
         *      - if absolute -> respected; if directory-like -> append auto bundle folder
         *      - if relative -> resolved under <area>/<namespace>/; if directory-like -> append auto folder
         *
         * Missing filename detection:
         *  - If the path has no meaningful filename component (empty, ".", "..", or ends
         *    in a directory-like form), it is treated as a directory and an auto folder is appended.
         *
         * @param ws Active workspace.
         * @param ns Namespace name (e.g., "inp","surf"). Must be safe.
         * @param user_path Optional user-provided output path.
         * @param auto_opt Options for deterministic auto naming.
         *
         * @return Absolute bundle root directory path.
         *
         * @throws std::invalid_argument
         * If ns is empty or unsafe, or if auto_opt.ns mismatches ns when provided.
         *
         * @throws std::logic_error
         * If a relative path escapes the base directory (traversal attempt).
         */
        static TNBFOUND_EXPORT std::filesystem::path resolve_export_bundle_root(
            const workspace::Workspace& ws,
            std::string_view ns,
            const std::optional<std::filesystem::path>& user_path,
            const ExportAutoNameOptions& auto_opt);

    private:
        /**
         * @brief Validate that a namespace token is safe to use as a directory name.
         *
         * @details
         * This rejects:
         * - empty string
         * - any path separators
         * - "." or ".."
         * - tokens containing traversal segments
         *
         * @param ns Namespace token.
         *
         * @throws std::invalid_argument on violation.
         */
        static void validate_namespace(std::string_view ns);

        /**
         * @brief Determine whether a path has a meaningful filename component.
         *
         * @details
         * "Meaningful filename" means:
         * - path.filename() is not empty
         * - filename != "."
         * - filename != ".."
         *
         * This is used to decide whether a path should be treated as a directory-like path.
         *
         * @param p Path to check.
         * @return True if p has a meaningful filename, false otherwise.
         */
        static bool has_meaningful_filename(const std::filesystem::path& p);

        /**
         * @brief Build a deterministic auto-generated bundle directory name.
         *
         * @details
         * Format (deterministic):
         * - <seq_padded>__<ns>-<verb>__<input_tag_optional>
         *
         * Example:
         * - 000042__inp-export__model
         *
         * @param opt Auto name options.
         * @return Directory name (single path segment).
         */
        static std::string make_auto_bundle_dir_name(const ExportAutoNameOptions& opt);

        /**
         * @brief Sanitise a token for safe use in a single path segment.
         *
         * @details
         * The sanitisation is intentionally conservative:
         * - replace whitespace with '_'
         * - replace '/', '\\' with '_'
         * - remove leading/trailing underscores
         *
         * This function does not attempt full unicode normalisation. It is intended
         * for deterministic, human-readable tags, not for security-critical validation.
         *
         * @param s Input string.
         * @return Sanitised string.
         */
        static std::string sanitise_token(std::string s);
    };
}

#endif // TONB_FOUNDATION_EXPORT_EXPORT_PATH_POLICY_HXX
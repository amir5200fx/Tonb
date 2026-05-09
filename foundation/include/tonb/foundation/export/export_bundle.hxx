/**
* @file export_bundle.hxx
 * @brief Structured export bundle model for deterministic, self-describing artefacts.
 *
 * @details
 * This module defines the core "export bundle" container abstraction used by Tonb
 * to produce professional-grade output artefacts.
 *
 * An export bundle is a directory rooted at an absolute path which contains:
 *  - One or more payload files (e.g. VTK, CSV, JSON sidecars).
 *  - A manifest (JSON) describing provenance and outputs (schema formalised in the manifest schema).
 *  - Optional integrity metadata (hashes, sizes) (hash computation integrated later).
 *
 * This issue (the foundational export-bundle design) provides the model and validation rules only:
 *  - No filesystem writes occur here.
 *  - No directory creation.
 *  - No hashing implementation.
 *
 * Determinism requirements:
 *  - Bundle outputs are stored in insertion order only (std::vector).
 *  - serialisation utilities must preserve deterministic key ordering.
 *  - No hash-based containers inside the model.
 *
 * No-partial-artefacts requirement (by design):
 *  - This module introduces a transaction plan that distinguishes between:
 *      - staging_root: where a writer would write intermediate files
 *      - final_root: where the bundle become visible
 *  - Atomic promotion from staging to final is implemented in the atomic writer layer
 *
 * Export vs dump separation:
 * - BundleKind explicitly distinguishes user-facing exports from internal debug dumps.
 * - Downstream writes must treat them differently (directory roots, naming, retention).
 */
#pragma once
#ifndef TONB_FOUNDATION_EXPORT_EXPORT_BUNDLE_HXX
#define TONB_FOUNDATION_EXPORT_EXPORT_BUNDLE_HXX

#include <tonb/foundation/module.hxx>

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace tonb::foundation::exporting {
    /**
     * @brief Bundle classification distinguishing user-facing exports from internal dumps.
     *
     * @details
     * This makes the separation explicit at the model level.
     *  - export_ bundles are intended as deliverables.
     *  - dump_ bundles are intended for internal diagnostics and visual inspection.
     */
    enum class BundleKind {
        export_,
        dump_
    };

    /**
     * @brief Known output file "kinds" for bundle payload classification.
     *
     * @details
     * This is intentionally lightweight and extensible. It is not a MIME type.
     * It enables consistent manifest content and downstream tooling.
     */
    enum class OutputKind {
        unknown,
        vtk_polydata,
        vtk_unstructured_grid,
        abaqus_inp,
        json,
        csv,
        txt
    };

    /**
     * @brief A single output file entry within an ExportBundle.
     *
     * @details
     * OutputFile tracks bundle-relative payload paths and optional integrity metadata.
     *
     * Invariants:
     *  - path is relative to ExportBundle root (must not be absolute).
     *  - path must not escape the bundle root (no traversal via ",,").
     *  - deterministic ordering is preserved by storing outputs in a vector.
     */
    struct OutputFile {
        /**
         * @brief Path relative to bundle root.
         *
         * @note
         * This must be relative path (no root name/path) and must not contain traversal
         * that escapes the bundle root.
         */
        std::filesystem::path path;

        /**
         * @brief Output kind classification.
         */
        OutputKind kind = OutputKind::unknown;

        /**
         * @brief Optional one-line description for human readability.
         */
        std::string description;

        /**
         * @brief Optional SHA256 hex string (computed elsewhere).
         *
         * @details
         * This module does not compute hashes. Writers may populate this field.
         */
        std::optional<std::string> sha256;

        /**
         * @brief Optional byte size of the payload (computed elsewhere).
         */
        std::optional<std::uint64_t> bytes;
    };

    /**
     * @brief Manifest schema v0.1 for export bundles.
     *
     * @details
     * Required fields:
     * - schema_version (wire value is "0.1")
     * - created_utc (ISO-8601 UTC string)
     * - tool: name, version, git_commit
     * - context: namespace, command, argv, cwd, workspace_root
     * - input provenance
     * - domain state summary
     * - outputs[]
     *
     * Deterministic JSON ordering:
     * Keys are emitted in a fixed order:
     *  1) schema_version
     *  2) created_utc
     *  3) tool
     *  4) context
     *  5) input
     *  6) domain
     *  7) outputs
     *  8) extensions
     *
     * Schema versioning rules:
     * - The JSON field "schema_version" is a string. For this schema it is "0.1".
     * - Patch updates within 0.1 must be backward compatible (additive only).
     * - Breaking changes require "0.2" or "1.0" etc.
     *
     * Forward compatibility strategy:
     * - Unknown fields must be ignored by readers.
     * - "extensions" provides a deterministic insertion-ordered map for future additions.
     *   Each extension stores a key and a raw JSON value string.
     */
    class Manifest {
    public:
        /**
         * @brief Wire schema version for JSON serialisation ("0.1").
         */
        static constexpr const char* schema_version_string() noexcept {return "0.1";}
        /**
         * @brief Construct an empty manifest with schema version 0.
         */
        TNBFOUND_EXPORT Manifest();

        /**
         * @brief Return legacy numeric schema version (1 corresponds to wire "0.1").
         *
         * @details
         * This exists for minimal disruption of earlier deterministic code.
         * Writers should treat schema_version_string() as authoritative on the wire.
         */
        TNB_NODISCARD int schema_version() const noexcept {return schema_version_;}

        /**
         * @brief Set schema version value.
         *
         * @throws std::invalid_argument If v is negative.
         */
        TNBFOUND_EXPORT void set_schema_version(int v);

        /**
         * @brief Set creation timestamp in UTC (ISO-8601 string).
         *
         * @note This module does not generate timestamps; caller must provide the value.
         *
         * @throws std::invalid_argument If s is empty.
         */
        TNBFOUND_EXPORT void set_created_utc(std::string s);

        /**
         * @brief Get creation timestamp in UTC.
         */
        TNB_NODISCARD const std::string& created_utc() const noexcept {return created_utc_;}

        /**
         * @brief Set tool name (e.g. "ixrupt").
         *
         * @throws std::invalid_argument If s is empty.
         */
        TNBFOUND_EXPORT void set_tool_name(std::string s);

        /**
         * @brief Set tool version string.
         *
         * @throws std::invalid_argument If s is empty.
         */
        TNBFOUND_EXPORT void set_tool_version(std::string s);

        /**
         * @brief Set git commit hash string.
         *
         * @throws std::invalid_argument If s is empty.
         */
        TNBFOUND_EXPORT void set_git_commit(std::string s);

        /**
         * @brief Set shell namespace for this export (e.g. "inp", "surf").
         *
         * @throws std::invalid_argument If s is empty.
         */
        TNBFOUND_EXPORT void set_namespace(std::string s);

        /**
         * @brief Set canonical command string (e.g. "inp export").
         *
         * @throws std::invalid_argument If s is empty.
         */
        TNBFOUND_EXPORT void set_command(std::string s);

        /**
         * @brief Set argv array for the command invocation.
         *
         * @details
         * argv must preserve user token ordering.
         */
        TNBFOUND_EXPORT void set_argv(std::vector<std::string> v);

        /**
         * @brief Set current working directory string.
         *
         * @throws std::invalid_argument If s is empty.
         */
        TNBFOUND_EXPORT void set_cwd(std::string s);

        /**
         * @brief Set workspace root string.
         *
         * @throws std::invalid_argument If s is empty.
         */
        TNBFOUND_EXPORT void set_workspace_root(std::string s);

        /**
         * @brief Input provenance block.
         */
        struct InputProvenance {
            std::string id;
            std::string kind;
            std::optional<std::string> sha256;
            std::optional<std::uint64_t> bytes;
            std::string note;
        };

        /**
         * @brief Set input provenance.
         *
         * @throws std::invalid_argument If required fields are empty.
         */
        TNBFOUND_EXPORT void set_input_provenance(InputProvenance p);

        /**
         * @brief Domain state summary block.
         */
        struct DomainSummary {
            std::string domain;
            std::string status;
            std::vector<std::string> summary_lines;

            struct KeyValue {
                std::string key;
                std::string value;
            };
            std::vector<KeyValue> key_values;
        };

        /**
         * @brief Set domain state summary.
         *
         * @throws std::invalid_argument If required fields are empty or keys duplicate.
         */
        TNBFOUND_EXPORT void set_domain_summary(DomainSummary s);

        /**
         * @brief Manifest-facing output entry.
         */
        struct ManifestOutput {
            std::filesystem::path path;
            OutputKind kind = OutputKind::unknown;
            std::string description;
            std::optional<std::uint64_t> bytes;
            std::optional<std::string> sha256;
        };

        /**
         * @brief Set outputs list (preserves order).
         *
         * @throws std::invalid_argument If outputs is empty or contains invalid paths.
         * @throws std::logic_error If any path contains traversal "..".
         */
        TNBFOUND_EXPORT void set_outputs(std::vector<ManifestOutput> outputs);

        /**
         * @brief Populate outputs[] deterministically from a bundle's outputs.
         *
         * @details
         * This copies output path/kind/description and integrity metadata (bytes/sha256).
         * Intended for use by writers immediately before writing manifest.json.
         */
        TNBFOUND_EXPORT void sync_outputs_from_bundle(const class ExportBundle& bundle);

        /**
         * @brief Extension entry for forward compatibility.
         *
         * @details
         * value_json must be a valid JSON value string. It is not parsed here.
         */
        struct Extension {
            std::string key;
            std::string value_json;
        };

        /**
         * @brief Add an extension (in insertion order).
         *
         * @throws std::invalid_argument If key/value are empty.
         * @throws std::logic_error If key already exists.
         */
        TNBFOUND_EXPORT void add_extension(Extension e);

        /**
         * @brief Deterministically serialise to JSON.
         *
         * @details
         * The JSON key ordering is fixed. Values are JSON-escaped.
         * This is a minimal deterministic serializer; the manifest schema will formalise schema.
         *
         * @return JSON string (UTF-8) with trailing newline.
         */
        TNBFOUND_ND_EXPORT std::string to_json() const;

        /**
         * @brief Validate required fields and invariants.
         *
         * @throws std::logic_error If required fields are missing.
         * @throws std::invalid_argument For malformed content.
         */
        TNBFOUND_EXPORT void validate() const;
    private:
        static void require_non_empty(std::string_view v, std::string_view what);
        static bool contains_traversal(const std::filesystem::path& p);
        static std::string kind_to_string(OutputKind k);

        int schema_version_ = 1; // legacy numeric mapping for wire "0.1"
        std::string created_utc_;

        std::string tool_name_;
        std::string tool_version_;
        std::string git_commit_;

        std::string ns_;
        std::string command_;

        std::vector<std::string> argv_;
        std::string cwd_;
        std::string workspace_root_;

        std::optional<InputProvenance> input_;
        std::optional<DomainSummary> domain_;
        std::vector<ManifestOutput> outputs_;
        std::vector<Extension> extensions_;
    };

    /**
     * @brief ExportBundle: in-memory representation of a bundle rooted at an absolute directory.
     *
     * @details
     * ExportBundle models:
     *  - root directory (absolute)
     *  - bundle kind (export vs dump)
     *  - list of output files(payload tracking
     *  - manifest object (metadata support)
     *
     * It provides validation and deterministic behaviour by design.
     * It does not create directories or write files.
     */
    class ExportBundle {
    public:
        /**
         * @brief Construct a bundle rooted at @p root with the given kind.
         *
         * @param kind BundleKind.
         * @param root Absolute root directory path of the bundle.
         *
         * @throws std::invalid_argument If root it empty or not absolute.
         */
         TNBFOUND_EXPORT ExportBundle(BundleKind kind, std::filesystem::path root);

        /**
         * @brief Return bundle kind.
         */
        TNB_NODISCARD BundleKind kind() const noexcept {return kind_;}

        /**
         * @brief Return bundle root directory (absolute).
         */
        TNB_NODISCARD const std::filesystem::path& root() const noexcept {return root_;}

        /**
         * @brief Access the manifest object for this bundle.
         */
        TNB_NODISCARD Manifest& manifest() noexcept {return manifest_;}

        /**
         * @brief Access the manifest object for the bundle (const).
         */
        TNB_NODISCARD const Manifest& manifest() const noexcept {return manifest_;}

        /**
         * @brief Return output file entries in deterministic insertion order.
         */
        TNB_NODISCARD const std::vector<OutputFile>& outputs() const noexcept {return outputs_;}

        /**
         * @brief Mutable access to outputs for writer-only metadata updates.
         *
         * @details
         * This is intended for writer components to populate integrity metadata (sha256, bytes)
         * after payload files have been written to staging.
         *
         * Invariant:
         *  - Writers must not reorder outputs; insertion order is the canonical order.
         */
        TNB_NODISCARD std::vector<OutputFile>& outputs_mut() noexcept { return outputs_; }

        /**
         * @brief Add an output file entry to the bundle.
         *
         * @details
         * The output path must be bundle-relative and must not attempt traversal escape.
         * This function preserved insertion order.
         *
         * @param out Output file metadata.
         *
         * @throws std::invalid_argument If out.path is empty or absolute.
         *
         * @throws std::logic_error If out.path escapes the bundle root (traversal).
         */
        TNBFOUND_EXPORT void add_output(OutputFile out);

        /**
         * @brief Validate bundle invariants.
         *
         * @throws std::invalid_argument For invalid construction state (empty/non-absolute root).
         *
         * @throws std::logic_error For invariant violations(e.g. traversal in outputs).
         */
        TNBFOUND_EXPORT void validate() const;

    private:
        BundleKind kind_ = {};
        std::filesystem::path root_;
        Manifest manifest_;
        std::vector<OutputFile> outputs_;
    };

    /**
     * @brief A deterministic plan for atomic bundle writing.
     *
     * @details
     * This plan is used by writers (the atomic writer layer) to avoid partial artefacts:
     *  - staging_root: a temporary directory path for intermediate writes
     *  - final_root: the final bundle directory path
     *
     * Both paths are absolute. No filesystem operations occur here.
     */
    struct BundleWritePlan {
        /**
         * @brief Root directory where temporary artefacts would be written.
         */
        std::filesystem::path staging_root;

        /**
         * @brief Final root directory where the bundle becomes visible.
         */
        std::filesystem::path final_root;
    };

    /**
     * @brief Compute a deterministic staging directory path for a given final root.
     *
     * @details
     * This function does not touch the filesystem. It builds:
     * - <final_root>.tmp.<token>
     *
     * Token must be deterministic (e.g., sequence number from shell session).
     *
     * @param final_root Absolute final bundle root.
     * @param token Deterministic token; used as a suffix.
     *
     * @return BundleWritePlan with absolute staging_root and final_root.
     *
     * @throws std::invalid_argument If final_root is empty or not absolute, or token is empty.
     */
    TNBFOUND_ND_EXPORT BundleWritePlan make_write_plan(const std::filesystem::path& final_root, std::string_view token);
}

#endif // TONB_FOUNDATION_EXPORT_EXPORT_BUNDLE_HXX
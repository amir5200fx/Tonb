/**
 * @file failure_bundle_writer.hxx
 * @brief Atomic writer for deterministic failure bundles.
 *
 * @details
 * The writer is deliberately no-throw at its public boundary and uses a staging
 * directory plus atomic rename promotion. The final bundle becomes visible only
 * after all required JSON files and payload artefacts have been written and size
 * checks have passed.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_BUNDLE_WRITER_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_BUNDLE_WRITER_HXX

#include <tonb/foundation/failure/failure_bundle.hxx>
#include <tonb/foundation/failure/failure_policy.hxx>
#include <tonb/foundation/module.hxx>

#include <filesystem>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace tonb::foundation::failure {

    /**
     * @brief Callback writing one artefact payload file.
     */
    using FailurePayloadWriteFn = std::function<void(const std::filesystem::path& abs_dst_path)>;

    /**
     * @brief Mapping from bundle artefact index to payload callback.
     */
    struct FailurePayloadItem {
        std::size_t artefact_index = 0;
        FailurePayloadWriteFn write;
    };

    /**
     * @brief Result of one bundle-write attempt.
     */
    struct FailureWriteResult {
        bool ok = false;
        std::filesystem::path final_root;
        std::filesystem::path staging_root;
        std::string error;
        std::uint64_t total_bytes = 0;
    };

    /**
     * @brief No-throw bundle writer.
     */
    class FailureBundleWriter {
    public:
        /**
         * @brief Write a bundle under the supplied failure root directory.
         */
        static TNBFOUND_EXPORT FailureWriteResult write_bundle_noexcept(
            const std::filesystem::path& failure_root,
            const FailureBundle& bundle,
            const std::vector<FailurePayloadItem>& artefact_payloads,
            const FailurePolicy& policy) noexcept;

        /**
         * @brief Compute the deterministic final bundle root.
         */
        static std::filesystem::path make_final_root(
            const std::filesystem::path& failure_root,
            std::string_view run_id,
            std::uint32_t sequence,
            std::string_view code);
    };

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_BUNDLE_WRITER_HXX

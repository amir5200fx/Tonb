/**
 * @file failure_run_context.hxx
 * @brief Process-local run identifier and monotonic bundle-sequence allocator.
 *
 * @details
 * The run context groups related failure bundles from the same process run and
 * assigns monotonic sequence numbers without gaps when the caller commits them
 * explicitly after a successful write.
 */
#pragma once
#ifndef TONB_FOUNDATION_FAILURE_FAILURE_RUN_CONTEXT_HXX
#define TONB_FOUNDATION_FAILURE_FAILURE_RUN_CONTEXT_HXX

#include <tonb/foundation/module.hxx>

#include <chrono>
#include <cstdint>
#include <string>

namespace tonb::foundation::failure {

    /**
     * @brief Format a canonical run identifier from UTC components.
     */
    TNBFOUND_ND_EXPORT std::string format_run_id_utc(
        int year,
        int month,
        int day,
        int hour,
        int minute,
        int second,
        std::uint32_t suffix_index = 0);

    /**
     * @brief Process-local run context with explicit sequence commit.
     */
    class FailureRunContext {
    public:
        /** @brief Start a run context using the current system clock. */
        static TNBFOUND_EXPORT FailureRunContext start();

        /** @brief Start a run context at a supplied time point. */
        static TNBFOUND_EXPORT FailureRunContext start_at(std::chrono::system_clock::time_point tp);

        /** @brief Return the canonical run identifier. */
        TNB_NODISCARD const std::string& run_id() const noexcept { return run_id_; }

        /** @brief Return the next sequence number that should be used. */
        TNB_NODISCARD std::uint32_t next_sequence() const noexcept { return next_seq_; }

        /** @brief Mark one bundle as successfully emitted and advance the sequence. */
        TNBFOUND_EXPORT void mark_emitted();

    private:
        FailureRunContext(std::string run_id, std::uint32_t next_seq);

        std::string run_id_;
        std::uint32_t next_seq_ = 1;
    };

} // namespace tonb::foundation::failure

#endif // TONB_FOUNDATION_FAILURE_FAILURE_RUN_CONTEXT_HXX

/**
 * @file logger.hxx
 * @brief Central foundation logger with sink fan-out and sequence assignment.
 *
 * @details
 * Logger owns the severity threshold, domain filtering rules, and the list of
 * attached sinks. The design remains intentionally small, but improves on the
 * current iXfract logger in a few important ways:
 *
 * - domain filtering is string-based and application-neutral
 * - each emitted record receives a monotonic sequence number
 * - sinks can be removed individually via handles
 * - the logger can optionally operate with domain filtering disabled
 */
#pragma once
#ifndef TONB_FOUNDATION_LOGGER_HXX
#define TONB_FOUNDATION_LOGGER_HXX

#include <tonb/foundation/logger/log_record.hxx>
#include <tonb/foundation/logger/log_sink.hxx>
#include <tonb/foundation/module.hxx>

#include <atomic>
#include <cstddef>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_set>
#include <vector>

namespace tonb::foundation::log {

    /**
     * @brief Opaque handle identifying a sink registration.
     */
    using SinkId = std::size_t;

    /**
     * @brief Central thread-safe logger.
     */
    class Logger {
    public:
        /**
         * @brief Construct a logger.
         * @param level Initial severity threshold.
         */
        explicit TNBFOUND_EXPORT Logger(Level level = Level::info);

        /** @brief Set the logger threshold. */
        TNBFOUND_EXPORT void set_level(Level level) noexcept;

        /** @brief Return the current logger threshold. */
        TNBFOUND_ND_EXPORT Level level() const noexcept;

        /**
         * @brief Add a sink and return its registration id.
         * @param sink Sink instance.
         * @return Stable sink id for later removal.
         */
        TNBFOUND_ND_EXPORT SinkId add_sink(std::shared_ptr<Sink> sink);

        /**
         * @brief Remove the sink with the supplied id.
         * @param id Sink id previously returned by add_sink().
         * @return True if a sink was removed.
         */
        TNBFOUND_ND_EXPORT bool remove_sink(SinkId id);

        /** @brief Remove all sinks. */
        TNBFOUND_EXPORT void clear_sinks();

        /** @brief Flush all currently registered sinks. */
        TNBFOUND_EXPORT void flush() noexcept;

        /**
         * @brief Enable filtering by textual domain set.
         *
         * When domain filtering is enabled, only explicitly enabled domains are
         * emitted. When disabled, all domains are accepted.
         */
        TNBFOUND_EXPORT void set_domain_filtering_enabled(bool enabled) noexcept;

        /** @brief Return true if textual domain filtering is active. */
        TNBFOUND_ND_EXPORT bool domain_filtering_enabled() const noexcept;

        /** @brief Enable one textual domain. */
        TNBFOUND_EXPORT void enable_domain(std::string domain);

        /** @brief Disable one textual domain. */
        TNBFOUND_EXPORT void disable_domain(const std::string& domain);

        /** @brief Remove all explicit domain entries. */
        TNBFOUND_EXPORT void clear_domains();

        /** @brief Return true if the supplied domain currently passes filtering. */
        TNBFOUND_ND_EXPORT bool domain_enabled(const std::string& domain) const;

        /**
         * @brief Emit a fully constructed record.
         * @param record Record to dispatch.
         *
         * This function never throws. It performs level filtering, optional
         * domain filtering, sequence assignment, and sink fan-out.
         */
        TNBFOUND_EXPORT void emit(Record record) noexcept;

        /** @brief Return the process-global logger instance. */
        static TNBFOUND_EXPORT Logger& global();

    private:
        struct SinkEntry {
            SinkId id = 0;
            std::shared_ptr<Sink> sink;
        };

        std::atomic<Level> level_;
        std::atomic<std::uint64_t> next_sequence_;
        std::atomic<bool> domain_filtering_enabled_;
        std::atomic<SinkId> next_sink_id_;

        mutable std::mutex mutex_;
        std::vector<SinkEntry> sinks_;
        std::unordered_set<std::string> enabled_domains_;
    };

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOGGER_HXX

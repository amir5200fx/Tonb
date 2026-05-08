/**
* @file log_sink.hxx
 * @brief Abstract output target for foundation log records.
 *
 * @details
 * A sink is responsible for consuming log records and delivering them to a
 * concrete destination such as the console, a file, a ring buffer, or a remote
 * transport. Implementations must be thread-safe and must not throw from the
 * `write()` path.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_SINK_HXX
#define TONB_FOUNDATION_LOG_SINK_HXX

#include <tonb/foundation/logger/log_record.hxx>
#include <tonb/foundation/module.hxx>

#include <string>
#include <vector>

namespace tonb::foundation::log {

    /**
     * @brief Base interface for all logging sinks.
     */
    class Sink {
    public:
        virtual ~Sink() = default;

        /**
         * @brief Consume a log record.
         * @param record Record to write.
         *
         * Implementations must be thread-safe and must not throw.
         */
        virtual void write(const Record& record) noexcept = 0;

        /**
         * @brief Flush any buffered output.
         *
         * Default implementation does nothing.
         */
        virtual void flush() noexcept {}

        /**
         * @brief Return buffered text if the sink supports snapshots.
         * @return Snapshot of buffered lines, or an empty vector if unsupported.
         */
        TNB_NODISCARD virtual std::vector<std::string> snapshot_lines() const { return {}; }

        /**
         * @brief Clear any buffered state if the sink supports clearing.
         */
        virtual void clear() {}
    };

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_SINK_HXX

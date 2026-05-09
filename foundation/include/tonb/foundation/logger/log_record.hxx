/**
 * @file log_record.hxx
 * @brief Immutable value model representing one emitted log event.
 *
 * @details
 * Record is the payload exchanged between the Logger and its sinks. The design
 * is intentionally generic so the foundation layer remains application-neutral.
 * Instead of a hard-coded subsystem enum, the record stores a textual `domain`
 * tag supplied by the application. This avoids baking Tonb- or iXfract-
 * specific categories into the reusable logging substrate.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_RECORD_HXX
#define TONB_FOUNDATION_LOG_RECORD_HXX

#include <tonb/foundation/logger/log_field.hxx>
#include <tonb/foundation/logger/log_level.hxx>

#include <chrono>
#include <cstdint>
#include <source_location>
#include <string>
#include <thread>
#include <vector>

namespace tonb::foundation::log {

    /**
     * @brief Single log event captured at emission time.
     */
    struct Record {
        /** @brief Wall-clock timestamp of the emission. */
        std::chrono::system_clock::time_point timestamp{};

        /** @brief Monotonic logger-assigned sequence number. */
        std::uint64_t sequence = 0;

        /** @brief Severity level. */
        Level level = Level::info;

        /**
         * @brief Application-defined domain or subsystem tag.
         *
         * Examples include "core", "mesh", "shell", or "geom".
         */
        std::string domain;

        /** @brief Correlation id for a background task or job, if any. */
        std::string task_id;

        /** @brief Flattened command path, if a command scope is active. */
        std::string command;

        /** @brief Human-readable message text. */
        std::string message;

        /** @brief Optional machine-readable structured fields. */
        std::vector<Field> fields;

        /** @brief Source location captured at the logging call site. */
        std::source_location location = std::source_location::current();

        /** @brief Thread id of the emitting thread. */
        std::thread::id thread_id = std::this_thread::get_id();
    };

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_RECORD_HXX

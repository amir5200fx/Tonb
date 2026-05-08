/**
 * @file log_level.hxx
 * @brief Severity levels and level-filtering policy for foundation logging.
 *
 * @details
 * This file defines the severity ordering used by the foundation logging
 * subsystem. The ordering is intentionally simple and stable:
 *
 * trace < debug < info < warn < error < critical < off
 *
 * A logger configured with a given threshold emits records whose level is
 * greater than or equal to that threshold. The special level `off` disables all
 * logging. Unlike the current iXfract logging policy, `off` here means fully
 * silent, including error and critical records. This is more predictable for a
 * reusable foundation layer.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_LEVEL_HXX
#define TONB_FOUNDATION_LOG_LEVEL_HXX

#include <cstdint>
#include <string_view>

namespace tonb::foundation::log {

    /**
     * @brief Logging severity levels ordered from most to least verbose.
     */
    enum class Level : std::uint8_t {
        trace = 0,
        debug = 1,
        info = 2,
        warn = 3,
        error = 4,
        critical = 5,
        off = 6
    };

    /**
     * @brief Convert a level into a stable lower-case textual name.
     * @param level Level to convert.
     * @return Stable level string such as "info" or "error".
     */
    constexpr std::string_view to_string(const Level level) noexcept {
        switch (level) {
            case Level::trace: return "trace";
            case Level::debug: return "debug";
            case Level::info: return "info";
            case Level::warn: return "warn";
            case Level::error: return "error";
            case Level::critical: return "critical";
            case Level::off: return "off";
        }
        return "unknown";
    }

    /**
     * @brief Return true if a message level passes the supplied threshold.
     * @param message_level Level of the candidate record.
     * @param threshold Active logger threshold.
     * @return True if the record should be emitted.
     */
    constexpr bool enabled(const Level message_level, const Level threshold) noexcept {
        if (threshold == Level::off) {
            return false;
        }
        return message_level >= threshold;
    }

    static_assert(Level::trace < Level::debug, "Level ordering invariant broken.");
    static_assert(Level::debug < Level::info, "Level ordering invariant broken.");
    static_assert(Level::info < Level::warn, "Level ordering invariant broken.");
    static_assert(Level::warn < Level::error, "Level ordering invariant broken.");
    static_assert(Level::error < Level::critical, "Level ordering invariant broken.");
    static_assert(Level::critical < Level::off, "Level ordering invariant broken.");

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_LEVEL_HXX

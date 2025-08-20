//
// Created by amir on 20/08/2025.
//
#pragma once
#ifndef TONB_SYSTEM_LOG1_HXX
#define TONB_SYSTEM_LOG1_HXX

#include <tonb/system/module.hxx>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <initializer_list>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>
#include <source_location>
#include <iostream>

namespace tonb::system {

    /**
     * @file log.hxx
     * @brief Lightweight, thread-safe logging with multiple sinks and structured fields
     *
     * @details
     *  - Core concepts:
     *      * LogLevel - severity threshold per logger.
     *      * LogRecord - a single event with timestamp, message, tags and fields.
     *      * Sink - destination that consumes records (console, JSON file, adapters).
     *      * Logger - fan out to sinks, with convenience helpers and context.
     *  - Thread safety: public logging methods are safe to call from multiple threads.
     *  - Dependencies: header-only, C++20. Colours use ANSI escapes on TTY.
     *  - Extensibility: add you own sink by implementing ISink.
     */

    /** @enum LogLevel
     * @brief  Logging severity.
     */

    enum class LogLevel : std::uint8_t {
        trace,
        debug,
        info,
        warn,
        error,
        critical,
        off
    };
}
#endif  // TONB_SYSTEM_LOG1_HXX

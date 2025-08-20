//
// Created by amir on 8/19/25.
//
#pragma once
#ifndef TONB_SYSTEM_LOG_HXX
#define TONB_SYSTEM_LOG_HXX

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
     * @file log.hpp
     * @brief Lightweight, thread-safe logging with multiple sinks and structured fields.
     *
     * @details
     *  - Core concepts:
     *      * LogLevel — severity threshold per logger.
     *      * LogRecord — a single event with timestamp, message, tags and fields.
     *      * Sink — destination that consumes records (console, JSON file, adapters).
     *      * Logger — fan-out to sinks, with convenience helpers and context.
     *  - Thread safety: public logging methods are safe to call from multiple threads.
     *  - Dependencies: header-only, C++20. Colours use ANSI escapes on TTY.
     *  - Extensibility: add your own sink by implementing ISink.
     */

    /** @enum LogLevel
     *  @brief Logging severity.
     */

    enum class LogLevel : std::uint8_t { trace, debug, info, warn, error, critical, Off };

    TNB_NODISCARD
    inline constexpr std::string_view to_string(const LogLevel lvl) noexcept {
        switch (lvl) {
            case LogLevel::trace:    return "trace";
            case LogLevel::debug:    return "debug";
            case LogLevel::info:     return "info";
            case LogLevel::warn:     return "warn";
            case LogLevel::error:    return "error";
            case LogLevel::critical: return "critical";
            case LogLevel::Off:      return "off";
        }
        return "unknown";
    }

    /** @struct LogRecord
    *  @brief Immutable log event passed to sinks.
    */
    struct LogRecord {
        using Clock = std::chrono::system_clock;

        Clock::time_point           ts;         ///< Wall clock time.
        LogLevel                    level;      ///< Severity.
        std::string                 message;    ///< Human-friendly message.
        std::string                 component;  ///< Subsystem/component (e.g., "Task").
        std::string                 task_id;    ///< Correlation id for tasks.
        std::thread::id             tid;        ///< Emitting thread id.
        std::string                 file;       ///< Source file (if provided).
        std::string                 function;   ///< Source function (if provided).
        int                         line = 0;   ///< Source line (if provided).
        std::vector<std::pair<std::string,std::string>> fields; ///< Structured fields.

        LogRecord(const LogLevel lvl,
                  std::string msg,
                  std::string comp,
                  std::string id,
                  const std::vector<std::pair<std::string,std::string>>& extra = {},
                  const std::source_location& loc = std::source_location::current())
            : ts(Clock::now()),
              level(lvl),
              message(std::move(msg)),
              component(std::move(comp)),
              task_id(std::move(id)),
              tid(std::this_thread::get_id()),
              file(loc.file_name()),
              function(loc.function_name()),
              line(static_cast<int>(loc.line())),
              fields(extra.begin(), extra.end())
        {}
    };

    /** @class ISink
     *  @brief Abstract destination for log records.
     */
    class ISink {
    public:
        virtual ~ISink() = default;
        virtual void write(const LogRecord& rec) = 0;
    };

    /** @class ConsoleSink
     *  @brief Thread-safe console sink (stdout for info and below, stderr for warn and above).
     */
    class ConsoleSink final : public ISink {
    public:
        explicit ConsoleSink(const bool with_timestamp = true, const bool colour = true)
            : with_ts_(with_timestamp), colour_(colour) {}

        TNBSYSTEM_EXPORT void write(const LogRecord& rec) override;

    private:
        static TNBSYSTEM_EXPORT std::string timestamp(LogRecord::Clock::time_point tp);
        static TNBSYSTEM_EXPORT std::string short_file(std::string_view path);
        static TNBSYSTEM_EXPORT std::string quote(std::string_view v);
        static TNBSYSTEM_EXPORT const char* level_colour(LogLevel lvl);

        std::mutex mu_;
        bool with_ts_;
        bool colour_;
    };

    /** @class JsonFileSink
     *  @brief NDJSON sink that writes one JSON object per line to a file (thread-safe).
     *
     *  @note Suitable for ingestion by tools (jq, logstash, etc.).
     */
    class JsonFileSink final : public ISink {
    public:
        explicit JsonFileSink(std::string path) : path_(std::move(path)), out_(path_, std::ios::app) {}

        TNBSYSTEM_EXPORT void write(const LogRecord& rec) override;

    private:
        static TNBSYSTEM_EXPORT std::string iso8601(LogRecord::Clock::time_point tp);
        static TNBSYSTEM_EXPORT std::string esc(std::string_view s);
        static TNBSYSTEM_EXPORT std::string thread_id_string(const std::thread::id& id);

        std::mutex   mu_;
        std::string  path_;
        std::ofstream out_;
    };

    /** @class RateLimiter
     *  @brief Simple token bucket per key to curb log spam (e.g., repeated errors).
     *
     *  @usage
     *    if (limiter.allow("io-error", 1000)) logger.error("disk full");
     */
    class RateLimiter {
    public:
        /// @param interval_ms Minimum milliseconds between allowed messages per key.
        explicit RateLimiter(const std::uint64_t interval_ms = 1000) : interval_ms_(interval_ms) {}

        TNBSYSTEM_ND_EXPORT bool allow(std::string_view key);

    private:
        static std::uint64_t now_ms();
        std::mutex mu_;
        std::map<std::string, std::uint64_t> last_ms_;
        std::uint64_t interval_ms_;
    };

    /** @class Logger
     *  @brief Fan-out logger with sinks, threshold and contextual fields.
     *
     *  @details
     *  - Construct once and share via std::shared_ptr.
     *  - Add sinks with addSink(...). Set severity threshold with setLevel(...).
     *  - Create child loggers with fixed context using withContext(...).
     */
    class Logger : public std::enable_shared_from_this<Logger> {
    public:
        explicit Logger(const LogLevel level = LogLevel::info,
                        std::string component = {},
                        std::string task_id = {})
            : level_(level), component_(std::move(component)), task_id_(std::move(task_id)) {
            add_sink(std::make_shared<ConsoleSink>(true, true)); // sensible default
        }

        void add_sink(std::shared_ptr<ISink> sink) {
            std::lock_guard<std::mutex> lock(mu_);
            sinks_.push_back(std::move(sink));
        }

        void clear_sinks() {
            std::lock_guard<std::mutex> lock(mu_);
            sinks_.clear();
        }

        void set_level(const LogLevel lvl) { level_.store(lvl, std::memory_order_release); }
        TNB_NODISCARD LogLevel level() const { return level_.load(std::memory_order_acquire); }

        /// Fixed context enrichment (component/task_id and key=value pairs).
        TNBSYSTEM_ND_EXPORT
        std::shared_ptr<Logger> with_context(
            std::string component,
            std::string task_id = {},
            std::initializer_list<std::pair<std::string,std::string>> kv = {}) const;

        // ---- Convenience methods (message only) ----
        void trace (const std::string_view msg) const { log(LogLevel::trace,    msg); }
        void debug (const std::string_view msg) const { log(LogLevel::debug,    msg); }
        void info  (const std::string_view msg) const { log(LogLevel::info,     msg); }
        void warn  (const std::string_view msg) const { log(LogLevel::warn,     msg); }
        void error (const std::string_view msg) const { log(LogLevel::error,    msg); }
        void critical(const std::string_view msg) const { log(LogLevel::critical, msg); }

        void debug(const std::string_view msg,
           const std::initializer_list<std::pair<std::string,std::string>> fields,
           const std::source_location& loc = std::source_location::current()) const {
            log(LogLevel::debug, msg, fields, loc);
        }
        void info (const std::string_view msg,
                   const std::initializer_list<std::pair<std::string,std::string>> fields,
                   const std::source_location& loc = std::source_location::current()) const {
            log(LogLevel::info, msg, fields, loc);
        }
        void warn(const std::string_view msg, const std::initializer_list<std::pair<std::string, std::string> > fields,
                  const std::source_location &loc = std::source_location::current()) const {
            log(LogLevel::warn, msg, fields, loc);
        }
        void error(const std::string_view msg, const std::initializer_list<std::pair<std::string, std::string> > fields,
                   const std::source_location &loc = std::source_location::current()) const {
            log(LogLevel::error, msg, fields, loc);
        }
        void critical(const std::string_view msg,
                      const std::initializer_list<std::pair<std::string, std::string> > fields,
                      const std::source_location &loc = std::source_location::current()) const {
            log(LogLevel::critical, msg, fields, loc);
        }
        /* similarly for warn/error/trace/critical if you like */

        // ---- Full API with fields and source location ----
        TNBSYSTEM_EXPORT
        void log(LogLevel lvl,
                 std::string_view message,
                 std::initializer_list<std::pair<std::string,std::string>> fields = {},
                 const std::source_location& loc = std::source_location::current()) const;

        /// RAII scope timer: logs on destruction with elapsed ms.
        class Scope {
        public:
            Scope(std::shared_ptr<Logger> lg, const LogLevel lvl, std::string what)
                : lg_(std::move(lg)), lvl_(lvl), what_(std::move(what)),
                  start_(std::chrono::steady_clock::now())
            {
                if (lg_) lg_->log(lvl_, "started " + what_);
            }
            TNBSYSTEM_EXPORT ~Scope();
        private:
            std::shared_ptr<Logger> lg_;
            LogLevel lvl_;
            std::string what_;
            std::chrono::steady_clock::time_point start_;
        };

    private:

        /*Private Data*/

        mutable std::mutex mu_;
        std::vector<std::shared_ptr<ISink>> sinks_;
        std::atomic<LogLevel> level_;
        std::string component_;
        std::string task_id_;
        std::vector<std::pair<std::string,std::string>> fields_;
    };

    // ---- Tiny helper macros to capture source location succinctly ----
#define TONB_LOG_INFO(LG, MSG)     (LG)->log(::tonb::system::LogLevel::info,     (MSG))
#define TONB_LOG_WARN(LG, MSG)     (LG)->log(::tonb::system::LogLevel::warn,     (MSG))
#define TONB_LOG_ERROR(LG, MSG)    (LG)->log(::tonb::system::LogLevel::error,    (MSG))
#define TONB_LOG_DEBUG(LG, MSG)    (LG)->log(::tonb::system::LogLevel::debug,    (MSG))
#define TONB_LOG_TRACE(LG, MSG)    (LG)->log(::tonb::system::LogLevel::trace,    (MSG))
#define TONB_LOG_CRITICAL(LG, MSG) (LG)->log(::tonb::system::LogLevel::critical, (MSG))
}
#endif //TONB_SYSTEM_LOG_HXX
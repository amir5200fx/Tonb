//
// Created by amir on 8/19/25.
//
#pragma once
#ifndef TONB_SYSTEM_LOG_HXX
#define TONB_SYSTEM_LOG_HXX

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

    inline constexpr std::string_view to_string(const LogLevel lvl) {
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

        void write(const LogRecord& rec) override {
            std::lock_guard<std::mutex> lock(mu_);

            std::ostream& os = (rec.level >= LogLevel::warn) ? std::cerr : std::cout;
            if (colour_) os << level_colour(rec.level);

            if (with_ts_) os << timestamp(rec.ts) << ' ';
            os << '[' << to_string(rec.level) << ']';
            if (!rec.component.empty()) os << '[' << rec.component << ']';
            if (!rec.task_id.empty())   os << "(id=" << rec.task_id << ')';
            os << ' ' << rec.message;

            if (!rec.fields.empty()) {
                os << " {";
                for (std::size_t i = 0; i < rec.fields.size(); ++i) {
                    os << rec.fields[i].first << '=' << quote(rec.fields[i].second);
                    if (i + 1 < rec.fields.size()) os << ", ";
                }
                os << '}';
            }

            // Useful but concise source hint
            if (!rec.file.empty()) {
                os << "  @" << short_file(rec.file) << ':' << rec.line;
            }
            if (colour_) os << "\033[0m";
            os << '\n';
        }

    private:
        static std::string timestamp(const LogRecord::Clock::time_point tp) {
            using namespace std::chrono;
            const auto t = LogRecord::Clock::to_time_t(tp);
            std::tm tm{};
        #if defined(_WIN32)
            localtime_s(&tm, &t);
        #else
            localtime_r(&t, &tm);
        #endif
            char buf[20];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
            return std::string(buf);
        }

        static std::string short_file(const std::string_view path) {
            const auto pos = path.find_last_of("/\\");
            return std::string(pos == std::string_view::npos ? path : path.substr(pos + 1));
        }

        static std::string quote(const std::string_view v) {
            std::string out; out.reserve(v.size() + 2);
            out.push_back('"');
            for (char c : v) {
                if (c == '"' || c == '\\') out.push_back('\\');
                out.push_back(c);
            }
            out.push_back('"');
            return out;
        }

        static const char* level_colour(const LogLevel lvl) {
            switch (lvl) {
                case LogLevel::trace:    return "\033[2m";        // dim
                case LogLevel::debug:    return "\033[36m";       // cyan
                case LogLevel::info:     return "\033[32m";       // green
                case LogLevel::warn:     return "\033[33m";       // yellow
                case LogLevel::error:    return "\033[31m";       // red
                case LogLevel::critical: return "\033[41;97m";    // red bg, white fg
                case LogLevel::Off:      return "\033[0m";
            }
            return "\033[0m";
        }

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

        void write(const LogRecord& rec) override {
            std::lock_guard<std::mutex> lock(mu_);
            if (!out_.is_open()) return;
            out_ << "{"
                 << R"("ts":")" << iso8601(rec.ts) << R"(",)"
                 << R"("level":")" << to_string(rec.level) << R"(",)"
                 << R"("component":")" << esc(rec.component) << R"(",)"
                 << R"("task_id":")" << esc(rec.task_id) << R"(",)"
                 << R"("thread":")" << thread_id_string(rec.tid) << R"(",)"
                 << R"("file":")" << esc(rec.file) << R"(",)"
                 << R"("line":)" << rec.line << ","
                 << R"("function":")" << esc(rec.function) << R"(",)"
                 << R"("message":")" << esc(rec.message) << R"(",)"
                 << R"("fields":{)";
            for (std::size_t i = 0; i < rec.fields.size(); ++i) {
                out_ << '"' << esc(rec.fields[i].first) << "\":\"" << esc(rec.fields[i].second) << '"';
                if (i + 1 < rec.fields.size()) out_ << ',';
            }
            out_ << "}}\n";
            out_.flush();
        }

    private:
        static std::string iso8601(const LogRecord::Clock::time_point tp) {
            using namespace std::chrono;
            const auto t = LogRecord::Clock::to_time_t(tp);
            std::tm tm{};
        #if defined(_WIN32)
            gmtime_s(&tm, &t);
        #else
            gmtime_r(&t, &tm);
        #endif
            char buf[25];
            std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm);
            return std::string(buf);
        }
        static std::string esc(const std::string_view s) {
            std::ostringstream os;
            for (char c : s) {
                switch (c) { case '\\': os << "\\\\"; break; case '"': os << "\\\""; break;
                             case '\n': os << "\\n"; break; case '\r': os << "\\r"; break;
                             case '\t': os << "\\t"; break; default: os << c; }
            }
            return os.str();
        }
        static std::string thread_id_string(const std::thread::id& id) {
            std::ostringstream os; os << id; return os.str();
        }

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

        bool allow(const std::string_view key) {
            const auto now = now_ms();
            std::lock_guard<std::mutex> lock(mu_);
            auto& last = last_ms_[std::string(key)];
            if (now - last >= interval_ms_) { last = now; return true; }
            return false;
        }

    private:
        static std::uint64_t now_ms() {
            using namespace std::chrono;
            return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
        }
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
        std::shared_ptr<Logger> with_context(
            std::string component,
            std::string task_id = {},
            const std::initializer_list<std::pair<std::string,std::string>> kv = {}) const
        {
            auto child = std::make_shared<Logger>(level(), std::move(component), std::move(task_id));
            // share sinks
            {
                std::lock_guard<std::mutex> lock(mu_);
                child->sinks_ = sinks_;
            }
            child->fields_.assign(kv.begin(), kv.end());
            return child;
        }

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
        void log(const LogLevel lvl,
                 const std::string_view message,
                 const std::initializer_list<std::pair<std::string,std::string>> fields = {},
                 const std::source_location& loc = std::source_location::current()) const {
            if (lvl < level()) return;
            // Merge fixed + call-time fields
            std::vector<std::pair<std::string,std::string>> merged = fields_;
            merged.insert(merged.end(), fields.begin(), fields.end());

            const LogRecord rec{
                lvl,
                std::string(message),
                component_,
                task_id_,
                merged,
                loc
            };
            // Fan-out to sinks
            std::lock_guard<std::mutex> lock(mu_);
            for (auto& s : sinks_) s->write(rec);
        }

        /// RAII scope timer: logs on destruction with elapsed ms.
        class Scope {
        public:
            Scope(std::shared_ptr<Logger> lg, const LogLevel lvl, std::string what)
                : lg_(std::move(lg)), lvl_(lvl), what_(std::move(what)),
                  start_(std::chrono::steady_clock::now())
            {
                if (lg_) lg_->log(lvl_, "started " + what_);
            }
            ~Scope() {
                using namespace std::chrono;
                if (!lg_) return;
                const auto ms = duration_cast<milliseconds>(steady_clock::now() - start_).count();
                lg_->log(lvl_, "finished " + what_, {{"duration_ms", std::to_string(ms)}});
            }
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
/**
 * @file log_formatter.cxx
 * @brief Implementation of shared text formatting helpers for foundation logging.
 */
#include <tonb/foundation/logger/log_formatter.hxx>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace tonb::foundation::log {
    namespace {
        std::string format_timestamp_utc(const std::chrono::system_clock::time_point tp) {
            const auto t = std::chrono::system_clock::to_time_t(tp);
            std::tm tm{};
#if defined(_WIN32)
            gmtime_s(&tm, &t);
#else
            gmtime_r(&t, &tm);
#endif
            std::ostringstream oss;
            oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
            return oss.str();
        }
    }

    TextFormatter::TextFormatter(const TextFormatterOptions options)
        : options_(options) {
    }

    std::string TextFormatter::format(const Record& record) const {
        std::ostringstream oss;

        if (options_.include_sequence) {
            oss << '#' << record.sequence << ' ';
        }
        if (options_.include_timestamp) {
            oss << format_timestamp_utc(record.timestamp) << ' ';
        }
        if (options_.include_command && !record.command.empty()) {
            oss << "[CMD:" << record.command << "] ";
        }

        oss << '[' << record.domain << ']'
            << '[' << to_string(record.level) << "] "
            << record.message;

        if (!record.task_id.empty()) {
            oss << " [task=" << record.task_id << ']';
        }
        for (const auto& field : record.fields) {
            oss << ' ' << field.key << '=' << field.value;
        }
        if (options_.include_location) {
            oss << " (" << record.location.file_name() << ':' << record.location.line() << ')';
        }
        return oss.str();
    }

    const TextFormatterOptions& TextFormatter::options() const noexcept {
        return options_;
    }

    std::shared_ptr<Formatter> make_text_formatter(const TextFormatterOptions options) {
        return std::make_shared<TextFormatter>(options);
    }

} // namespace tonb::foundation::log

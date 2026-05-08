/**
 * @file log_ndjson_file_sink.cxx
 * @brief Implementation of the newline-delimited JSON file sink.
 */
#include <tonb/foundation/logger/sinks/log_ndjson_file_sink.hxx>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace tonb::foundation::log {
    namespace {
        std::string json_escape(const std::string& text) {
            std::string out;
            out.reserve(text.size() + 16);
            for (const char c : text) {
                switch (c) {
                    case '"': out += "\\\""; break;
                    case '\\': out += "\\\\"; break;
                    case '\b': out += "\\b"; break;
                    case '\f': out += "\\f"; break;
                    case '\n': out += "\\n"; break;
                    case '\r': out += "\\r"; break;
                    case '\t': out += "\\t"; break;
                    default:
                        if (static_cast<unsigned char>(c) < 0x20) {
                            std::ostringstream oss;
                            oss << "\\u" << std::hex << std::setw(4) << std::setfill('0')
                                << static_cast<int>(static_cast<unsigned char>(c));
                            out += oss.str();
                        } else {
                            out += c;
                        }
                        break;
                }
            }
            return out;
        }

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

    NdjsonFileSink::NdjsonFileSink(std::string path, const bool append, const bool flush_each)
        : path_(std::move(path)), flush_each_(flush_each) {
        std::ios::openmode mode = std::ios::out;
        mode |= append ? std::ios::app : std::ios::trunc;
        out_.open(path_, mode);
    }

    void NdjsonFileSink::write(const Record& record) noexcept {
        try {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!out_.is_open()) {
                return;
            }

            out_ << '{';
            out_ << "\"timestamp\":\"" << format_timestamp_utc(record.timestamp) << "\",";
            out_ << "\"sequence\":" << record.sequence << ',';
            out_ << "\"level\":\"" << to_string(record.level) << "\",";
            out_ << "\"domain\":\"" << json_escape(record.domain) << "\",";
            out_ << "\"task_id\":\"" << json_escape(record.task_id) << "\",";
            out_ << "\"command\":\"" << json_escape(record.command) << "\",";
            out_ << "\"message\":\"" << json_escape(record.message) << "\",";
            out_ << "\"file\":\"" << json_escape(record.location.file_name()) << "\",";
            out_ << "\"line\":" << record.location.line() << ',';
            out_ << "\"fields\":{";
            for (std::size_t i = 0; i < record.fields.size(); ++i) {
                const auto& field = record.fields[i];
                out_ << '"' << json_escape(field.key) << "\":\"" << json_escape(field.value) << '"';
                if (i + 1 < record.fields.size()) {
                    out_ << ',';
                }
            }
            out_ << "}}\n";

            if (flush_each_) {
                out_.flush();
            }
        } catch (...) {
        }
    }

    void NdjsonFileSink::flush() noexcept {
        try {
            std::lock_guard<std::mutex> lock(mutex_);
            if (out_.is_open()) {
                out_.flush();
            }
        } catch (...) {
        }
    }

} // namespace tonb::foundation::log

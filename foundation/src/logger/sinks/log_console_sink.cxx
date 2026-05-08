/**
 * @file log_console_sink.cxx
 * @brief Implementation of the coloured console sink.
 */
#include <tonb/foundation/logger/sinks/log_console_sink.hxx>

#include <iostream>

namespace tonb::foundation::log {
    namespace {
        const char* level_colour(const Level level) noexcept {
            switch (level) {
                case Level::trace: return "\x1b[37m";
                case Level::debug: return "\x1b[36m";
                case Level::info: return "\x1b[32m";
                case Level::warn: return "\x1b[33m";
                case Level::error: return "\x1b[31m";
                case Level::critical: return "\x1b[35m";
                case Level::off: return "\x1b[0m";
            }
            return "\x1b[0m";
        }
    }

    ConsoleSink::ConsoleSink(const bool use_colour, std::shared_ptr<Formatter> formatter)
        : use_colour_(use_colour), formatter_(std::move(formatter)) {
        if (!formatter_) {
            formatter_ = make_text_formatter();
        }
    }

    void ConsoleSink::write(const Record& record) noexcept {
        try {
            std::lock_guard<std::mutex> lock(mutex_);
            std::ostream& os = (record.level >= Level::error) ? std::cerr : std::cout;
            const auto line = formatter_->format(record);

            if (use_colour_) {
                os << '[' << record.domain << ']';
                os << level_colour(record.level) << '[' << to_string(record.level) << "]\x1b[0m";

                // Avoid duplicating the [domain][level] prefix if the formatter already produced it.
                const auto prefix = std::string("[") + record.domain + "][" + std::string(to_string(record.level)) + "] ";
                if (line.rfind(prefix, 0) == 0) {
                    os << ' ' << line.substr(prefix.size()) << '\n';
                } else {
                    os << ' ' << line << '\n';
                }
            } else {
                os << line << '\n';
            }
        } catch (...) {
        }
    }

    void ConsoleSink::flush() noexcept {
        try {
            std::lock_guard<std::mutex> lock(mutex_);
            std::cout.flush();
            std::cerr.flush();
        } catch (...) {
        }
    }

} // namespace tonb::foundation::log

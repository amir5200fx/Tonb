/**
* @file log_console_sink.hxx
 * @brief Thread-safe coloured console sink for human-facing execution logs.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_SINKS_LOG_CONSOLE_SINK_HXX
#define TONB_FOUNDATION_LOG_SINKS_LOG_CONSOLE_SINK_HXX

#include <tonb/foundation/logger/log_formatter.hxx>
#include <tonb/foundation/logger/log_sink.hxx>
#include <tonb/foundation/module.hxx>

#include <memory>
#include <mutex>

namespace tonb::foundation::log {

    /**
     * @brief Console sink writing one record per line to stdout or stderr.
     */
    class ConsoleSink final : public Sink {
    public:
        /**
         * @brief Construct a console sink.
         * @param use_colour If true, colourise the level token.
         * @param formatter Formatter used for the textual content.
         */
        explicit TNBFOUND_EXPORT ConsoleSink(
            bool use_colour = true,
            std::shared_ptr<Formatter> formatter = make_text_formatter());

        TNBFOUND_EXPORT void write(const Record& record) noexcept override;
        TNBFOUND_EXPORT void flush() noexcept override;

    private:
        bool use_colour_ = true;
        std::shared_ptr<Formatter> formatter_;
        mutable std::mutex mutex_;
    };

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_SINKS_LOG_CONSOLE_SINK_HXX

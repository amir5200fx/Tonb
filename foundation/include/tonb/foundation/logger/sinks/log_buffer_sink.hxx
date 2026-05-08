/**
* @file log_buffer_sink.hxx
 * @brief Bounded in-memory line-buffer sink for GUI panes and tests.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_SINKS_LOG_BUFFER_SINK_HXX
#define TONB_FOUNDATION_LOG_SINKS_LOG_BUFFER_SINK_HXX

#include <tonb/foundation/logger/log_formatter.hxx>
#include <tonb/foundation/logger/log_sink.hxx>
#include <tonb/foundation/module.hxx>

#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace tonb::foundation::log {

    /**
     * @brief Thread-safe bounded line buffer sink.
     *
     * The sink stores formatted text lines rather than raw records so it can be
     * used directly by terminal history viewers, GUI log panels, and tests.
     */
    class BufferSink final : public Sink {
    public:
        /**
         * @brief Construct a buffer sink.
         * @param max_lines Maximum number of stored lines.
         * @param formatter Formatter used to convert records into text.
         */
        explicit TNBFOUND_EXPORT BufferSink(
            std::size_t max_lines = 5000,
            std::shared_ptr<Formatter> formatter = make_text_formatter());

        TNBFOUND_EXPORT void write(const Record& record) noexcept override;
        TNBFOUND_ND_EXPORT std::vector<std::string> snapshot_lines() const override;
        TNBFOUND_EXPORT void clear() override;

    private:
        std::size_t max_lines_ = 5000;
        std::shared_ptr<Formatter> formatter_;
        mutable std::mutex mutex_;
        std::deque<std::string> lines_;
    };

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_SINKS_LOG_BUFFER_SINK_HXX

/**
* @file log_text_file_sink.hxx
 * @brief Plain-text file sink for operational log capture.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_SINKS_LOG_TEXT_FILE_SINK_HXX
#define TONB_FOUNDATION_LOG_SINKS_LOG_TEXT_FILE_SINK_HXX

#include <tonb/foundation/logger/log_formatter.hxx>
#include <tonb/foundation/logger/log_sink.hxx>
#include <tonb/foundation/module.hxx>

#include <fstream>
#include <memory>
#include <mutex>
#include <string>

namespace tonb::foundation::log {

    /**
     * @brief File sink that stores one formatted text line per record.
     */
    class TextFileSink final : public Sink {
    public:
        /**
         * @brief Construct a text file sink.
         * @param path Output file path.
         * @param append If true, append to an existing file. Otherwise truncate.
         * @param flush_each If true, flush after each write.
         * @param formatter Formatter used for textual output.
         */
        explicit TNBFOUND_EXPORT TextFileSink(
            std::string path,
            bool append = true,
            bool flush_each = false,
            std::shared_ptr<Formatter> formatter = make_text_formatter());

        TNBFOUND_EXPORT void write(const Record& record) noexcept override;
        TNBFOUND_EXPORT void flush() noexcept override;

    private:
        std::string path_;
        bool flush_each_ = false;
        std::shared_ptr<Formatter> formatter_;
        std::ofstream out_;
        mutable std::mutex mutex_;
    };

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_SINKS_LOG_TEXT_FILE_SINK_HXX

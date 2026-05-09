/**
* @file log_ndjson_file_sink.hxx
 * @brief NDJSON file sink for structured machine-readable log export.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_SINKS_LOG_NDJSON_FILE_SINK_HXX
#define TONB_FOUNDATION_LOG_SINKS_LOG_NDJSON_FILE_SINK_HXX

#include <tonb/foundation/logger/log_sink.hxx>
#include <tonb/foundation/module.hxx>

#include <fstream>
#include <mutex>
#include <string>

namespace tonb::foundation::log {

    /**
     * @brief File sink writing one JSON object per line.
     */
    class NdjsonFileSink final : public Sink {
    public:
        /**
         * @brief Construct an NDJSON sink.
         * @param path Output file path.
         * @param append If true, append to an existing file. Otherwise truncate.
         * @param flush_each If true, flush after every record.
         */
        explicit TNBFOUND_EXPORT NdjsonFileSink(
            std::string path,
            bool append = true,
            bool flush_each = false);

        TNBFOUND_EXPORT void write(const Record& record) noexcept override;
        TNBFOUND_EXPORT void flush() noexcept override;

    private:
        std::string path_;
        bool flush_each_ = false;
        std::ofstream out_;
        mutable std::mutex mutex_;
    };

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_SINKS_LOG_NDJSON_FILE_SINK_HXX

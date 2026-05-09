/**
* @file log_text_file_sink.cxx
 * @brief Implementation of the plain-text file sink.
 */
#include <tonb/foundation/logger/sinks/log_text_file_sink.hxx>

namespace tonb::foundation::log {

    TextFileSink::TextFileSink(
        std::string path,
        const bool append,
        const bool flush_each,
        std::shared_ptr<Formatter> formatter)
        : path_(std::move(path)),
          flush_each_(flush_each),
          formatter_(std::move(formatter)) {
        if (!formatter_) {
            formatter_ = make_text_formatter();
        }

        std::ios::openmode mode = std::ios::out;
        mode |= append ? std::ios::app : std::ios::trunc;
        out_.open(path_, mode);
    }

    void TextFileSink::write(const Record& record) noexcept {
        try {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!out_.is_open()) {
                return;
            }
            out_ << formatter_->format(record) << '\n';
            if (flush_each_) {
                out_.flush();
            }
        } catch (...) {
        }
    }

    void TextFileSink::flush() noexcept {
        try {
            std::lock_guard<std::mutex> lock(mutex_);
            if (out_.is_open()) {
                out_.flush();
            }
        } catch (...) {
        }
    }

} // namespace tonb::foundation::log

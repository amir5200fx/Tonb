/**
* @file log_buffer_sink.cxx
 * @brief Implementation of the bounded in-memory line buffer sink.
 */
#include <tonb/foundation/logger/sinks/log_buffer_sink.hxx>

namespace tonb::foundation::log {

    BufferSink::BufferSink(const std::size_t max_lines, std::shared_ptr<Formatter> formatter)
        : max_lines_(max_lines), formatter_(std::move(formatter)) {
        if (!formatter_) {
            formatter_ = make_text_formatter();
        }
    }

    void BufferSink::write(const Record& record) noexcept {
        try {
            const auto line = formatter_->format(record);
            std::lock_guard<std::mutex> lock(mutex_);
            lines_.push_back(line);
            while (lines_.size() > max_lines_) {
                lines_.pop_front();
            }
        } catch (...) {
        }
    }

    std::vector<std::string> BufferSink::snapshot_lines() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return {lines_.begin(), lines_.end()};
    }

    void BufferSink::clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        lines_.clear();
    }

} // namespace tonb::foundation::log

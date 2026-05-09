/**
 * @file logger.cxx
 * @brief Implementation of the central foundation logger.
 */
#include <tonb/foundation/logger/logger.hxx>

#include <algorithm>

namespace tonb::foundation::log {

    Logger::Logger(const Level level)
        : level_(level),
          next_sequence_(0),
          domain_filtering_enabled_(false),
          next_sink_id_(1) {
    }

    void Logger::set_level(const Level level) noexcept {
        level_.store(level, std::memory_order_relaxed);
    }

    Level Logger::level() const noexcept {
        return level_.load(std::memory_order_relaxed);
    }

    SinkId Logger::add_sink(std::shared_ptr<Sink> sink) {
        const auto id = next_sink_id_.fetch_add(1, std::memory_order_relaxed);
        std::lock_guard<std::mutex> lock(mutex_);
        sinks_.push_back({id, std::move(sink)});
        return id;
    }

    bool Logger::remove_sink(const SinkId id) {
        std::lock_guard<std::mutex> lock(mutex_);
        const auto old_size = sinks_.size();
        sinks_.erase(
            std::remove_if(
                sinks_.begin(),
                sinks_.end(),
                [id](const SinkEntry& entry) { return entry.id == id; }),
            sinks_.end());
        return sinks_.size() != old_size;
    }

    void Logger::clear_sinks() {
        std::lock_guard<std::mutex> lock(mutex_);
        sinks_.clear();
    }

    void Logger::flush() noexcept {
        std::vector<std::shared_ptr<Sink>> sinks;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            sinks.reserve(sinks_.size());
            for (const auto& entry : sinks_) {
                sinks.push_back(entry.sink);
            }
        }
        for (const auto& sink : sinks) {
            if (sink) {
                sink->flush();
            }
        }
    }

    void Logger::set_domain_filtering_enabled(const bool enabled) noexcept {
        domain_filtering_enabled_.store(enabled, std::memory_order_relaxed);
    }

    bool Logger::domain_filtering_enabled() const noexcept {
        return domain_filtering_enabled_.load(std::memory_order_relaxed);
    }

    void Logger::enable_domain(std::string domain) {
        std::lock_guard<std::mutex> lock(mutex_);
        enabled_domains_.insert(std::move(domain));
    }

    void Logger::disable_domain(const std::string& domain) {
        std::lock_guard<std::mutex> lock(mutex_);
        enabled_domains_.erase(domain);
    }

    void Logger::clear_domains() {
        std::lock_guard<std::mutex> lock(mutex_);
        enabled_domains_.clear();
    }

    bool Logger::domain_enabled(const std::string& domain) const {
        if (!domain_filtering_enabled()) {
            return true;
        }
        std::lock_guard<std::mutex> lock(mutex_);
        return enabled_domains_.find(domain) != enabled_domains_.end();
    }

    void Logger::emit(Record record) noexcept {
        if (!enabled(record.level, level())) {
            return;
        }
        if (!domain_enabled(record.domain)) {
            return;
        }

        record.sequence = next_sequence_.fetch_add(1, std::memory_order_relaxed) + 1;

        std::vector<std::shared_ptr<Sink>> sinks;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            sinks.reserve(sinks_.size());
            for (const auto& entry : sinks_) {
                sinks.push_back(entry.sink);
            }
        }

        for (const auto& sink : sinks) {
            if (sink) {
                sink->write(record);
            }
        }
    }

    Logger& Logger::global() {
        static Logger logger(Level::info);
        return logger;
    }

} // namespace tonb::foundation::log

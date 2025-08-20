//
// Created by amir on 8/20/25.
//
#include <tonb/system/log.hxx>

void tonb::system::ConsoleSink::write(const LogRecord &rec) {
    std::lock_guard<std::mutex> lock(mu_);

    std::ostream& os = (rec.level >= LogLevel::warn) ? std::cerr : std::cout;
    if (colour_) os << level_colour(rec.level);

    if (with_ts_) os << timestamp(rec.ts) << ' ';
    os << '[' << to_string(rec.level) << ']';
    if (!rec.component.empty()) os << '[' << rec.component << ']';
    if (!rec.task_id.empty())   os << "(id=" << rec.task_id << ')';
    os << ' ' << rec.message;

    if (!rec.fields.empty()) {
        os << " {";
        for (std::size_t i = 0; i < rec.fields.size(); ++i) {
            os << rec.fields[i].first << '=' << quote(rec.fields[i].second);
            if (i + 1 < rec.fields.size()) os << ", ";
        }
        os << '}';
    }

    // Useful but concise source hint
    if (!rec.file.empty()) {
        os << "  @" << short_file(rec.file) << ':' << rec.line;
    }
    if (colour_) os << "\033[0m";
    os << '\n';
}

void tonb::system::ConsoleSink::flush() {
    std::lock_guard<std::mutex> lock(mu_);
    std::cout.flush();
    std::cerr.flush();
}

std::string tonb::system::ConsoleSink::timestamp(const LogRecord::Clock::time_point tp) {
    using namespace std::chrono;
    const auto t = LogRecord::Clock::to_time_t(tp);
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buf);
}

std::string tonb::system::ConsoleSink::short_file(const std::string_view path) {
    const auto pos = path.find_last_of("/\\");
    return std::string(pos == std::string_view::npos ? path : path.substr(pos + 1));
}

std::string tonb::system::ConsoleSink::quote(const std::string_view v) {
    std::string out; out.reserve(v.size() + 2);
    out.push_back('"');
    for (char c : v) {
        if (c == '"' || c == '\\') out.push_back('\\');
        out.push_back(c);
    }
    out.push_back('"');
    return out;
}

const char * tonb::system::ConsoleSink::level_colour(const LogLevel lvl) {
    switch (lvl) {
        case LogLevel::trace:    return "\033[2m";        // dim
        case LogLevel::debug:    return "\033[36m";       // cyan
        case LogLevel::info:     return "\033[32m";       // green
        case LogLevel::warn:     return "\033[33m";       // yellow
        case LogLevel::error:    return "\033[31m";       // red
        case LogLevel::critical: return "\033[41;97m";    // red bg, white fg
        case LogLevel::off:      return "\033[0m";
    }
    return "\033[0m";
}

void tonb::system::JsonFileSink::write(const LogRecord &rec) {
    std::lock_guard<std::mutex> lock(mu_);
    if (!out_.is_open()) return;
    out_ << "{"
         << R"("ts":")" << iso8601(rec.ts) << R"(",)"
         << R"("level":")" << to_string(rec.level) << R"(",)"
         << R"("component":")" << esc(rec.component) << R"(",)"
         << R"("task_id":")" << esc(rec.task_id) << R"(",)"
         << R"("thread":")" << thread_id_string(rec.tid) << R"(",)"
         << R"("file":")" << esc(rec.file) << R"(",)"
         << R"("line":)" << rec.line << ","
         << R"("function":")" << esc(rec.function) << R"(",)"
         << R"("message":")" << esc(rec.message) << R"(",)"
         << R"("fields":{)";
    for (std::size_t i = 0; i < rec.fields.size(); ++i) {
        out_ << '"' << esc(rec.fields[i].first) << "\":\"" << esc(rec.fields[i].second) << '"';
        if (i + 1 < rec.fields.size()) out_ << ',';
    }
    out_ << "}}\n";
    out_.flush();
}

void tonb::system::JsonFileSink::flush() {
    std::lock_guard<std::mutex> lock(mu_);
    out_.flush();
}

std::string tonb::system::JsonFileSink::iso8601(const LogRecord::Clock::time_point tp) {
    using namespace std::chrono;
    const auto t = LogRecord::Clock::to_time_t(tp);
    std::tm tm{};
#if defined(_WIN32)
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif
    char buf[25];
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm);
    return std::string(buf);
}

std::string tonb::system::JsonFileSink::esc(const std::string_view s) {
    std::ostringstream os;
    for (char c : s) {
        switch (c) { case '\\': os << "\\\\"; break; case '"': os << "\\\""; break;
            case '\n': os << "\\n"; break; case '\r': os << "\\r"; break;
            case '\t': os << "\\t"; break; default: os << c; }
    }
    return os.str();
}

std::string tonb::system::JsonFileSink::thread_id_string(const std::thread::id &id) {
    std::ostringstream os; os << id; return os.str();
}

bool tonb::system::RateLimiter::allow(const std::string_view key) {
    const auto now = now_ms();
    std::lock_guard<std::mutex> lock(mu_);
    auto& last = last_ms_[std::string(key)];
    if (now - last >= interval_ms_) { last = now; return true; }
    return false;
}

std::uint64_t tonb::system::RateLimiter::now_ms() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

std::shared_ptr<tonb::system::Logger> tonb::system::Logger::with_context(std::string component, std::string task_id,
    const std::initializer_list<std::pair<std::string, std::string>> kv) const {
    auto child = std::make_shared<Logger>(level(), std::move(component), std::move(task_id));
    // share sinks
    {
        std::lock_guard<std::mutex> lock(mu_);
        child->sinks_ = sinks_;
    }
    child->fields_.assign(kv.begin(), kv.end());
    return child;
}

void tonb::system::Logger::flush() const {
    std::lock_guard<std::mutex> lock(mu_);
    for (auto& sink : sinks_) {
        if (auto* f = dynamic_cast<FlushableSink*>(sink.get())) f->flush();
    }
}

void tonb::system::Logger::rewind() const {
    std::lock_guard<std::mutex> lock(mu_);
    for (auto& sink : sinks_) {
        if (auto* f = dynamic_cast<RewindableSink*>(sink.get())) f->rewind();
    }
}

void tonb::system::Logger::rewind(const std::size_t n) const {
    std::lock_guard<std::mutex> lock(mu_);
    for (auto& sink : sinks_) {
        if (auto* r = dynamic_cast<RewindableSink*>(sink.get())) r->rewind_count(n);
    }
}

void tonb::system::Logger::rewind_to_last() const {
    std::lock_guard<std::mutex> lock(mu_);
    for (auto& sink : sinks_) {
        if (auto* r = dynamic_cast<RewindableSink*>(sink.get())) r->rewind_to_last();
    }
}

void tonb::system::Logger::log(const LogLevel lvl, const std::string_view message,
                               const std::initializer_list<std::pair<std::string, std::string>> fields, const std::source_location &loc) const {
    if (lvl < level()) return;
    // Merge fixed + call-time fields
    std::vector<std::pair<std::string,std::string>> merged = fields_;
    merged.insert(merged.end(), fields.begin(), fields.end());

    const LogRecord rec{
        lvl,
        std::string(message),
        component_,
        task_id_,
        merged,
        loc
    };
    // Fan-out to sinks
    std::lock_guard<std::mutex> lock(mu_);
    for (auto& s : sinks_) s->write(rec);
}

tonb::system::Logger::Scope::~Scope() {
    using namespace std::chrono;
    if (!lg_) return;
    const auto ms = duration_cast<milliseconds>(steady_clock::now() - start_).count();
    lg_->log(lvl_, "finished " + what_, {{"duration_ms", std::to_string(ms)}});
}

void tonb::system::BufferedTextSink::maybe_flush_on_overflow_unlocked() {
    if (max_buf_ == 0) return;
    if (buffer_.size() <= max_buf_) return;
    if (auto_flush_on_overflow_) {
        do_flush_unlocked();
    } else {
        // keep only tail within limit
        buffer_.erase(0,  buffer_.size() - max_buf_);
    }
}

void tonb::system::BufferedTextSink::do_flush_unlocked() {
    if (!out_ || buffer_.empty()) return;
    out_(buffer_);
    last_flushed_ = buffer_;
    buffer_.clear();
}

std::string tonb::system::BufferedTextSink::format(const LogRecord &rec) {
    std::ostringstream os;
    if (with_ts_static_) os << timestamp(rec.ts) <<' ';
    os <<'['<< to_string(rec.level)<<']';
    if (!rec.component.empty()) os<<'['<<rec.component<<']';
    if (!rec.task_id.empty()) os<<'['<<rec.task_id<<']';
    os << ' ' << rec.message;
    if (!rec.fields.empty()) {
        os << " {";
        for (std::size_t i = 0; i < rec.fields.size(); i++) {
            os << rec.fields[i].first << "=\" " << rec.fields[i].second << '"';
            if (i + 1 < rec.fields.size()) os << ", ";
        }
        os << '}';
    }
    if (!rec.fields.empty() && rec.line > 0) {
        const auto pos = rec.file.find_last_of("/\\");
        os << "  @" << (pos == std::string::npos ? rec.file : rec.file.substr(pos + 1)) << ':' << rec.line;
    }
    os << '\n';
    return os.str();
}

std::string tonb::system::BufferedTextSink::timestamp(const LogRecord::Clock::time_point tp) {
    using namespace std::chrono;
    const auto t = LogRecord::Clock::to_time_t(tp);
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buf);
}

void tonb::system::BufferedTextSink::write(const LogRecord &rec) {
    std::lock_guard<std::mutex> lock(mu_);
    // append formatted line
    append_line(format(rec));
    maybe_flush_on_overflow_unlocked();
    // If you want "auto flush on delimiter" semantics like your old version, enable this:
    if (!flush_delim_.empty() && buffer_.find(flush_delim_) != std::string::npos) {
        do_flush_unlocked();
    }
}

void tonb::system::BufferedTextSink::flush() {
    std::lock_guard<std::mutex> lock(mu_);
    do_flush_unlocked();
}

void tonb::system::BufferedTextSink::rewind() {
    std::lock_guard<std::mutex> lock(mu_);
    buffer_.clear();
}

void tonb::system::BufferedTextSink::rewind_count(std::size_t n) {
    std::lock_guard<std::mutex> lock(mu_);
    if (n >= buffer_.size()) {
        buffer_.clear();
    } else {
        buffer_.erase(buffer_.size() - n);
    }
}

void tonb::system::BufferedTextSink::rewind_to_last() {
    std::lock_guard<std::mutex> lock(mu_);
    buffer_ = last_flushed_;
}

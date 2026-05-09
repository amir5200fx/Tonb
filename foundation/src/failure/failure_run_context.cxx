/**
 * @file failure_run_context.cxx
 * @brief Implementation of process-local failure run context.
 */
#include <tonb/foundation/failure/failure_run_context.hxx>

#include <cstdio>
#include <ctime>
#include <map>
#include <mutex>
#include <stdexcept>
#include <utility>

namespace tonb::foundation::failure {
    namespace {

        void require_range(const char* name, const int value, const int lo, const int hi) {
            if (value < lo || value > hi) {
                throw std::invalid_argument(
                    std::string("format_run_id_utc: field out of range: ") + name + "=" + std::to_string(value));
            }
        }

        std::tm to_utc_tm(const std::chrono::system_clock::time_point tp) {
            const std::time_t tt = std::chrono::system_clock::to_time_t(tp);
            std::tm tm_utc{};
        #if defined(_WIN32)
            if (gmtime_s(&tm_utc, &tt) != 0) {
                throw std::runtime_error("FailureRunContext: gmtime_s failed");
            }
        #else
            if (gmtime_r(&tt, &tm_utc) == nullptr) {
                throw std::runtime_error("FailureRunContext: gmtime_r failed");
            }
        #endif
            return tm_utc;
        }

        std::string format_base_run_id(const std::tm& tm_utc) {
            char buf[32]{};
            const int n = std::snprintf(
                buf,
                sizeof(buf),
                "%04d%02d%02d-%02d%02d%02dZ",
                tm_utc.tm_year + 1900,
                tm_utc.tm_mon + 1,
                tm_utc.tm_mday,
                tm_utc.tm_hour,
                tm_utc.tm_min,
                tm_utc.tm_sec);
            if (n <= 0 || static_cast<std::size_t>(n) >= sizeof(buf)) {
                throw std::runtime_error("FailureRunContext: RUN_ID formatting failed");
            }
            return {buf, static_cast<std::size_t>(n)};
        }

        std::uint32_t allocate_suffix_index_process_local(const std::string& base_id) {
            static std::mutex mutex;
            static std::map<std::string, std::uint32_t> counts;

            std::lock_guard<std::mutex> lock(mutex);
            const auto it = counts.find(base_id);
            if (it == counts.end()) {
                counts.emplace(base_id, 0);
                return 0;
            }
            const std::uint32_t next = it->second + 1;
            it->second = next;
            return next;
        }

        std::string append_suffix(std::string base, const std::uint32_t suffix_index) {
            if (suffix_index == 0) {
                return base;
            }
            char suf[16]{};
            const int n = std::snprintf(suf, sizeof(suf), "_%02u", suffix_index);
            if (n <= 0 || static_cast<std::size_t>(n) >= sizeof(suf)) {
                throw std::runtime_error("FailureRunContext: suffix formatting failed");
            }
            base.append(suf, static_cast<std::size_t>(n));
            return base;
        }

    } // namespace

    std::string format_run_id_utc(
        const int year,
        const int month,
        const int day,
        const int hour,
        const int minute,
        const int second,
        const std::uint32_t suffix_index) {
        require_range("year", year, 1970, 9999);
        require_range("month", month, 1, 12);
        require_range("day", day, 1, 31);
        require_range("hour", hour, 0, 23);
        require_range("minute", minute, 0, 59);
        require_range("second", second, 0, 60);

        char buf[32]{};
        const int n = std::snprintf(
            buf,
            sizeof(buf),
            "%04d%02d%02d-%02d%02d%02dZ",
            year, month, day, hour, minute, second);
        if (n <= 0 || static_cast<std::size_t>(n) >= sizeof(buf)) {
            throw std::runtime_error("format_run_id_utc: formatting failed");
        }
        return append_suffix(std::string(buf, static_cast<std::size_t>(n)), suffix_index);
    }

    FailureRunContext FailureRunContext::start() {
        return start_at(std::chrono::system_clock::now());
    }

    FailureRunContext FailureRunContext::start_at(const std::chrono::system_clock::time_point tp) {
        const std::tm tm_utc = to_utc_tm(tp);
        const std::string base = format_base_run_id(tm_utc);
        const std::uint32_t suffix = allocate_suffix_index_process_local(base);
        return {append_suffix(base, suffix), 1};
    }

    FailureRunContext::FailureRunContext(std::string run_id, const std::uint32_t next_seq)
        : run_id_(std::move(run_id)), next_seq_(next_seq) {
        if (run_id_.empty()) {
            throw std::invalid_argument("FailureRunContext: run_id must not be empty");
        }
        if (next_seq_ < 1) {
            throw std::invalid_argument("FailureRunContext: next_seq must be >= 1");
        }
    }

    void FailureRunContext::mark_emitted() {
        if (next_seq_ == 0xFFFFFFFFu) {
            throw std::overflow_error("FailureRunContext: sequence overflow");
        }
        ++next_seq_;
    }

} // namespace tonb::foundation::failure

/**
 * @file failure_event.cxx
 * @brief Implementation of failure-event utilities.
 */
#include <tonb/foundation/failure/failure_event.hxx>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace tonb::foundation::failure {

    namespace {
        bool looks_like_path(const std::string_view value) noexcept {
            return value.find('/') != std::string_view::npos ||
                   value.find('\\') != std::string_view::npos ||
                   value.find(':') != std::string_view::npos;
        }
    }

    std::string current_utc_timestamp() {
        const auto now = std::chrono::system_clock::now();
        const auto tt = std::chrono::system_clock::to_time_t(now);
        std::tm tm_utc{};
    #if defined(_WIN32)
        gmtime_s(&tm_utc, &tt);
    #else
        gmtime_r(&tt, &tm_utc);
    #endif
        std::ostringstream oss;
        oss << std::put_time(&tm_utc, "%Y-%m-%dT%H:%M:%SZ");
        return oss.str();
    }

    bool is_valid_domain_token(const std::string_view token) noexcept {
        if (token.empty()) {
            return false;
        }
        for (const char c : token) {
            const bool ok =
                (c >= 'a' && c <= 'z') ||
                (c >= '0' && c <= '9') ||
                c == '_' || c == '.' || c == '-';
            if (!ok) {
                return false;
            }
        }
        return true;
    }

    std::string redact_paths_copy(std::string value) {
        if (!looks_like_path(value)) {
            return value;
        }
        return "<redacted-path>";
    }

} // namespace tonb::foundation::failure

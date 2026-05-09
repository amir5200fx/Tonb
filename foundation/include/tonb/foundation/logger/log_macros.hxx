/**
 * @file log_macros.hxx
 * @brief Convenience macros for low-overhead stream-style logging.
 *
 * @details
 * These macros preserve the practical style used in iXfract while adapting the
 * implementation to the cleaner foundation logger. The macros:
 *
 * - consult the active logger before building the message
 * - honour the thread-local level override when present
 * - inject task and command context automatically
 * - support both plain text messages and optional structured fields
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_MACROS_HXX
#define TONB_FOUNDATION_LOG_MACROS_HXX

#include <tonb/foundation/log/log_context.hxx>
#include <tonb/foundation/log/logger.hxx>

#include <chrono>
#include <source_location>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace tonb::foundation::log {

    /**
     * @brief Build a message from streamable parts.
     * @tparam Ts Message part types.
     * @param parts Streamable message parts.
     * @return Concatenated textual message.
     */
    template<class... Ts>
    std::string build_message(Ts&&... parts) {
        std::ostringstream oss;
        (oss << ... << std::forward<Ts>(parts));
        return oss.str();
    }

    /**
     * @brief Emit a fully contextualised record.
     * @param level Record severity.
     * @param domain Application-supplied domain tag.
     * @param message Fully formatted message text.
     * @param location Source location.
     * @param fields Structured fields.
     */
    inline void emit_with_context(
        const Level level,
        std::string domain,
        std::string message,
        const std::source_location location,
        std::vector<Field> fields = {}) {

        const auto& context = current_context();

        Record record;
        record.timestamp = std::chrono::system_clock::now();
        record.level = level;
        record.domain = std::move(domain);
        record.task_id = context.task_id;
        record.command = current_command_path();
        record.message = std::move(message);
        record.fields = std::move(fields);
        record.location = location;

        active_logger().emit(std::move(record));
    }

} // namespace tonb::foundation::log

#define GFO_LOG_AT(_level, _domain, ...)                                                            \
    do {                                                                                           \
        auto& _gf_log = ::tonb::foundation::log::active_logger();                              \
        const auto& _gf_ctx = ::tonb::foundation::log::current_context();                      \
        const auto _gf_thr = _gf_ctx.level_override.has_value()                                    \
            ? *_gf_ctx.level_override                                                               \
            : _gf_log.level();                                                                      \
        if (::tonb::foundation::log::enabled((_level), _gf_thr)) {                             \
            ::tonb::foundation::log::emit_with_context(                                         \
                (_level),                                                                           \
                (_domain),                                                                          \
                ::tonb::foundation::log::build_message(__VA_ARGS__),                            \
                std::source_location::current());                                                   \
        }                                                                                           \
    } while (false)

#define GFO_LOG_AT_F(_level, _domain, _fields, ...)                                                 \
    do {                                                                                           \
        auto& _gf_log = ::tonb::foundation::log::active_logger();                              \
        const auto& _gf_ctx = ::tonb::foundation::log::current_context();                      \
        const auto _gf_thr = _gf_ctx.level_override.has_value()                                    \
            ? *_gf_ctx.level_override                                                               \
            : _gf_log.level();                                                                      \
        if (::tonb::foundation::log::enabled((_level), _gf_thr)) {                             \
            ::tonb::foundation::log::emit_with_context(                                         \
                (_level),                                                                           \
                (_domain),                                                                          \
                ::tonb::foundation::log::build_message(__VA_ARGS__),                            \
                std::source_location::current(),                                                    \
                (_fields));                                                                         \
        }                                                                                           \
    } while (false)

#define GFO_LOG_TRACE(domain, ...)    GFO_LOG_AT(::tonb::foundation::log::Level::trace, domain, __VA_ARGS__)
#define GFO_LOG_DEBUG(domain, ...)    GFO_LOG_AT(::tonb::foundation::log::Level::debug, domain, __VA_ARGS__)
#define GFO_LOG_INFO(domain, ...)     GFO_LOG_AT(::tonb::foundation::log::Level::info, domain, __VA_ARGS__)
#define GFO_LOG_WARN(domain, ...)     GFO_LOG_AT(::tonb::foundation::log::Level::warn, domain, __VA_ARGS__)
#define GFO_LOG_ERROR(domain, ...)    GFO_LOG_AT(::tonb::foundation::log::Level::error, domain, __VA_ARGS__)
#define GFO_LOG_CRITICAL(domain, ...) GFO_LOG_AT(::tonb::foundation::log::Level::critical, domain, __VA_ARGS__)

#define GFO_LOG_TRACE_F(domain, fields, ...)    GFO_LOG_AT_F(::tonb::foundation::log::Level::trace, domain, fields, __VA_ARGS__)
#define GFO_LOG_DEBUG_F(domain, fields, ...)    GFO_LOG_AT_F(::tonb::foundation::log::Level::debug, domain, fields, __VA_ARGS__)
#define GFO_LOG_INFO_F(domain, fields, ...)     GFO_LOG_AT_F(::tonb::foundation::log::Level::info, domain, fields, __VA_ARGS__)
#define GFO_LOG_WARN_F(domain, fields, ...)     GFO_LOG_AT_F(::tonb::foundation::log::Level::warn, domain, fields, __VA_ARGS__)
#define GFO_LOG_ERROR_F(domain, fields, ...)    GFO_LOG_AT_F(::tonb::foundation::log::Level::error, domain, fields, __VA_ARGS__)
#define GFO_LOG_CRITICAL_F(domain, fields, ...) GFO_LOG_AT_F(::tonb::foundation::log::Level::critical, domain, fields, __VA_ARGS__)

#endif // TONB_FOUNDATION_LOG_MACROS_HXX

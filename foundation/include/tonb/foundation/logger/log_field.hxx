/**
* @file log_field.hxx
 * @brief Structured key-value fields attached to log records.
 *
 * @details
 * Foundation logging supports both a primary free-text message and an optional
 * list of structured fields. Structured fields are useful for filtering,
 * machine ingestion, export, and repeatable diagnostics.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_FIELD_HXX
#define TONB_FOUNDATION_LOG_FIELD_HXX

#include <string>
#include <utility>

namespace tonb::foundation::log {

    /**
     * @brief Structured key-value pair stored on a log record.
     */
    struct Field {
        /** @brief Field name. Expected to be a short machine-friendly token. */
        std::string key;

        /** @brief Field value represented as text. */
        std::string value;
    };

    /**
     * @brief Convenience helper for constructing a field.
     * @param key Field name.
     * @param value Field value.
     * @return Newly constructed Field.
     */
    inline Field kv(std::string key, std::string value) {
        return {std::move(key), std::move(value)};
    }

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_FIELD_HXX

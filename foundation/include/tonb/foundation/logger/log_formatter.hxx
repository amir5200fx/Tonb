/**
 * @file log_formatter.hxx
 * @brief Formatting abstractions for human-readable log output.
 *
 * @details
 * The original iXfract logging code duplicated text formatting logic between
 * the console sink and the buffer sink. This foundation version introduces a
 * small formatter abstraction so text-based sinks can share one formatting
 * policy while remaining independent in how they store or write the final text.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_FORMATTER_HXX
#define TONB_FOUNDATION_LOG_FORMATTER_HXX

#include <tonb/foundation/logger/log_record.hxx>
#include <tonb/foundation/module.hxx>

#include <memory>
#include <string>

namespace tonb::foundation::log {

    /**
     * @brief Abstract formatter for converting a log record into display text.
     */
    class Formatter {
    public:
        virtual ~Formatter() = default;

        /**
         * @brief Format a record into a single text line.
         * @param record Record to format.
         * @return Formatted single-line text.
         */
        TNB_NODISCARD virtual std::string format(const Record& record) const = 0;
    };

    /**
     * @brief Options controlling human-readable text formatting.
     */
    struct TextFormatterOptions {
        /** @brief Include UTC timestamp prefix. */
        bool include_timestamp = true;

        /** @brief Include flattened command path when present. */
        bool include_command = true;

        /** @brief Include source file and line. */
        bool include_location = false;

        /** @brief Include sequence number prefix. */
        bool include_sequence = false;
    };

    /**
     * @brief Shared formatter used by text-oriented sinks.
     */
    class TextFormatter final : public Formatter {
    public:
        /**
         * @brief Construct a formatter with the supplied options.
         * @param options Formatting options.
         */
        explicit TNBFOUND_EXPORT TextFormatter(TextFormatterOptions options = {});

        /**
         * @brief Format a record into one human-readable line.
         * @param record Record to format.
         * @return Formatted text line.
         */
        TNBFOUND_ND_EXPORT std::string format(const Record& record) const override;

        /**
         * @brief Return the current formatter options.
         * @return Formatter options snapshot.
         */
        TNBFOUND_ND_EXPORT const TextFormatterOptions& options() const noexcept;

    private:
        TextFormatterOptions options_{};
    };

    /**
     * @brief Create a shared text formatter with the supplied options.
     * @param options Formatting options.
     * @return Shared formatter instance.
     */
    TNBFOUND_ND_EXPORT std::shared_ptr<Formatter> make_text_formatter(
        TextFormatterOptions options = {});

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_FORMATTER_HXX

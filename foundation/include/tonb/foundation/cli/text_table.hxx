/**
 * @file text_table.hxx
 * @brief Small deterministic ASCII text-table helper used by CLI rendering.
 */
#pragma once
#ifndef TONB_FOUNDATION_CLI_TEXT_TABLE_HXX
#define TONB_FOUNDATION_CLI_TEXT_TABLE_HXX

#include <tonb/foundation/module.hxx>

#include <string>
#include <vector>

namespace tonb::foundation::cli {

    /** @brief Cell alignment mode. */
    enum class Align {
        left,
        right
    };

    /** @brief One table column definition. */
    struct Column final {
        std::string header;
        std::size_t min_width = 0;
        std::size_t max_width = 0;
        Align align = Align::left;
    };

    /** @brief Simple deterministic text table. */
    class TextTable final {
    public:
        using Row = std::vector<std::string>;

        explicit TextTable(std::vector<Column> columns);
        void add_row(Row row);
        TNBFOUND_ND_EXPORT std::vector<std::string> render_lines() const;

    private:
        std::vector<Column> columns_;
        std::vector<Row> rows_;
    };

} // namespace tonb::foundation::cli

#endif // TONB_FOUNDATION_CLI_TEXT_TABLE_HXX

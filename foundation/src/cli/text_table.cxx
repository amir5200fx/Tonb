/**
 * @file text_table.cxx
 * @brief Implementation of the lightweight ASCII table helper for CLI rendering.
 */
#include <tonb/foundation/cli/text_table.hxx>

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace tonb::foundation::cli {

    namespace {
        std::string truncate_with_ellipsis(const std::string& text, const std::size_t max_width) {
            if (max_width == 0 || text.size() <= max_width) {
                return text;
            }
            if (max_width <= 3) {
                return text.substr(0, max_width);
            }
            return text.substr(0, max_width - 3) + "...";
        }

        std::string pad_cell(const std::string& text, const std::size_t width, const Align align) {
            std::ostringstream oss;
            if (align == Align::right) {
                oss << std::right << std::setw(static_cast<int>(width)) << text;
            } else {
                oss << std::left << std::setw(static_cast<int>(width)) << text;
            }
            return oss.str();
        }

        std::string normalise_cell(const std::string& text, const Column& column) {
            if (column.max_width > 0) {
                return truncate_with_ellipsis(text, column.max_width);
            }
            return text;
        }
    }

    TextTable::TextTable(std::vector<Column> columns)
        : columns_(std::move(columns)) {
        if (columns_.empty()) {
            throw std::invalid_argument("TextTable: at least one column is required");
        }
    }

    void TextTable::add_row(Row row) {
        if (row.size() != columns_.size()) {
            throw std::invalid_argument("TextTable::add_row: row size does not match column count");
        }
        rows_.push_back(std::move(row));
    }

    std::vector<std::string> TextTable::render_lines() const {
        std::vector<std::size_t> widths(columns_.size(), 0);

        for (std::size_t i = 0; i < columns_.size(); ++i) {
            widths[i] = std::max(columns_[i].min_width, columns_[i].header.size());
            if (columns_[i].max_width > 0) {
                widths[i] = std::min(widths[i], columns_[i].max_width);
            }
        }

        std::vector<Row> cooked_rows;
        cooked_rows.reserve(rows_.size());
        for (const auto& row : rows_) {
            Row cooked;
            cooked.reserve(row.size());
            for (std::size_t i = 0; i < row.size(); ++i) {
                const auto cell = normalise_cell(row[i], columns_[i]);
                cooked.push_back(cell);
                widths[i] = std::max(widths[i], cell.size());
                if (columns_[i].max_width > 0) {
                    widths[i] = std::min(widths[i], columns_[i].max_width);
                }
            }
            cooked_rows.push_back(std::move(cooked));
        }

        std::vector<std::string> lines;
        std::ostringstream header;
        for (std::size_t i = 0; i < columns_.size(); ++i) {
            if (i > 0) header << " | ";
            header << pad_cell(columns_[i].header, widths[i], Align::left);
        }
        lines.push_back(header.str());

        std::ostringstream separator;
        for (std::size_t i = 0; i < columns_.size(); ++i) {
            if (i > 0) separator << "-+-";
            separator << std::string(widths[i], '-');
        }
        lines.push_back(separator.str());

        for (const auto& row : cooked_rows) {
            std::ostringstream line;
            for (std::size_t i = 0; i < row.size(); ++i) {
                if (i > 0) line << " | ";
                line << pad_cell(row[i], widths[i], columns_[i].align);
            }
            lines.push_back(line.str());
        }

        return lines;
    }

} // namespace tonb::foundation::cli

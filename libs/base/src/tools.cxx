//
// Created by amir on 8/22/25.
//
#include <tonb/base/tools.hxx>

namespace tonb::base {
    bool Tools::is_number(const std::string &str) noexcept {
        if (str.empty()) return false;
        return std::ranges::all_of(str, ::isdigit);
    }
    std::string Tools::to_lower(const std::string &str) noexcept {
        if (str.empty()) return "";
        auto c = str;
        std::ranges::transform(c, c.begin(), ::tolower);
        return c;
    }
    std::string Tools::to_upper(const std::string &str) noexcept {
        if (str.empty()) return "";
        auto c = str;
        std::ranges::transform(c, c.begin(), ::toupper);
        return c;
    }
}
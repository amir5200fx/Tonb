//
// Created by amir on 8/22/25.
//
#pragma once
#ifndef TONB_BASE_TOOLS_HXX
#define TONB_BASE_TOOLS_HXX

#include <tonb/base/module.hxx>
#include <tonb/base/precision.hxx>

#include <string>

namespace tonb::base {
    class Tools {
        public:
        static TNBBASE_EXPORT bool is_number(const std::string& str) noexcept;
        static TNBBASE_EXPORT std::string to_lower(const std::string& str) noexcept;
        static TNBBASE_EXPORT std::string to_upper(const std::string& str) noexcept;


    };
}
#endif  // TONB_BASE_TOOLS_HXX

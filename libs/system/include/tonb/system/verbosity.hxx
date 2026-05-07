//
// Created by amir on 8/16/25.
//
#pragma once
#ifndef TONB_SYSTEM_VERBOSITY_HXX
#define TONB_SYSTEM_VERBOSITY_HXX
#include <cstdint>

namespace tonb::system {
    enum class Verbosity : std::uint8_t {
        quiet = 0,
        info = 1,
        normal = 2,
        verbose = 3,
        debug = 4
    };
}
#endif //TONB_SYSTEM_VERBOSITY_HXX
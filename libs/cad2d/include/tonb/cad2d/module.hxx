//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_CAD2D_MODULE_HXX
#define TONB_CAD2D_MODULE_HXX
#include <tonb/system/module.hxx>

// If building/using a static lib, exports are no-ops
#if defined(TNBCAD2D_STATIC_MODULE)
#define TNBCAD2D_EXPORT
#define TNBCAD2D_NO_EXPORT
#else
// Windows (MSVC/MinGW)
#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(TNBCAD2D_EXPORTS) // set by CMake for the library itself
#define TNBCAD2D_EXPORT __declspec(dllexport)
#else
#define TNBCAD2D_EXPORT __declspec(dllimport)
#endif
#else
// GCC/Clang on Linux/macOS
#if __GNUC__ >= 4
#define TNBCAD2D_EXPORT __attribute__((visibility("default")))
#define TNBCAD2D_NO_EXPORT __attribute__((visibility("hidden")))
#else
#define TNBCAD2D_EXPORT
#define TNBCAD2D_NO_EXPORT
#endif
#endif
#endif

// ----- Combined: nodiscard + export/visibility -------------------------------
#define TNBCAD2D_ND_EXPORT      TNB_NODISCARD TNBCAD2D_EXPORT
#define TNBCAD2D_ND_EXPORT_MSG(msg) TNB_NODISCARD_MSG(msg) TNBCAD2D_EXPORT
#endif //TONB_CAD2D_MODULE_HXX
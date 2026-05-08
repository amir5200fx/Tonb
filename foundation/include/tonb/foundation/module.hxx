//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_FOUNDATION_MODULE_HXX
#define TONB_FOUNDATION_MODULE_HXX
#include <tonb/system/module.hxx>

// If building/using a static lib, exports are no-ops
#if defined(TNBFOUND_STATIC_MODULE)
#define TNBFOUND_EXPORT
#define TNBFOUND_NO_EXPORT
#else
// Windows (MSVC/MinGW)
#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(TNBFOUND_EXPORTS) // set by CMake for the library itself
#define TNBFOUND_EXPORT __declspec(dllexport)
#else
#define TNBFOUND_EXPORT __declspec(dllimport)
#endif
#else
// GCC/Clang on Linux/macOS
#if __GNUC__ >= 4
#define TNBFOUND_EXPORT __attribute__((visibility("default")))
#define TNBFOUND_NO_EXPORT __attribute__((visibility("hidden")))
#else
#define TNBFOUND_EXPORT
#define TNBFOUND_NO_EXPORT
#endif
#endif
#endif

// ----- Combined: nodiscard + export/visibility -------------------------------
#define TNBFOUND_ND_EXPORT      TNB_NODISCARD TNBFOUND_EXPORT
#define TNBFOUND_ND_EXPORT_MSG(msg) TNB_NODISCARD_MSG(msg) TNBFOUND_EXPORT
#endif //TONB_CAD2D_MODULE_HXX
//
// Created by amir on 8/22/25.
//
#pragma once
#ifndef TONB_BASE_MODULE_HXX
#define TONB_BASE_MODULE_HXX

#include <tonb/system/module.hxx>

// If building/using a static lib, exports are no-ops
#if defined(TNBBASE_STATIC_MODULE)
#define TNBBASE_EXPORT
#define TNBBASE_NO_EXPORT
#else
// Windows (MSVC/MinGW)
#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(TNBBASE_EXPORTS) // set by CMake for the library itself
#define TNBBASE_EXPORT __declspec(dllexport)
#else
#define TNBBASE_EXPORT __declspec(dllimport)
#endif
#else
// GCC/Clang on Linux/macOS
#if __GNUC__ >= 4
#define TNBBASE_EXPORT __attribute__((visibility("default")))
#define TNBBASE_NO_EXPORT __attribute__((visibility("hidden")))
#else
#define TNBBASE_EXPORT
#define TNBBASE_NO_EXPORT
#endif
#endif
#endif

// ----- Combined: nodiscard + export/visibility -------------------------------
#define TNBBASE_ND_EXPORT      TNB_NODISCARD TNBBASE_EXPORT
#define TNBBASE_ND_EXPORT_MSG(msg) TNB_NODISCARD_MSG(msg) TNBBASE_EXPORT

#endif  // TONB_BASE_MODULE_HXX

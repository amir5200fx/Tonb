//
// Created by amir on 8/24/25.
//
#pragma once
#ifndef TONB_CAD_MODULE_HXX
#define TONB_CAD_MODULE_HXX

#include <tonb/system/module.hxx>

// If building/using a static lib, exports are no-ops
#if defined(TNBCAD_STATIC_MODULE)
#define TNBCAD_EXPORT
#define TNBCAD_NO_EXPORT
#else
// Windows (MSVC/MinGW)
#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(TNBCAD_EXPORTS) // set by CMake for the library itself
#define TNBCAD_EXPORT __declspec(dllexport)
#else
#define TNBCAD_EXPORT __declspec(dllimport)
#endif
#else
// GCC/Clang on Linux/macOS
#if __GNUC__ >= 4
#define TNBCAD_EXPORT __attribute__((visibility("default")))
#define TNBCAD_NO_EXPORT __attribute__((visibility("hidden")))
#else
#define TNBCAD_EXPORT
#define TNBCAD_NO_EXPORT
#endif
#endif
#endif

// ----- Combined: nodiscard + export/visibility -------------------------------
#define TNBCAD_ND_EXPORT      TNB_NODISCARD TNBCAD_EXPORT
#define TNBCAD_ND_EXPORT_MSG(msg) TNB_NODISCARD_MSG(msg) TNBCAD_EXPORT

#endif //TONB_CAD_MODULE_HXX
//
// Created by amir on 8/19/25.
//
#pragma once
#ifndef TONB_SYSTEM_MODULE_HXX
#define TONB_SYSTEM_MODULE_HXX

// If building/using a static lib, exports are no-ops
#if defined(TNBSYSTEM_STATIC_MODULE)
#define TNBSYSTEM_EXPORT
#define TNBSYSTEM_NO_EXPORT
#else
// Windows (MSVC/MinGW)
#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(TNBSYSTEM_EXPORTS) // set by CMake for the library itself
#define TNBSYSTEM_EXPORT __declspec(dllexport)
#else
#define TNBSYSTEM_EXPORT __declspec(dllimport)
#endif
#else
// GCC/Clang on Linux/macOS
#if __GNUC__ >= 4
#define TNBSYSTEM_EXPORT __attribute__((visibility("default")))
#define TNBSYSTEM_NO_EXPORT __attribute__((visibility("hidden")))
#else
#define TNBSYSTEM_EXPORT
#define TNBSYSTEM_NO_EXPORT
#endif
#endif
#endif

// ----- [[nodiscard]] support ----------------------------------------
// Prefer C++17 [[nodiscard]] when available; otherwise use compiler-specific fallback.
#if defined(__has_cpp_attribute)
#if __has_cpp_attribute(nodiscard)
#define TNB_NODISCARD [[nodiscard]]
#define TNB_NORETURN [[noreturn]]
#endif
#endif
#ifndef TNB_NODISCARD
#if defined(__GNUG__) || defined(__clang__)
#define TNB_NODISCARD __attribute__((warn_unused_result))
#define TNB_NORETURN __attribute__((warn_unused_result))
#else
// MSVC prior to C++17 has no portable equivalent without SAL.
#define TNB_NODISCARD
#define TNB_NORETURN
#endif
#endif

// Optional: nodiscard with a message (C++20 and later). Falls back silently.
#if defined(__has_cpp_attribute)
#if __has_cpp_attribute(nodiscard) >= 201907
#define TNB_NODISCARD_MSG(msg) [[nodiscard(msg)]]
#else
#define TNB_NODISCARD_MSG TNB_NODISCARD
#endif
#else
#define TNB_NODISCARD_MSG(msg) TNB_NODISCARD
#endif

// ----- Combined: nodiscard + export/visibility -------------------------------
#define TNBSYSTEM_ND_EXPORT      TNB_NODISCARD TNBSYSTEM_EXPORT
#define TNBSYSTEM_ND_EXPORT_MSG(msg) TNB_NODISCARD_MSG(msg) TNBSYSTEM_EXPORT

// ----- Deprecation helpers ----------------------------------------------------
#if defined(__has_cpp_attribute)
  #if __has_cpp_attribute(deprecated)
    #define TNB_DEPRECATED [[deprecated]]
  #endif
#endif
#ifndef TNB_DEPRECATED
  #if defined(_MSC_VER)
    #define TNB_DEPRECATED __declspec(deprecated)
  #elif defined(__GNUC__) || defined(__clang__)
    #define TNB_DEPRECATED __attribute__((deprecated))
  #else
    #define TNB_DEPRECATED
  #endif
#endif

#endif //TONB_SYSTEM_MODULE_HXX
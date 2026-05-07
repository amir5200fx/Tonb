//
// Created by amir on 8/22/25.
//

#ifndef TONB_GEOMETRY_MODULE_HXX
#define TONB_GEOMETRY_MODULE_HXX

#include <tonb/system/module.hxx>

// If building/using a static lib, exports are no-ops
#if defined(TNBGEOM_STATIC_MODULE)
#define TNBGEOM_EXPORT
#define TNBGEOM_NO_EXPORT
#else
// Windows (MSVC/MinGW)
#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(TNBGEOM_EXPORTS) // set by CMake for the library itself
#define TNBGEOM_EXPORT __declspec(dllexport)
#else
#define TNBGEOM_EXPORT __declspec(dllimport)
#endif
#else
// GCC/Clang on Linux/macOS
#if __GNUC__ >= 4
#define TNBGEOM_EXPORT __attribute__((visibility("default")))
#define TNBGEOM_NO_EXPORT __attribute__((visibility("hidden")))
#else
#define TNBGEOM_EXPORT
#define TNBGEOM_NO_EXPORT
#endif
#endif
#endif

// ----- Combined: nodiscard + export/visibility -------------------------------
#define TNBGEOM_ND_EXPORT      TNB_NODISCARD TNBGEOM_EXPORT
#define TNBGEOM_ND_EXPORT_MSG(msg) TNB_NODISCARD_MSG(msg) TNBGEOM_EXPORT

#endif //TONB_GEOMETRY_MODULE_HXX
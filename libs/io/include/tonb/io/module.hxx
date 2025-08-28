//
// Created by amir on 8/27/25.
//

#ifndef TONB_IO_MODULE_HXX
#define TONB_IO_MODULE_HXX

#include <tonb/system/module.hxx>

// If building/using a static lib, exports are no-ops
#if defined(TNBIO_STATIC_MODULE)
#define TNBIO_EXPORT
#define TNBIO_NO_EXPORT
#else
// Windows (MSVC/MinGW)
#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(TNBIO_EXPORTS) // set by CMake for the library itself
#define TNBIO_EXPORT __declspec(dllexport)
#else
#define TNBIO_EXPORT __declspec(dllimport)
#endif
#else
// GCC/Clang on Linux/macOS
#if __GNUC__ >= 4
#define TNBIO_EXPORT __attribute__((visibility("default")))
#define TNBIO_NO_EXPORT __attribute__((visibility("hidden")))
#else
#define TNBIO_EXPORT
#define TNBIO_NO_EXPORT
#endif
#endif
#endif

// ----- Combined: nodiscard + export/visibility -------------------------------
#define TNBIO_ND_EXPORT      TNB_NODISCARD TNBIO_EXPORT
#define TNBIO_ND_EXPORT_MSG(msg) TNB_NODISCARD_MSG(msg) TNBIO_EXPORT

#endif //TONB_IO_MODULE_HXX
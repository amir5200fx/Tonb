//
// Created by amir on 02/09/2025.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT)
#include <tonb/geometry/occt/precision.hxx>

// OCCT
#include <opencascade/Precision.hxx>

namespace tonb::geometry::occt {
    bool Precision::is_infinite(const real x) {
        return ::Precision::IsInfinite(x);
    }
}
#else
static_assert(true, "src/occt/precision.cxx compiled without TONB_WITH_OCCT");
#endif

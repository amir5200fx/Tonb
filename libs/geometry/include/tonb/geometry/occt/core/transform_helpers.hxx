//
// Created by amir on 8/24/25.
//

#ifndef TONB_GEOMETRY_OCCT_TRANSFORM_HELPERS_HXX
#define TONB_GEOMETRY_OCCT_TRANSFORM_HELPERS_HXX

#include <tonb/geometry/occt/transform.hxx>
#include <opencascade/gp_Trsf.hxx>

namespace tonb::geometry::occt {
    struct Transform::Impl {
        gp_Trsf t;
    };
}

namespace tonb::geometry::occt::core {
    // interop
    struct occt_trsf_access {
        static Transform make(const gp_Trsf& t) {
            Transform result;
            result.pimpl_->t = t; return result;
        }
        static gp_Trsf get(const Transform& t) {
            return t.pimpl_->t;
        }
    };
}
#endif //TONB_GEOMETRY_OCCT_TRANSFORM_HELPERS_HXX
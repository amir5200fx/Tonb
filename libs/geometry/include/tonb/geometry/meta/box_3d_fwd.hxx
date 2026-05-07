//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_BOX_3D_FWD_HXX
#define TONB_GEOMETRY_META_BOX_3D_FWD_HXX
namespace tonb::geometry {
    // Forward Declarations
    class Pnt3d;
    namespace meta {
        // Forward Declarations
        template<class Point>
        class Box;

        using Box3d = Box<Pnt3d>;
    }
}
#endif //TONB_GEOMETRY_META_BOX_3D_FWD_HXX
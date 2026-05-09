//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_BOX_2D_FWD_HXX
#define TONB_GEOMETRY_META_BOX_2D_FWD_HXX

namespace tonb::geometry {
    // Forward Declarations
    class Pnt2d;

    namespace meta {
        // Forward Declarations
        template<class Point>
        class Box;

        using Box2d = Box<Pnt2d>;
    }
}
#endif //TONB_GEOMETRY_META_BOX_2D_FWD_HXX
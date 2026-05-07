//
// Created by amir on 11/8/25.
//
#pragma once
#ifndef TONB_GEOMETRY_FIELD_UNIFORM_SIZE_FUNC_2D_FWD_HXX
#define TONB_GEOMETRY_FIELD_UNIFORM_SIZE_FUNC_2D_FWD_HXX
namespace tonb::geometry {
    // Forward Declarations
    class Pnt2d;
    namespace field {
        template<class Point> class UniformSizeFunc;
        using UniformSizeFunc2D = UniformSizeFunc<Pnt2d>;
    }
}
#endif //TONB_GEOMETRY_FIELD_UNIFORM_SIZE_FUNC_2D_FWD_HXX
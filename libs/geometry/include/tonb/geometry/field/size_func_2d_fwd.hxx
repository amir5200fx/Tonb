//
// Created by amir on 11/8/25.
//

/**
 * @file size_func_2d_fwd.hxx
 * @brief Forward declarations for size function types in the Tonb geometry module.
 *
 * This header provides forward declarations for the generic `SizeFunc` template and
 * its 2D alias `sizeFunc2D`, which are used to represent spatially varying sizing
 * functions in geometric and meshing operations.
 *
 * Forward-declaring these types allows other components (such as triangulation or
 * spatial utilities) to reference sizing function interfaces without introducing
 * heavy dependencies on geometric field definitions.
 *
 */
#pragma once
#ifndef TONB_GEOMETRY_FIELD_SIZE_FUNC_2D_FWD_HXX
#define TONB_GEOMETRY_FIELD_SIZE_FUNC_2D_FWD_HXX

namespace tonb::geometry {
    // Forward Declarations
    class Pnt2d;
    namespace field {
        /**
         * @brief Templates abstract base class defining a scalar size function.
         * @tparam Point The point type (e.g., Pnt2d, Pnt3d, or a coordinate array).
         */
        template<class Point> class SizeFunc;

        /**
         * @brief Type alias for a 2D sizing function using Pnt2d points.
         *
         * Provides a convenient shorthand for the common case of 2D geometry sizing.
         */
        using SizeFunc2D = SizeFunc<Pnt2d>;
    }
}
#endif //TONB_GEOMETRY_FIELD_SIZE_FUNC_2D_FWD_HXX
//
// Created by amir on 8/25/25.
//
#include <tonb/geometry/meta/box_3d.hxx>

namespace tonb::geometry::meta {
    template<>
    template<>
    Box3d Box3d::subdivide<Box3d::Utility::Volume>(const Utility::Volume sub) const {
        switch (sub) {
            case Utility::Volume::half_down:
                return {
                    corner1(), avg(corner(Utility::Corner::fwd_down_right), corner(Utility::Corner::fwd_top_right))
                };
            case Utility::Volume::half_top:
                return {avg(corner(Utility::Corner::bwd_down_left), corner(Utility::Corner::bwd_top_left)), corner2()};
            case Utility::Volume::half_left:
                return {corner1(), avg(corner(Utility::Corner::fwd_top_left), corner(Utility::Corner::fwd_top_right))};
            case Utility::Volume::half_right:
                return {
                    avg(corner(Utility::Corner::bwd_down_left), corner(Utility::Corner::bwd_down_right)), corner2()
                };
            case Utility::Volume::half_back:
                return {corner1(), avg(corner(Utility::Corner::bwd_top_right), corner(Utility::Corner::fwd_top_right))};
            case Utility::Volume::half_front:
                return {avg(corner(Utility::Corner::bwd_down_left), corner(Utility::Corner::fwd_down_left)), corner2()};

            case Utility::Volume::bwd_eighth_down_left:
                return {corner1(), center()};
            case Utility::Volume::bwd_eighth_down_right:
                return {
                    avg(corner1(), corner(Utility::Corner::bwd_down_right)),
                    avg(corner2(), corner(Utility::Corner::bwd_down_right))
                };
            case Utility::Volume::bwd_eighth_top_right:
                return {
                    avg(corner1(), corner(Utility::Corner::bwd_top_right)),
                    avg(corner2(), corner(Utility::Corner::bwd_top_right))
                };
            case Utility::Volume::bwd_eighth_top_left:
                return {
                    avg(corner1(), corner(Utility::Corner::bwd_top_left)),
                    avg(corner2(), corner(Utility::Corner::bwd_top_left))
                };


            case Utility::Volume::fwd_eighth_down_left:
                return {
                    avg(corner1(), corner(Utility::Corner::fwd_down_left)),
                    avg(corner2(), corner(Utility::Corner::fwd_down_left))
                };
            case Utility::Volume::fwd_eighth_down_right:
                return {
                    avg(corner1(), corner(Utility::Corner::fwd_down_right)),
                    avg(corner2(), corner(Utility::Corner::fwd_down_right))
                };
            case Utility::Volume::fwd_eighth_top_right:
                return {center(), corner2()};
            case Utility::Volume::fwd_eighth_top_left:
                return {
                    avg(corner1(), corner(Utility::Corner::fwd_top_left)),
                    avg(corner2(), corner(Utility::Corner::fwd_top_left))
                };

        }
        return {};
    }

    template<>
    template<>
    Pnt3d Box3d::corner<Box3d::Utility::Corner>(const Utility::Corner c) const {
        const auto& p0 = corner1();
        const auto& p1 = corner2();

        switch (c) {
            case Utility::Corner::fwd_down_left: return {p0.x(), p0.y(), p1.z()};
            case Utility::Corner::fwd_down_right: return {p1.x(), p0.y(), p1.z()};
            case Utility::Corner::fwd_top_right: return p1;
            case Utility::Corner::fwd_top_left: return {p0.x(), p1.y(), p1.z()};

            case Utility::Corner::bwd_down_left: return p0;
            case Utility::Corner::bwd_down_right: return {p1.x(), p0.y(), p0.z()};
            case Utility::Corner::bwd_top_right: return {p1.x(), p1.y(), p0.z()};
            case Utility::Corner::bwd_top_left: return {p0.x(), p1.y(), p0.z()};
        }
        return {};
    }
}
//
// Created by amir on 8/25/25.
//
#include <tonb/geometry/meta/box_2d.hxx>

namespace tonb::geometry::meta {
    template<>
    template<>
    Box2d Box2d::subdivide<Box2d::Utility::Area>(const Utility::Area sub) const {
        switch (sub) {
            case Utility::Area::half_down:
                return {corner1(), avg(corner(Utility::Corner::down_right), corner(Utility::Corner::top_right))};
            case Utility::Area::half_top:
                return {avg(corner(Utility::Corner::down_left), corner(Utility::Corner::top_left)), corner2()};
            case Utility::Area::half_left:
                return {corner1(), avg(corner(Utility::Corner::top_left), corner(Utility::Corner::top_right))};
            case Utility::Area::half_right:
                return {avg(corner(Utility::Corner::down_left), corner(Utility::Corner::down_right)), corner2()};

            case Utility::Area::quarter_down_left:
                return {corner1(), center()};
            case Utility::Area::quarter_down_right:
                return {
                    avg(corner(Utility::Corner::down_left), corner(Utility::Corner::down_right)),
                    avg(corner(Utility::Corner::down_right), corner(Utility::Corner::top_right))
                };
            case Utility::Area::quarter_top_right:
                return {center(), corner2()};
            case Utility::Area::quarter_top_left:
                return {
                    avg(corner(Utility::Corner::down_left), corner(Utility::Corner::top_left)),
                    avg(corner(Utility::Corner::top_left), corner(Utility::Corner::top_right))
                };
        }
        return {};
    }

    template<>
    template<>
    Pnt2d Box2d::corner(const Utility::Corner c) const {
        switch (c) {
            case Utility::Corner::down_left:
                return corner1();
            case Utility::Corner::down_right:
                return {corner2().x(), corner1().y()};
            case Utility::Corner::top_right:
                return corner2();
            case Utility::Corner::top_left:
                return {corner1().x(), corner2().y()};
        }
        return {};
    }

}
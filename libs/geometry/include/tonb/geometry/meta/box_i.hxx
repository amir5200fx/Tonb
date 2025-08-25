//
// Created by amir on 8/23/25.
//
#pragma once
namespace tonb::geometry::meta {

    template<class Point>
    void Box<Point>::normalize() noexcept {
        for (size_t d = 0; d < static_cast<size_t>(Point::dim); ++d) {
            if (corners_[0][d] > corners_[1][d]) {std::swap(corners_[0][d], corners_[1][d]);}
        }
    }

    template<class Point>
    void Box<Point>::set_corners(Point corner1, Point corner2) noexcept {
        corners_ = {std::move(corner1), std::move(corner2)};
    }

    template<class Point>
    real Box<Point>::diameter() const noexcept {
        return std::sqrt(diameter_squared());
    }
    template<class Point>
    real Box<Point>::diameter_squared() const noexcept {
        return distance(corner1(), corner2());
    }

    template<class Point>
    bool Box<Point>::contains(const Point &p) const noexcept {
        for (size_t d = 0; d < static_cast<size_t>(Point::dim); ++d) {
            if (p[d] < corners_[0][d]) return false;
            if (p[d] > corners_[1][d]) return false;
        }
        return true;
    }

    template<class Point>
    bool Box<Point>::intersects(const Box &other) const noexcept {
        for (size_t d = 0; d < static_cast<size_t>(Point::dim); ++d) {
            if (const auto r = range(static_cast<Direction>(d));
                r.inside(other.corners_[0][d]) || r.inside(other.corners_[1][d])) return true;
        }
        return false;
    }

    template<class Point>
    Point Box<Point>::center() const noexcept {
        return Point::avg(corner1(), corner2());
    }

    template<class Point>
    real Box<Point>::volume() const noexcept {
        return Point::volume(corner1(), corner2());
    }

    template<class Point>
    Box<Point> Box<Point>::extended(const std::array<real, Point::dim> &components) const {
        auto r = *this; r.extend(components); return r;
    }
    template<class Point>
    void Box<Point>::extend(const std::array<real, Point::dim> &components) {
        for (size_t d = 0; d < static_cast<size_t>(Point::dim); ++d) {
            corners_[0][d] -= components[d];
            corners_[1][d] += components[d];
        }
    }

    template<class Point>
    std::array<real, Point::dim> Box<Point>::length() const noexcept {
        std::array<real, Point::dim> r;
        for (size_t d = 0; d < static_cast<size_t>(Point::dim); ++d) {
            r[d] = corners_[1][d] - corners_[0][d];
        }
        return r;
    }

    template<class Point>
    typename Box<Point>::Range Box<Point>::range(const Direction d) const {
        Range r; range(d, r); return r;
    }
    template<class Point>
    void Box<Point>::range(Direction d, Range &r) const{
        r.set(min()[static_cast<size_t>(d)], max()[static_cast<size_t>(d)]);
    }

    template<class Point>
    void Box<Point>::add(const Point & p) {
        for (size_t d = 0; d < static_cast<size_t>(Point::dim); ++d) {
            corners_[0][d] = std::min(corners_[0][d], p[d]);
            corners_[1][d] = std::max(corners_[1][d], p[d]);
        }
    }
    template<class Point>
    void Box<Point>::add(const Box &other) {
        add(other.min()); add(other.max());
    }

}

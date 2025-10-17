//
// Created by amir on 30/09/2025.
//
#include <stdexcept>

// namespace tonb::geometry::occt {
//
//     struct Axis22d::Impl { bool ok{false}; };
//     bool Axis22d::s_valid(const std::shared_ptr<Impl>& p) noexcept { return p && p->ok; }
//
//     Axis22d::Axis22d(const Point2d&, const std::array<real,2>&, const std::array<real,2>&, bool)
//         : pimpl_(std::make_shared<Impl>()) {}
//
//     Axis22d::Axis22d(const Point2d&, const std::array<real,2>&, bool)
//         : pimpl_(std::make_shared<Impl>()) {}
//
//     bool Axis22d::is_valid() const noexcept { return s_valid(pimpl_); }
//     Point2d Axis22d::origin() const { return {}; }
//     std::array<real,2> Axis22d::x_direction() const { return {0,0}; }
//     std::array<real,2> Axis22d::y_direction() const { return {0,0}; }
//     bool Axis22d::is_direct() const noexcept { return false; }
//
//     Axis22d Axis22d::with_origin(const Point2d&) const { return {}; }
//     Axis22d Axis22d::with_x_direction(const std::array<real,2>&) const { return {}; }
//     Axis22d Axis22d::with_y_direction(const std::array<real,2>&) const { return {}; }
//
//     Axis22d Axis22d::mirrored(const Point2d&) const { return {}; }
//     Axis22d Axis22d::mirrored(const Axis2d&) const { return {}; }
//     Axis22d Axis22d::rotated(const Point2d&, real) const { return {}; }
//     Axis22d Axis22d::scaled(const Point2d&, real) const { return {}; }
//     Axis22d Axis22d::translated(real, real) const { return {}; }
//
//     void Axis22d::mirror(const Point2d&) {}
//     void Axis22d::mirror(const Axis2d&) {}
//     void Axis22d::rotate(const Point2d&, real) {}
//     void Axis22d::scale(const Point2d&, real) {}
//     void Axis22d::translate(real, real) {}
//
//     namespace core {
//         struct occt_axis22d_access {
//             static int get(const Axis22d&) { return 0; } // stub to satisfy friend
//             static Axis22d make(...) { return {}; }
//         };
//     }
//
// } // namespace tonb::geometry::occt
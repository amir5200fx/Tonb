//
// Created by amir on 30/09/2025.
//
// namespace tonb::geometry::occt {
//     struct Circle2d::Impl { real r{0}; };
//
//     Circle2d::Circle2d(const Point2d&, const real) : pimpl_(std::make_shared<Impl>()) {}
//     Circle2d::Circle2d(const Axis2d&, const real) : pimpl_(std::make_shared<Impl>()) {}
//
//     bool Circle2d::is_valid() const noexcept { return pimpl_ && pimpl_->r > 0; }
//     Point2d Circle2d::centre() const { return {}; }
//     Axis2d Circle2d::axis() const { return {}; }
//     real Circle2d::radius() const noexcept { return pimpl_ ? pimpl_->r : 0; }
//     real Circle2d::length() const noexcept { return 0; }
//
//     Circle2d Circle2d::with_centre(const Point2d&) const { return {}; }
//     Circle2d Circle2d::with_radius(real) const { return {}; }
//     Circle2d Circle2d::mirrored(const Point2d&) const { return {}; }
//     Circle2d Circle2d::mirrored(const Axis2d&) const { return {}; }
//     Circle2d Circle2d::rotated(const Point2d&, real) const { return {}; }
//     Circle2d Circle2d::scaled(const Point2d&, real) const { return {}; }
//     Circle2d Circle2d::translated(real, real) const { return {}; }
//
//     void Circle2d::mirror(const Point2d&) {}
//     void Circle2d::mirror(const Axis2d&) {}
//     void Circle2d::rotate(const Point2d&, real) {}
//     void Circle2d::scale(const Point2d&, real) {}
//     void Circle2d::translate(real, real) {}
// }
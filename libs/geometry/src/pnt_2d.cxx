//
// Created by amir on 8/22/25.
//
#include <cmath>
#include <fstream>
#include <tonb/geometry/pnt_2d.hxx>

// ---- static data
const tonb::geometry::Pnt2d tonb::geometry::Pnt2d::null{0,0};

// ---- mutating transforms ---------------------------------------------------

tonb::geometry::Pnt2d &tonb::geometry::Pnt2d::translate(const real dx, const real dy) noexcept {
    components_[0] += dx;
    components_[1] += dy;
    return *this;
}

tonb::geometry::Pnt2d &tonb::geometry::Pnt2d::scale(const real s) noexcept {
    components_[0] *= s;
    components_[1] *= s;
    return *this;
}

tonb::geometry::Pnt2d &tonb::geometry::Pnt2d::rotate(const real angle) {
    const real c = static_cast<real>(std::cos(angle));
    const real s = static_cast<real>(std::sin(angle));
    const real x = components_[0];
    const real y = components_[1];
    components_[0] = c * x - s * y;
    components_[1] = s * x + c * y;
    return *this;
}

tonb::geometry::Pnt2d tonb::geometry::Pnt2d::translated(const real dx, const real dy) const noexcept {
    auto r = *this;
    r.translate(dx, dy);
    return r;
}

tonb::geometry::Pnt2d tonb::geometry::Pnt2d::scaled(const real s) const noexcept {
    auto r = *this;
    r.scale(s);
    return r;
}

tonb::geometry::Pnt2d tonb::geometry::Pnt2d::rotated(const real angle) const noexcept {
    auto r = *this;
    r.rotate(angle);
    return r;
}

// ---- I/O -------------------------------------------------------------------

void tonb::geometry::Pnt2d::print(std::ostream &os) const noexcept {
    os << "(" << components_[0] << ", " << components_[1] << ")";
}

void tonb::geometry::Pnt2d::write_to_plt(std::fstream &os) const noexcept {
    // simple "x y \n" format
    os << components_[0] << ", " << components_[1] <<'\n';
}


// ---- free utilities ---------------------------------------------------------

namespace tonb::geometry {
    Pnt2d avg(const Pnt2d& p1, const Pnt2d& p2) noexcept {
        const auto xm = 0.5*(p1.x() + p2.x());
        const auto ym = 0.5*(p1.y() + p2.y());
        return {xm, ym};
    }
    Pnt2d avg(const Pnt2d& p1, const Pnt2d& p2, const Pnt2d& p3) noexcept {
        const auto xm = (p1.x() + p2.x() + p3.x()) / 3.0;
        const auto ym = (p1.y() + p2.y() + p3.y()) / 3.0;
        return {xm, ym};
    }

    real volume(const Pnt2d& p1, const Pnt2d& p2) noexcept {
        const auto dx = p2.x() - p1.x();
        const auto dy = p2.y() - p1.y();
        return dx*dy;
    }
}

tonb::real tonb::geometry::distance_sq(const Pnt2d &p1, const Pnt2d &p2) {
    const real dx = p1.x() - p2.x();
    const real dy = p1.y() - p2.y();
    return dx * dx + dy * dy;
}

tonb::real tonb::geometry::distance(const Pnt2d &p1, const Pnt2d &p2) {
    return static_cast<real>(std::sqrt(distance_sq(p1, p2)));
}

bool tonb::geometry::almost_equal(const Pnt2d &p1, const Pnt2d &p2) {
    return base::nearly_equal(p1.x(), p2.x()) && base::nearly_equal(p1.y(), p2.y());
}





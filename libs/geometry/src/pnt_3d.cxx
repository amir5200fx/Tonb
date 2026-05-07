//
// Created by amir on 8/23/25.
//
#include <cmath>
#include <fstream>
#include <tonb/geometry/pnt_3d.hxx>

// ---- static data
const tonb::geometry::Pnt3d tonb::geometry::Pnt3d::null{0,0,0};

constexpr tonb::real tonb::geometry::Pnt3d::at(const size_t i) const {
    assert(i < components_.size());
    return components_[i];
}

constexpr tonb::real& tonb::geometry::Pnt3d::at(const size_t i) {
    assert(i < components_.size());
    return components_[i];
}

// ---- mutating transforms -----------------------------------------------

tonb::geometry::Pnt3d &tonb::geometry::Pnt3d::translate(real dx, real dy, real dz) noexcept {
    components_[0] += dx;
    components_[1] += dy;
    components_[2] += dz;
    return *this;
}

tonb::geometry::Pnt3d& tonb::geometry::Pnt3d::scale(real s) noexcept {
    components_[0] *= s;
    components_[1] *= s;
    components_[2] *= s;
    return *this;
}

tonb::geometry::Pnt3d tonb::geometry::Pnt3d::translated(real dx, real dy, real dz) const noexcept {
    auto r = *this;
    r.translate(dx, dy, dz);
    return r;
}

tonb::geometry::Pnt3d tonb::geometry::Pnt3d::scaled(real s) const noexcept {
    auto r = *this;
    r.scale(s);
    return r;
}

// ---- I/O ----------------------------------------------------------------

void tonb::geometry::Pnt3d::print(std::ostream &os) const noexcept {
    os << '(' << components_[0] << ',' << components_[1] << ',' << components_[2] << ')';
}

void tonb::geometry::Pnt3d::write_to_plt(std::ostream &os) const noexcept {
    os<<components_[0]<<", "<<components_[1]<<", "<<components_[2]<<'\n';
}

// ---- free utilities ---------------------------------------------------------

namespace tonb::geometry {
    Pnt3d avg(const Pnt3d& p1, const Pnt3d& p2) noexcept {
        const auto xm = 0.5*(p1.x() + p2.x());
        const auto ym = 0.5*(p1.y() + p2.y());
        const auto zm = 0.5*(p1.z() + p2.z());
        return {xm, ym, zm};
    }
    Pnt3d avg(const Pnt3d &p1, const Pnt3d &p2, const Pnt3d &p3) noexcept {
        const auto xm = (p1.x() + p2.x() + p3.x()) / 3.0;
        const auto ym = (p1.y() + p2.y() + p3.y()) / 3.0;
        const auto zm = (p1.z() + p2.z() + p3.z()) / 3.0;
        return {xm, ym, zm};
    }
    Pnt3d avg(const Pnt3d &p1, const Pnt3d &p2, const Pnt3d &p3, const Pnt3d &p4) noexcept {
        const auto xm = 0.25*(p1.x() + p2.x() + p3.x() + p4.x());
        const auto ym = 0.25*(p1.y() + p2.y() + p3.y() + p4.y());
        const auto zm = 0.25*(p1.z() + p2.z() + p3.z() + p4.z());
        return {xm, ym, zm};
    }

    real volume(const Pnt3d &p1, const Pnt3d &p2) noexcept {
        const auto dx = p2.x() - p1.x();
        const auto dy = p2.y() - p1.y();
        const auto dz = p2.z() - p1.z();
        return dx*dy*dz;
    }

}

tonb::real tonb::geometry::distance_sq(const Pnt3d &p1, const Pnt3d &p2) {
    const real dx = p1[0] - p2[0];
    const real dy = p1[1] - p2[1];
    const real dz = p1[2] - p2[2];
    return dx*dx + dy*dy + dz*dz;
}

tonb::real tonb::geometry::distance(const Pnt3d &p1, const Pnt3d &p2) {
    return static_cast<real>(std::sqrt(distance_sq(p1, p2)));
}

bool tonb::geometry::almost_equal(const Pnt3d &p1, const Pnt3d &p2) {
    return base::nearly_equal(p1.x(), p2.x()) && base::nearly_equal(p1.y(), p2.y()) && base::nearly_equal(
               p1.z(), p2.z());
}


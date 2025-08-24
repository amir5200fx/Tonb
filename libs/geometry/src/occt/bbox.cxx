//
// Created by amir on 8/24/25.
//
#include <tonb/geometry/occt/bbox.hxx>
#include <tonb/geometry/occt/adapters.hxx>
#include <tonb/geometry/meta/box_3d.hxx>
#include <tonb/geometry/pnt_3d.hxx>

// OCCT headers only here
#include <opencascade/Bnd_Box.hxx>
#include <opencascade/gp_Pnt.hxx>

namespace tonb::geometry::occt {

    struct BBox::Impl {
        Bnd_Box box;  // real OCCT box
        Impl() {box.SetVoid();}
    };

    BBox::BBox() noexcept : p_(std::make_shared<Impl>())
    {}

    BBox BBox::from_min_max(const std::array<real, 3>& mn, const std::array<real, 3>& mx) noexcept {
        BBox b;
        b.p_->box = Bnd_Box{core::make_gp_pnt(mn), core::make_gp_pnt(mx)};
        return b;
    }

    bool BBox::empty() const noexcept {
        return !p_ || p_->box.IsVoid();
    }

    void BBox::clear() noexcept {
        if (!p_) p_ = std::make_shared<Impl>();
        p_->box.SetVoid();
    }

    void BBox::add(const real x, const real y, const real z) noexcept {
        if (!p_) p_ = std::make_shared<Impl>();
        p_->box.Add(core::make_gp_pnt({x, y, z}));
    }

    void BBox::add(const std::array<real, 3> &p) noexcept {
        if (!p_) p_ = std::make_shared<Impl>();
        p_->box.Add(core::make_gp_pnt(p));
    }

    void BBox::add(const BBox &other) noexcept {
        if (!p_) p_ = std::make_shared<Impl>();
        if (!other.p_ || other.p_->box.IsVoid()) { return;}
        p_->box.Add(other.p_->box);
    }

    std::array<real, 3> BBox::min() const noexcept {
        if (empty()) return {0,0,0};
        Standard_Real xmin, ymin, zmin, xmax, ymax, zmax;
        p_->box.Get(xmin, ymin, zmin, xmax, ymax, zmax);
        return {static_cast<real>(xmin), static_cast<real>(ymin), static_cast<real>(zmin)};
    }

    std::array<real, 3> BBox::max() const noexcept {
        if (empty()) return {0,0,0};
        Standard_Real xmin, ymin, zmin, xmax, ymax, zmax;
        p_->box.Get(xmin, ymin, zmin, xmax, ymax, zmax);
        return {static_cast<real>(xmax), static_cast<real>(ymax), static_cast<real>(zmax)};
    }

    void BBox::expand(const double delta) const noexcept {
        if (delta <= 0.0 || empty()) return;
        const auto mn = min();
        const auto mx = max();
        p_->box.Update(mn[0] - delta, mn[1] - delta, mn[2] - delta, mx[0] + delta, mx[1] + delta, mx[2] + delta);
    }

    void BBox::set_gap(const double gap) const noexcept {
        if (!p_) return;
        p_->box.SetGap(gap);
    }

    meta::Box3d BBox::to_box() const noexcept {
        return meta::Box3d{Pnt3d{min()}, Pnt3d{max()}};
    }
}

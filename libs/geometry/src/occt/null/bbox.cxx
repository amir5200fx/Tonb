//
// Created by amir on 8/24/25.
//
#include <tonb/geometry/occt/bbox.hxx>

#include <algorithm>
#include <limits>

namespace tonb::geometry::occt {

    struct BBox::Impl {
        real mn[3];
        real mx[3];

        bool is_void{true};
        real gap{0.0};

        Impl() {
            mn[0] = mn[1] = mn[2] = std::numeric_limits<real>::infinity();
            mx[0] = mx[1] = mx[2] = std::numeric_limits<real>::infinity();
        }
    };

    BBox::BBox() noexcept : p_(std::make_shared<Impl>()) {}

    BBox BBox::from_min_max(const std::array<real, 3>& mn, const std::array<real, 3>& mx) noexcept {
        BBox b;
        b.p_->mn[0] = mn[0]; b.p_->mn[1] = mn[1]; b.p_->mn[2] = mn[2];
        b.p_->mx[0] = mx[0]; b.p_->mx[1] = mx[1]; b.p_->mx[2] = mx[2];
        b.p_->is_void = false;
        return b;
    }

    bool BBox::empty() const noexcept {
        return !p_ || p_->is_void ||!(p_->mx[0] >= p_->mn[0] && p_->mx[1] >= p_->mn[1] && p_->mx[2] >= p_->mn[2]);
    }

    void BBox::clear() noexcept {
        if (!p_) p_ = std::make_shared<Impl>();
        *p_ = Impl{};
    }

    void BBox::add(const real x, const real y, const real z) noexcept {
        if (!p_) p_ = std::make_shared<Impl>();
        if (p_->is_void) {
            p_->mn[0] = p_->mx[0] = x; p_->mn[1] = p_->mx[1] = y; p_->mn[2] = p_->mx[2] = z;
            p_->is_void = false;
        } else {
            p_->mn[0] = std::min(p_->mn[0], x); p_->mn[1] = std::min(p_->mn[1], y);
            p_->mn[2] = std::min(p_->mn[2], z);
            p_->mx[0] = std::max(p_->mx[0], x); p_->mx[1] = std::max(p_->mx[1], y);
            p_->mx[2] = std::max(p_->mx[2], z);
        }
    }

    void BBox::add(const BBox& other) noexcept {
        if (!p_) p_ = std::make_shared<Impl>();
        if (other.empty()) return;
        auto omn = other.min();
        auto omx = other.max();
        add(omn[0], omn[1], omn[2]);
        add(omx[0], omx[1], omx[2]);
    }

    std::array<real, 3> BBox::min() const noexcept {
        if (empty()) return {0, 0, 0};
        return {p_->mn[0], p_->mn[1], p_->mn[2]};
    }

    std::array<real, 3> BBox::max() const noexcept {
        if (empty()) return {0, 0, 0};
        return {p_->mx[0], p_->mx[1], p_->mx[2]};
    }

    void BBox::expand(const real d) const noexcept {
        if (d <= 0.0 || empty()) return;
        p_->mn[0] -=d; p_->mn[1] -= d; p_->mn[2] -= d;
        p_->mx[0] += d; p_->mx[1] += d; p_->mx[2] += d;
    }

    void BBox::set_gap(const real g) const noexcept {
        if (!p_) return;
        p_->gap = g; // retained for consistency; no effect in null build
    }
}
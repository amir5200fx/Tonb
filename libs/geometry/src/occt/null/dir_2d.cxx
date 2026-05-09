//
// Created by amir on 30/09/2025.
//
#include <tonb/geometry/occt/dir_2d.hxx>

namespace tonb::geometry::occt {

    struct Dirction2d::Impl { bool ok{false}; };
    bool Dirction2d::s_valid(const std::shared_ptr<Impl>& p) noexcept { return p && p->ok; }

    Dirction2d::Dirction2d(const real, const real) : pimpl_(std::make_shared<Impl>()) {}
    Dirction2d::Dirction2d(const std::array<real,2>&) : pimpl_(std::make_shared<Impl>()) {}

    bool Dirction2d::is_valid() const noexcept { return s_valid(pimpl_); }
    std::array<real,2> Dirction2d::components() const noexcept { return {0,0}; }
    real Dirction2d::u() const noexcept { return 0; }
    real Dirction2d::v() const noexcept { return 0; }
    real Dirction2d::angle(const Dirction2d&) const { return 0; }
    bool Dirction2d::is_equal(const Dirction2d&, real) const { return false; }

    Dirction2d Dirction2d::mirrored(const Axis2d&) const { return {}; }
    Dirction2d Dirction2d::rotated(real) const { return {}; }

    void Dirction2d::mirror(const Axis2d&) {}
    void Dirction2d::rotate(real) {}
    void Dirction2d::reverse() {}

} // namespace tonb::geometry::occt
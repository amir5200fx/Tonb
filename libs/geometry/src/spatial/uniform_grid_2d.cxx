//
// Created by amir on 03/09/2025.
//
#include <tonb/geometry/spatial/uniform_grid_2d.hxx>

#include <tonb/geometry/meta/box_2d.hxx>

namespace tonb::geometry::spatial {
    void UniformGrid2d::build(const meta::Box2d& domain, int nx, int ny) {
        min_ = {domain.min().x(), domain.min().y()};
        max_ = {domain.max().x(), domain.max().y()};

        nx_ = std::max(1, nx);
        ny_ = std::max(1, ny);

        const real ex = std::max<real>(std::nextafter(max_.u() - min_.u(), static_cast<real>(1)), static_cast<real>(1e-12));
        const real ey = std::max<real>(std::nextafter(max_.v() - min_.v(), static_cast<real>(1)), static_cast<real>(1e-12));
        hx_ = ex / nx_;
        hy_ = ey / ny_;

        buckets_.assign(static_cast<size_t>(nx_ * ny_), {});
        built_ = true;
    }

    void UniformGrid2d::insert(index_t id, const meta::Box2d& box) {
        if (!built_) return;
        const auto ijmin = clamp_idx(to_idx({box.min().x(), box.min().y()}));
        const auto ijmax = clamp_idx(to_idx({box.max().x(), box.max().y()}));
        for (int j = ijmin.second; j <= ijmax.second; ++j)
            for (int i = ijmin.first; i <= ijmax.first; ++i)
                buckets_[index(i, j)].push_back(id);
    }

    void UniformGrid2d::query_aabb(const meta::Box2d &region, std::vector<index_t> &out) const {
        if (!built_) return;
        auto ijmin = clamp_idx(to_idx({region.min().x(), region.min().y()}));
        auto ijmax = clamp_idx(to_idx({region.max().x(), region.max().y()}));
        for (int j = ijmin.second; j <= ijmax.second; ++j)
            for (int i = ijmin.first; i <= ijmax.first; ++i) {
                const auto& b = buckets_[index(i, j)];
                out.insert(out.end(), b.begin(), b.end());
            }
    }

    const std::vector<index_t>& UniformGrid2d::query_cell(const Vec2d& p) const {
        static const std::vector<index_t> kEmpty;
        if (!built_) return kEmpty;
        auto ij = clamp_idx(to_idx(p));
        return buckets_[index(ij.first, ij.second)];
    }

    meta::Box2d UniformGrid2d::domain() const {
        return {{min_.u(), min_.v()}, {max_.u(), max_.v()}};
    }
}
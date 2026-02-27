//
// Created by amir on 11/2/25.
//
#pragma once
#include <ranges>

template<class T>
tonb::geometry::spatial::HashGrid2d<T>::HashGrid2d(real cell)
    : cell_size_(cell), inv_cell_(1.0/cell) {}

template<class T>
void tonb::geometry::spatial::HashGrid2d<T>::clear() {
    buckets_.clear();
    items_.clear();
}

template<class T>
std::size_t tonb::geometry::spatial::HashGrid2d<T>::insert(const T &item) {
    items_.push_back(item);
    std::size_t id = items_.size() - 1;
    const Key k = key_of(items_[id]);
    buckets_[k].push_back(id);
    return id;
}

template<class T>
void tonb::geometry::spatial::HashGrid2d<T>::update(std::size_t id) {
    const Key oldk = locate_[id];
    const Key newk = key_of(items_[id]);
    if (oldk == newk) return;
    auto& vec = buckets_[oldk];
    for (std::size_t i=0;i<vec.size();++i) {
        if (vec[i]==id) { vec[i]=vec.back(); vec.pop_back(); break; }
    }
    buckets_[newk].push_back(id);
    locate_[id] = newk;
}

template<class T>
void tonb::geometry::spatial::HashGrid2d<T>::erase(const std::size_t id) {
    const Key k = locate_[id];
    auto& vec = buckets_[k];
    for (std::size_t i=0;i<vec.size();++i) {
        if (vec[i]==id) { vec[i]=vec.back(); vec.pop_back(); break; }
    }
    // leave a tombstone in items_ (optional compacting method could be added)
}

template<class T>
template<tonb::geometry::spatial::PointLike P>
void tonb::geometry::spatial::HashGrid2d<T>::radius_query(const P &p, real r, std::vector<std::size_t> &out_ids) const {
    out_ids.clear();
    const int rx = static_cast<int>(std::ceil(r * inv_cell_));
    const auto kp = key_of_point(p);
    for (int dy=-rx; dy<=rx; ++dy) {
        for (int dx=-rx; dx<=rx; ++dx) {
            Key k{kp.first+dx, kp.second+dy};
            auto it = buckets_.find(k);
            if (it==buckets_.end()) continue;
            for (auto id: it->second) {
                auto q = get_point_(items_[id]);
                const double dxp = q[0]-p[0], dyp = q[1]-p[1];
                if (dxp*dxp + dyp*dyp <= r*r) out_ids.push_back(id);
            }
        }
    }
}

template<class T>
template<tonb::geometry::spatial::PointLike P>
void tonb::geometry::spatial::HashGrid2d<T>::aabb_query(const P &bmin, const P &bmax,
    std::vector<std::size_t> &out_ids) const {
    out_ids.clear();
    auto kmin = key_of_point(bmin);
    auto kmax = key_of_point(bmax);
    for (int y=kmin.second; y<=kmax.second; ++y) {
        for (int x=kmin.first; x<=kmax.first; ++x) {
            Key k{x,y};
            auto it = buckets_.find(k);
            if (it==buckets_.end()) continue;
            for (auto id: it->second) {
                auto q = get_point_(items_[id]);
                if (q[0] >= bmin[0] && q[0] <= bmax[0] &&
                    q[1] >= bmin[1] && q[1] <= bmax[1]) {
                    out_ids.push_back(id);
                    }
            }
        }
    }
}

template<class T>
template<tonb::geometry::spatial::PointLike P>
void tonb::geometry::spatial::HashGrid2d<T>::segment_query(const P &a, const P &b,
    std::vector<std::size_t> &out_ids) const {
    out_ids.clear();
    // 2D Amanatides–Woo grid traversal
    auto A = a; auto B = b;
    auto ka = key_of_point(A);
    auto kb = key_of_point(B);
    int x = ka.first, y = ka.second;
    const int stepX = (B[0] > A[0]) ? 1 : -1;
    const int stepY = (B[1] > A[1]) ? 1 : -1;

    auto cellBorder = [&](int i, double coord) {
        return (i + (stepX>0 ? 1 : 0)) * cell_size_;
    };

    const double dx = B[0]-A[0], dy = B[1]-A[1];
    double invdx = (dx != 0.0) ? 1.0/dx : std::numeric_limits<double>::infinity();
    double invdy = (dy != 0.0) ? 1.0/dy : std::numeric_limits<double>::infinity();

    double nextVx = (x + (stepX>0 ? 1 : 0)) * cell_size_;
    double nextVy = (y + (stepY>0 ? 1 : 0)) * cell_size_;
    double tMaxX = (dx != 0.0) ? (nextVx - A[0]) * invdx : std::numeric_limits<double>::infinity();
    double tMaxY = (dy != 0.0) ? (nextVy - A[1]) * invdy : std::numeric_limits<double>::infinity();
    const double tDeltaX = std::abs(cell_size_ * invdx);
    const double tDeltaY = std::abs(cell_size_ * invdy);

    auto push_bucket = [&](int cx, int cy){
        const auto it = buckets_.find(Key{cx,cy});
        if (it==buckets_.end()) return;
        out_ids.insert(out_ids.end(), it->second.begin(), it->second.end());
    };

    push_bucket(x,y);
    const int maxSteps = static_cast<int>(std::ceil((std::abs(dx)+std::abs(dy))/cell_size_)) + 4;
    for (int i=0; i<maxSteps && (x!=kb.first || y!=kb.second); ++i) {
        if (tMaxX < tMaxY) { x += stepX; tMaxX += tDeltaX; }
        else               { y += stepY; tMaxY += tDeltaY; }
        push_bucket(x,y);
    }
    // Note: caller should deduplicate IDs if needed.
}

template<class T>
bool tonb::geometry::spatial::HashGrid2d<T>::needs_compact(const real dead_ratio_threshold) const {
    const std::size_t n = items_.size();
    if (n == 0) return false;
    // Count alive by scanning buckets once
    std::size_t alive = 0;
    {
        // To avoid O(N) memory here, approximate by summing unique-looking IDs.
        // For accuracy, compact() computes exact alive set anyway.
        // This heuristic keeps needs_compact() cheap.
        for (const auto &val: buckets_ | std::views::values) alive += val.size();
    }
    // alive can overcount duplicates; clamp
    if (alive > n) alive = n;
    const std::size_t dead = n - alive;
    return dead > n * dead_ratio_threshold;
}

template<class T>
void tonb::geometry::spatial::HashGrid2d<T>::compact() {
    const std::size_t oldN = items_.size();
    if (oldN == 0) return;

    // 1) Mark alive IDs by scanning buckets (exact)
    std::vector<unsigned char> alive(oldN, 0);
    std::size_t alive_count = 0;
    for (const auto& [key, vec] : buckets_) {
        for (std::size_t id : vec) {
            if (id < oldN && !alive[id]) {
                alive[id] = 1;
                ++alive_count;
            }
        }
    }
    if (alive_count == oldN) {
        // Nothing to compact
        return;
    }

    // 2) Build remap: old id -> new id (or npos for dead)
    const std::size_t NPOS = std::numeric_limits<std::size_t>::max();
    std::vector<std::size_t> remap(oldN, NPOS);
    std::vector<T> new_items;
    new_items.reserve(alive_count);
    std::vector<Key> new_locate;
    new_locate.reserve(alive_count);

    for (std::size_t i = 0; i < oldN; ++i) {
        if (alive[i]) {
            const std::size_t nid = new_items.size();
            remap[i] = nid;
            new_items.push_back(std::move(items_[i]));
            // Recompute the cell key for safety
            new_locate.push_back(key_of_point(get_point_(new_items.back())));
        }
    }

    // 3) Remap every bucket in place and drop dead IDs
    for (auto& [key, vec] : buckets_) {
        std::size_t w = 0;
        for (std::size_t id : vec) {
            std::size_t nid = id < oldN ? remap[id] : NPOS;
            if (nid != NPOS) vec[w++] = nid;
        }
        vec.resize(w);
    }

    // 4) Swap in new compact storage
    items_.swap(new_items);
    locate_.swap(new_locate);
}

template<class T>
typename tonb::geometry::spatial::HashGrid2d<T>::Key tonb::geometry::spatial::HashGrid2d<T>::key_of(const T &item) const {
    auto p = get_point_(item);
    return Key{
        static_cast<int>(std::floor(p[0] * inv_cell_)),
        static_cast<int>(std::floor(p[1] * inv_cell_))
      };
}

template<class T>
template<tonb::geometry::spatial::PointLike P>
typename tonb::geometry::spatial::HashGrid2d<T>::Key tonb::geometry::spatial::HashGrid2d<T>::key_of_point(
    const P &p) const {
    return Key{
        static_cast<int>(std::floor(p[0] * inv_cell_)),
        static_cast<int>(std::floor(p[1] * inv_cell_))
      };
}



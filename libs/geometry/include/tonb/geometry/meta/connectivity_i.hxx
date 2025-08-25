//
// Created by amir on 8/23/25.
//
#pragma once
template<std::size_t N, class Tag>
void tonb::geometry::meta::Connectivity<N, Tag>::reverse() {
    std::reverse(components_.begin(), components_.end());
}

template<std::size_t N, class Tag>
tonb::geometry::meta::Connectivity<N, Tag> tonb::geometry::meta::Connectivity<N, Tag>::reversed() const noexcept {
    auto r = *this;
    r.reverse();
    return r;
}

template<std::size_t N, class Tag>
std::size_t tonb::geometry::meta::find_max_id(const std::vector<Connectivity<N, Tag>> &components) {
    std::size_t max_v = 0;
    for (const auto& c : components) {
        for (std::size_t i = 0; i < c.size(); i++) {
            if (const auto v = c[i]; v > max_v) {
                max_v = v;
            }
        }
    }
    return max_v;
}

template<std::size_t N, class Tag>
std::vector<tonb::geometry::meta::Connectivity<N, Tag> > tonb::geometry::meta::merge(const std::vector<Connectivity<N, Tag> > &components1, const std::vector<Connectivity<N, Tag> > &components2) {
    const auto max_id = find_max_id(components1);
    std::vector<Connectivity<N, Tag>> merged;
    merged.reserve(components1.size() + components2.size());

    for (const auto& c : components1) {
        merged.emplace_back(c);
    }
    for (const auto& c : components2) {
        auto cc = c;
        for (std::size_t i = 0; i < c.size(); i++) {
            cc[i] += max_id;
        }
        merged.emplace_back(cc);
    }
    return merged;
}

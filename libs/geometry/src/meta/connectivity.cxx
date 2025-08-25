//
// Created by amir on 8/23/25.
//
#include <tonb/geometry/meta/connectivity.hxx>

std::vector<tonb::geometry::meta::detail::Edge> tonb::geometry::meta::detail::make_edges(const std::size_t n) {
    std::vector<Edge> edges(n);
    size_t k = 0;
    for (auto&e : edges) {
        e[0] = k * 2 + 1;
        e[1] = k * 2 + 2;
        ++k;
    }
    return edges;
}

std::vector<tonb::geometry::meta::detail::Edge> tonb::geometry::meta::detail::make_chain_edges(std::size_t n,
    const bool close_option) {
    std::vector<Edge> edges(n);
    size_t k = 0;
    for (auto&e : edges) {
        e[0] = k + 1;
        e[1] = k + 2;
        ++k;
    }
    if (close_option) {
        edges.at(n - 1)[1] = 1;
    }
    return edges;
}

tonb::geometry::meta::detail::Tri tonb::geometry::meta::promote(const detail::Edge & edge) {
    return detail::Tri{{edge[0], edge[1], edge[0]}};
}

tonb::geometry::meta::detail::Quad tonb::geometry::meta::promote(const detail::Tri & tri) {
    return detail::Quad{{tri[0], tri[1], tri[2], tri[0]}};
}

tonb::geometry::meta::detail::Hexa6 tonb::geometry::meta::promote(const detail::Quad & quad) {
    return detail::Hexa6({quad[0], quad[1], quad[2], quad[3], quad[3], quad[3]});
}

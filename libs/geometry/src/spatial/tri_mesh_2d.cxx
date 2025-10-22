//
// Created by amir on 03/09/2025.
//
#include <tonb/geometry/spatial/tri_mesh_2d.hxx>

#include <map>

namespace tonb::geometry::spatial {
    void TriMesh2d::build_adjacency() {
        neighbors.assign(F.size(), std::array<index_t, 3>{-1, -1, -1});
        v2f.assign(V.size(), -1);

        struct EdgeKey {
            index_t a, b;
            bool operator<(const EdgeKey& o) const {
                return (a < o.a) || (a == o.a && b < o.b);
            }
        };
        auto key = [](const index_t u, const index_t v) -> EdgeKey {
            return {std::min(u, v), std::max(u, v)};
        };

        std::map<EdgeKey, std::pair<index_t, index_t>> owner;
        for (index_t f = 0; f < static_cast<index_t>(F.size()); ++f) {
            const auto [i, j, k] = F[f];
            if (v2f[i] < 0) v2f[i] = f;
            if (v2f[j] < 0) v2f[j] = f;
            if (v2f[k] < 0) v2f[k] = f;

            const index_t eV[3][2] = {{i, j}, {j, k}, {k, i}};
            for (index_t e = 0; e < 3; ++e) {
                EdgeKey ek = key(eV[e][0], eV[e][1]);
                if (auto it = owner.find(ek); it == owner.end()) {
                    owner[ek] = {f, e};
                } else {
                    const index_t f2 = it->second.first, e2 = it->second.second;
                    neighbors[f][e]   = f2;
                    neighbors[f2][e2] = f;
                }
            }
        }
    }
}
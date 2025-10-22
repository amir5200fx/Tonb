//
// Created by amir on 03/09/2025.
//
#include <tonb/geometry/spatial/point_locator_2d.hxx>

#include <tonb/geometry/spatial/uniform_grid_2d.hxx>
#include <tonb/geometry/meta/box_2d.hxx>
#include <tonb/geometry/vec_2d.hxx>
#include <tonb/geometry/spatial/tri_mesh_2d.hxx>
#include <tonb/geometry/tools.hxx>

namespace tonb::geometry::spatial {

    PointLocator2d::PointLocator2d(const TriMesh2d &mesh, int grid_cells_per_axis)
        : M_(mesh) {
        // Compute domain AABB
        real minx = std::numeric_limits<real>::max();
        real miny = std::numeric_limits<real>::max();
        real maxx = std::numeric_limits<real>::min();
        real maxy = std::numeric_limits<real>::min();
        for (const auto& v: M_.V) {
            minx = std::min(minx, v[0]);
            miny = std::min(miny, v[1]);
            maxx = std::max(maxx, v[0]);
            maxy = std::max(maxy, v[1]);
        }

        meta::Box2d domain{{minx, miny}, {maxx, maxy}};

        // Choose grid resolution
        int base;
        if (grid_cells_per_axis > 0) {
            base = grid_cells_per_axis;
        } else {
            const auto nF = static_cast<int>(M_.F.size());
            base = std::clamp(static_cast<int>(std::sqrt(std::max(1, nF))), 8, 512);
        }

        grid_.build(domain, base, base);

        // Insert triangle AABBs
        for (index_t f = 0; f < static_cast<index_t>(M_.F.size()); ++f) {
            const auto [i, j, k]= M_.F[static_cast<size_t>(f)];
            const real ax = M_.V[i][0], ay = M_.V[i][1];
            const real bx = M_.V[j][0], by = M_.V[j][1];
            const real cx = M_.V[k][0], cy = M_.V[k][1];

            const real minx = std::min({ax, bx, cx});
            const real miny = std::min({ay, by, cy});
            const real maxx = std::max({ax, bx, cx});
            const real maxy = std::max({ay, by, cy});

            grid_.insert(static_cast<int>(f), {{minx, miny}, {maxx, maxy}});
        }
    }

    PointLocator2d::Result PointLocator2d::locate(real px, real py, index_t seed_face, index_t max_hops) const {
        Result res;

        // Seed face selection
        index_t f = seed_face;
        if (f < 0 || f >= static_cast<index_t>(M_.F.size())) {
            const auto& bucket = grid_.query_cell(Vec2d{px, py});
            if (!bucket.empty()) {
                real best = std::numeric_limits<real>::infinity();
                for (int cf : bucket) {
                    const auto [i, j, k] = M_.F[static_cast<size_t>(cf)];
                    const real gx = (M_.V[i][0] + M_.V[j][0] + M_.V[k][0]) * (1.0 / 3.0);
                    const real gy = (M_.V[i][1] + M_.V[j][1] + M_.V[k][1]) * (1.0 / 3.0);
                    const real dx = gx - px, dy = gy - py;
                    const real d2 = dx*dx + dy*dy;
                    if (d2 < best) { best = d2; f = static_cast<index_t>(cf); }
                }
            } else {
                // global fallback
                real best = std::numeric_limits<real>::infinity();
                for (index_t cf = 0; cf < static_cast<index_t>(M_.F.size()); ++cf) {
                    const auto [i, j, k] = M_.F[static_cast<size_t>(cf)];
                    const real gx = (M_.V[i][0] + M_.V[j][0] + M_.V[k][0]) * (1.0 / 3.0);
                    const real gy = (M_.V[i][1] + M_.V[j][1] + M_.V[k][1]) * (1.0 / 3.0);
                    const real dx = gx - px, dy = gy - py;
                    const real d2 = dx*dx + dy*dy;
                    if (d2 < best) { best = d2; f = cf; }
                }
            }
        }

        if (f < 0) return res; // empty mesh guard

        // Walk until inside or boundary
        for (index_t hop = 0; hop < max_hops; ++hop) {
            const auto [i, j, k] = M_.F[static_cast<size_t>(f)];
            const real ax = M_.V[i][0], ay = M_.V[i][1];
            const real bx = M_.V[j][0], by = M_.V[j][1];
            const real cx = M_.V[k][0], cy = M_.V[k][1];

            const auto w = Tools::barycentric(px, py, ax, ay, bx, by, cx, cy);
            if (Tools::inside_bary(w)) { res.triangle_id = f; res.bary = w; return res; }

            // Step across the edge opposite the most negative weight
            index_t neg = 0; real mn = w[0];
            if (w[1] < mn) { mn = w[1]; neg = 1; }
            if (w[2] < mn) { mn = w[2]; neg = 2; }

            // neighbours[f] is ordered by edges: 0:(i,j), 1:(j,k), 2:(k,i)
            // map vertex -> opposite edge
            static const index_t opp_edge[3] = {
                /* w0 -> cross (j,k) */ 1,
                /* w1 -> cross (k,i) */ 2,
                /* w2 -> cross (i,j) */ 0
            };

            const index_t e  = opp_edge[neg];
            const index_t fn = M_.neighbors.empty() ? -1 : M_.neighbors[static_cast<size_t>(f)][static_cast<size_t>(e)];
            if (fn < 0) {
                // boundary: return clamped barycentrics on current face
                res.triangle_id = f;
                res.bary = Tools::clamp_bary(w);
                return res;
            }
            f = fn;
        }

        // Safety exit: clamp on last face
        {
            const auto [i, j, k] = M_.F[static_cast<size_t>(f)];
            const auto w = Tools::barycentric(px, py, M_.V[i][0], M_.V[i][1],
                                               M_.V[j][0], M_.V[j][1],
                                               M_.V[k][0], M_.V[k][1]);
            res.triangle_id = f;
            res.bary = Tools::clamp_bary(w);
            return res;
        }
    }


}

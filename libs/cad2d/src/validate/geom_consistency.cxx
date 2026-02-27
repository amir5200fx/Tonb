//
// Created by amir on 1/25/26.
//
#include <tonb/cad2d/validate/geom_consistency.hxx>

#include <tonb/cad2d/point.hxx>

#include <cmath>
#include <unordered_map>

namespace tonb::cad2d::validate {
    namespace {

        bool finite(const real x) noexcept {
            return std::isfinite(x) != 0;
        }

        real dist(const Point& a, const Point& b) noexcept {
            return geometry::distance(a, b);
        }

        real endpoint_to(const topo::Tolerance& cfg_override, const real edge_tol, const real vtx_tol) noexcept {
            const real t0 = cfg_override.linear();
            const real t1 = edge_tol >= 0.0 ? edge_tol : 0.0;
            const real t2 = vtx_tol >= 0.0 ? vtx_tol : 0.0;
            return std::max(t0, std::max(t1, t2));
        }

        void add_issue(GeomReport& out, const GeomIssueCode code, const topo::Id edge_id, const topo::Id vertex_id, const real measured, const real allowed, const char* msg) {
            GeomIssue i;
            i.code = code;
            i.edge = edge_id;
            i.vertex = vertex_id;
            i.measured = measured;
            i.allowed = allowed;
            i.message = msg;
            out.add(i);
        }

        std::optional<std::pair<Point, Point>> eval_oriented_endpoints(const topo::HalfEdge& e, const ICurveEval2d& curves) {
            const auto[u0, u1] = e.param_range();

            const auto p_u0 = curves.eval(e.curve_id(), u0);
            const auto p_u1 = curves.eval(e.curve_id(), u1);
            if (!p_u0 || !p_u1) return std::nullopt;

            Point a = *p_u0;
            Point b = *p_u1;

            if (e.orientation() == topo::Orientation::reversed) {
                std::swap(a, b);
            }
            return std::make_pair(a, b);
        }
    }
}
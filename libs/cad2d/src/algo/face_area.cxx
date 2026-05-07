//
// Created by amir on 5/7/26.
//
/**
 * @file face_area.cxx
 * @brief Implements polygonal face-area and orientation utilities for cad2d.
 */
#include <tonb/cad2d/algo/face_area.hxx>

#include <tonb/cad2d/topo/face.hxx>
#include <tonb/cad2d/topo/wire.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/geom/curve_ops.hxx>
#include <tonb/cad2d/point.hxx>

#include <cmath>
#include <sstream>
#include <vector>

namespace tonb::cad2d::algo {
    namespace {

        struct XY {
            real x = 0.0;
            real y = 0.0;
        };

        std::string wire_ctx(const std::shared_ptr<topo::Wire>& wire) {
            if (!wire) {
                return "FaceArea";
            }
            return "FaceArea (wire id=" + std::to_string(wire->id()) + ")";
        }

        std::string face_ctx(const std::shared_ptr<topo::Face>& face) {
            if (!face) {
                return "FaceArea";
            }
            return "FaceArea (face id=" + std::to_string(face->id()) + ")";
        }

        bool finite(const real x) noexcept {
            return std::isfinite(x) != 0;
        }

        XY to_xy(const Point& p) {
            return XY{p.x(), p.y()};
        }

        real cross(const XY& a, const XY& b) noexcept {
            return a.x * b.y - a.y * b.x;
        }

        real norm(const XY& v) noexcept {
            return std::sqrt(v.x * v.x + v.y * v.y);
        }

        real distance(const XY& a, const XY& b) noexcept {
            return norm(XY{b.x - a.x, b.y - a.y});
        }

        XY midpoint(const XY& a, const XY& b) noexcept {
            return XY{0.5 * (a.x + b.x), 0.5 * (a.y + b.y)};
        }

        topo::Result<void> ensure_segment_like_span(const std::shared_ptr<topo::HalfEdge>& edge,
                                                    const Curve& curve,
                                                    const FaceAreaOptions& options) {
            if (!options.require_linear_geometry) {
                return {};
            }

            const real u0 = edge->u0();
            const real u1 = edge->u1();
            const real um = 0.5 * (u0 + u1);

            const XY p0 = to_xy(geom::value(curve, u0));
            const XY p1 = to_xy(geom::value(curve, u1));
            const XY pm = to_xy(geom::value(curve, um));
            const XY chord_mid = midpoint(p0, p1);

            const real dev = distance(pm, chord_mid);
            if (dev > options.linearity_tolerance) {
                std::ostringstream oss;
                oss << "FaceArea: half-edge id=" << edge->id()
                    << " is not segment-like within tolerance"
                    << " (midpoint deviation=" << dev
                    << ", tolerance=" << options.linearity_tolerance << ")";
                return topo::Result<void>(topo::ResultError{
                    oss.str(),
                    topo::ErrorCode::geometry_error
                });
            }

            return {};
        }

        topo::Result<std::pair<XY, XY>> directed_edge_points(const std::shared_ptr<topo::HalfEdge>& edge,
                                                             const geom::CurveStore& curves,
                                                             const FaceAreaOptions& options) {
            if (!edge) {
                return topo::Result<std::pair<XY, XY>>(topo::ResultError{
                    "FaceArea: wire contains a null or expired half-edge",
                    topo::ErrorCode::topology_error
                });
            }

            const auto cid = edge->curve_id();
            if (cid == 0) {
                return topo::Result<std::pair<XY, XY>>(topo::ResultError{
                    "FaceArea: half-edge stores invalid curve id 0",
                    topo::ErrorCode::geometry_error
                });
            }

            if (!curves.contains(cid)) {
                return topo::Result<std::pair<XY, XY>>(topo::ResultError{
                    "FaceArea: referenced curve id is not present in CurveStore",
                    topo::ErrorCode::geometry_error
                });
            }

            const auto& curve = curves.get(cid);

            const real u0 = edge->u0();
            const real u1 = edge->u1();
            if (!finite(u0) || !finite(u1)) {
                return topo::Result<std::pair<XY, XY>>(topo::ResultError{
                    "FaceArea: half-edge parameters are not finite",
                    topo::ErrorCode::geometry_error
                });
            }

            if (const auto linear = ensure_segment_like_span(edge, curve, options); !linear) {
                return topo::Result<std::pair<XY, XY>>(linear.error());
            }

            return topo::Result<std::pair<XY, XY>>(
                std::make_pair(to_xy(geom::value(curve, u0)), to_xy(geom::value(curve, u1))));
        }

        topo::Result<real> wire_area_impl(const std::shared_ptr<topo::Wire>& wire,
                                          const geom::CurveStore& curves,
                                          const FaceAreaOptions& options) {
            if (!wire) {
                return topo::Result<real>(topo::ResultError{
                    "FaceArea: wire pointer is null",
                    topo::ErrorCode::invalid_input
                });
            }

            if (wire->empty()) {
                return topo::Result<real>(topo::ResultError{
                    wire_ctx(wire) + ": wire boundary is empty",
                    topo::ErrorCode::invalid_input
                });
            }

            const auto edges = wire->edges_locked();
            XY first_start{};
            XY prev_end{};
            bool have_first = false;
            real twice_area = 0.0;

            for (std::size_t i = 0; i < edges.size(); ++i) {
                const auto re = directed_edge_points(edges[i], curves, options);
                if (!re) {
                    return topo::Result<real>(topo::ResultError{
                        wire_ctx(wire) + ": failed on boundary edge index " + std::to_string(i) +
                        " (" + re.error().message + ")",
                        re.error().code
                    });
                }

                const XY p0 = re.value().first;
                const XY p1 = re.value().second;

                if (!have_first) {
                    first_start = p0;
                    have_first = true;
                } else {
                    if (distance(prev_end, p0) > options.linearity_tolerance) {
                        std::ostringstream oss;
                        oss << wire_ctx(wire)
                            << ": wire is not continuous in geometric traversal order"
                            << " (edge index=" << i
                            << ", gap=" << distance(prev_end, p0)
                            << ", tolerance=" << options.linearity_tolerance << ")";
                        return topo::Result<real>(topo::ResultError{
                            oss.str(),
                            topo::ErrorCode::validation_failed
                        });
                    }
                }

                twice_area += cross(p0, p1);
                prev_end = p1;
            }

            if (distance(prev_end, first_start) > options.linearity_tolerance) {
                std::ostringstream oss;
                oss << wire_ctx(wire)
                    << ": wire is not geometrically closed"
                    << " (closure gap=" << distance(prev_end, first_start)
                    << ", tolerance=" << options.linearity_tolerance << ")";
                return topo::Result<real>(topo::ResultError{
                    oss.str(),
                    topo::ErrorCode::validation_failed
                });
            }

            return topo::Result<real>(0.5 * twice_area);
        }

        topo::Result<bool> normalize_wire_if_needed(const std::shared_ptr<topo::Wire>& wire,
                                                    const LoopOrientation expected,
                                                    const geom::CurveStore& curves,
                                                    const FaceAreaOptions& options) {
            const auto rc = classify_wire_orientation(wire, curves, options);
            if (!rc) {
                return topo::Result<bool>(rc.error());
            }

            const auto current = rc.value();
            if (current == LoopOrientation::collinear) {
                return topo::Result<bool>(topo::ResultError{
                    wire_ctx(wire) + ": cannot normalize a collinear or zero-area loop",
                    topo::ErrorCode::degenerate
                });
            }

            if (current == expected) {
                return topo::Result<bool>(false);
            }

            return reverse_wire_using_twins(wire, options);
        }
    }

    topo::Result<real> signed_area_of_wire_polygon(const std::shared_ptr<topo::Wire>& wire,
                                                   const geom::CurveStore& curves,
                                                   const FaceAreaOptions& options) {
        return wire_area_impl(wire, curves, options);
    }

    topo::Result<LoopOrientation> classify_wire_orientation(const std::shared_ptr<topo::Wire>& wire,
                                                            const geom::CurveStore& curves,
                                                            const FaceAreaOptions& options) {
        const auto ra = wire_area_impl(wire, curves, options);
        if (!ra) {
            return topo::Result<LoopOrientation>(ra.error());
        }

        const real a = ra.value();
        if (std::abs(a) <= options.area_epsilon) {
            return topo::Result<LoopOrientation>(LoopOrientation::collinear);
        }

        return topo::Result<LoopOrientation>(a > 0.0 ? LoopOrientation::ccw : LoopOrientation::cw);
    }

    topo::Result<real> signed_area_of_face_polygon(const std::shared_ptr<topo::Face>& face,
                                                   const geom::CurveStore& curves,
                                                   const FaceAreaOptions& options) {
        if (!face) {
            return topo::Result<real>(topo::ResultError{
                "FaceArea: face pointer is null",
                topo::ErrorCode::invalid_input
            });
        }

        const auto outer = face->outer();
        if (!outer) {
            return topo::Result<real>(topo::ResultError{
                face_ctx(face) + ": outer wire is null or expired",
                topo::ErrorCode::topology_error
            });
        }

        real total = 0.0;

        const auto ro = signed_area_of_wire_polygon(outer, curves, options);
        if (!ro) {
            return topo::Result<real>(topo::ResultError{
                face_ctx(face) + ": failed on outer wire (" + ro.error().message + ")",
                ro.error().code
            });
        }
        total += ro.value();

        const auto holes = face->holes_locked();
        for (std::size_t i = 0; i < holes.size(); ++i) {
            if (!holes[i]) {
                return topo::Result<real>(topo::ResultError{
                    face_ctx(face) + ": hole wire is null or expired at index " + std::to_string(i),
                    topo::ErrorCode::topology_error
                });
            }

            const auto rh = signed_area_of_wire_polygon(holes[i], curves, options);
            if (!rh) {
                return topo::Result<real>(topo::ResultError{
                    face_ctx(face) + ": failed on hole wire index " + std::to_string(i) +
                    " (" + rh.error().message + ")",
                    rh.error().code
                });
            }
            total += rh.value();
        }

        return topo::Result<real>(total);
    }

    topo::Result<bool> face_has_standard_orientation(const std::shared_ptr<topo::Face>& face,
                                                     const geom::CurveStore& curves,
                                                     const FaceAreaOptions& options) {
        if (!face) {
            return topo::Result<bool>(topo::ResultError{
                "FaceArea: face pointer is null",
                topo::ErrorCode::invalid_input
            });
        }

        const auto outer = face->outer();
        if (!outer) {
            return topo::Result<bool>(topo::ResultError{
                face_ctx(face) + ": outer wire is null or expired",
                topo::ErrorCode::topology_error
            });
        }

        const auto ro = classify_wire_orientation(outer, curves, options);
        if (!ro) {
            return topo::Result<bool>(topo::ResultError{
                face_ctx(face) + ": failed to classify outer wire (" + ro.error().message + ")",
                ro.error().code
            });
        }

        if (ro.value() != LoopOrientation::ccw) {
            return topo::Result<bool>(false);
        }

        const auto holes = face->holes_locked();
        for (std::size_t i = 0; i < holes.size(); ++i) {
            if (!holes[i]) {
                return topo::Result<bool>(topo::ResultError{
                    face_ctx(face) + ": hole wire is null or expired at index " + std::to_string(i),
                    topo::ErrorCode::topology_error
                });
            }

            const auto rh = classify_wire_orientation(holes[i], curves, options);
            if (!rh) {
                return topo::Result<bool>(topo::ResultError{
                    face_ctx(face) + ": failed to classify hole wire index " + std::to_string(i) +
                    " (" + rh.error().message + ")",
                    rh.error().code
                });
            }

            if (rh.value() != LoopOrientation::cw) {
                return topo::Result<bool>(false);
            }
        }

        return topo::Result<bool>(true);
    }

    topo::Result<bool> reverse_wire_using_twins(const std::shared_ptr<topo::Wire>& wire,
                                                const FaceAreaOptions& options) {
        if (!wire) {
            return topo::Result<bool>(topo::ResultError{
                "FaceArea: wire pointer is null",
                topo::ErrorCode::invalid_input
            });
        }

        const auto edges = wire->edges_locked();
        if (edges.empty()) {
            return topo::Result<bool>(topo::ResultError{
                wire_ctx(wire) + ": wire boundary is empty",
                topo::ErrorCode::invalid_input
            });
        }

        std::vector<std::shared_ptr<topo::HalfEdge>> reversed;
        reversed.reserve(edges.size());

        for (auto it = edges.rbegin(); it != edges.rend(); ++it) {
            if (!(*it)) {
                return topo::Result<bool>(topo::ResultError{
                    wire_ctx(wire) + ": wire contains a null or expired half-edge",
                    topo::ErrorCode::topology_error
                });
            }

            const auto twin = (*it)->twin();
            if (!twin) {
                return topo::Result<bool>(topo::ResultError{
                    wire_ctx(wire) + ": cannot reverse wire because half-edge id=" +
                    std::to_string((*it)->id()) + " has no twin",
                    topo::ErrorCode::topology_error
                });
            }

            reversed.push_back(twin);
        }

        std::vector<std::weak_ptr<topo::HalfEdge>> boundary;
        boundary.reserve(reversed.size());
        for (const auto& e : reversed) {
            boundary.emplace_back(e);
        }
        wire->set_boundary(std::move(boundary));

        if (options.update_next_prev_on_normalize) {
            const std::size_t n = reversed.size();
            for (std::size_t i = 0; i < n; ++i) {
                const auto& curr = reversed[i];
                const auto& next = reversed[(i + 1) % n];
                const auto& prev = reversed[(i + n - 1) % n];
                curr->set_next(next);
                curr->set_prev(prev);
            }
        }

        return topo::Result<bool>(true);
    }

    topo::Result<bool> normalize_face_polygon_orientations(const std::shared_ptr<topo::Face>& face,
                                                           const geom::CurveStore& curves,
                                                           const FaceAreaOptions& options) {
        if (!face) {
            return topo::Result<bool>(topo::ResultError{
                "FaceArea: face pointer is null",
                topo::ErrorCode::invalid_input
            });
        }

        bool changed = false;

        const auto outer = face->outer();
        if (!outer) {
            return topo::Result<bool>(topo::ResultError{
                face_ctx(face) + ": outer wire is null or expired",
                topo::ErrorCode::topology_error
            });
        }

        const auto ro = normalize_wire_if_needed(outer, LoopOrientation::ccw, curves, options);
        if (!ro) {
            return topo::Result<bool>(topo::ResultError{
                face_ctx(face) + ": failed to normalize outer wire (" + ro.error().message + ")",
                ro.error().code
            });
        }
        changed = changed || ro.value();

        const auto holes = face->holes_locked();
        for (std::size_t i = 0; i < holes.size(); ++i) {
            if (!holes[i]) {
                return topo::Result<bool>(topo::ResultError{
                    face_ctx(face) + ": hole wire is null or expired at index " + std::to_string(i),
                    topo::ErrorCode::topology_error
                });
            }

            const auto rh = normalize_wire_if_needed(holes[i], LoopOrientation::cw, curves, options);
            if (!rh) {
                return topo::Result<bool>(topo::ResultError{
                    face_ctx(face) + ": failed to normalize hole wire index " + std::to_string(i) +
                    " (" + rh.error().message + ")",
                    rh.error().code
                });
            }
            changed = changed || rh.value();
        }

        return topo::Result<bool>(changed);
    }
}

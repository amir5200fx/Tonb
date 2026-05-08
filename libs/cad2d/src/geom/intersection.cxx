//
// Created by amir on 5/7/26.
//
/**
 * @file intersection.cxx
 * @brief Implements bounded 2D curve-span intersection utilities.
 */
#include <tonb/config.hxx>
#include <tonb/cad2d/geom/intersection.hxx>
#include <tonb/cad2d/geom/curve_ops.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)
#include <tonb/geometry/occt/core/curve_2d_helpers.hxx>

#include <Geom2dAdaptor_Curve.hxx>
#include <GeomAbs_CurveType.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Pnt2d.hxx>
#include <ElCLib.hxx>
#include <Standard_Failure.hxx>
#endif

#include <algorithm>
#include <cmath>
#include <exception>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace tonb::cad2d::geom {
    namespace {

        /**
         * @brief Lightweight Cartesian helper used internally by the intersection code.
         */
        struct XY {
            real x = 0.0;
            real y = 0.0;
        };

        /**
         * @brief Parameter span helper preserving the original input direction.
         */
        struct Span {
            real a = 0.0;
            real b = 0.0;
        };

        /**
         * @brief Internal bounded-span geometry classification used for dispatch.
         */
        enum class SpanKind : std::uint8_t {
            line_like = 0,
            circle_like,
            unsupported
        };

        /**
         * @brief Circle data extracted from a circular span.
         */
        struct CircleData {
            XY center{};
            real radius = 0.0;
        };

        /**
         * @brief Convert public Point to internal XY.
         */
        XY to_xy(const Point& p) {
            return XY{p.x(), p.y()};
        }

        /**
         * @brief Convert internal XY to public Point.
         */
        Point to_point(const XY& p) {
            return Point{p.x, p.y};
        }

        XY operator+(const XY& a, const XY& b) noexcept {
            return XY{a.x + b.x, a.y + b.y};
        }

        XY operator-(const XY& a, const XY& b) noexcept {
            return XY{a.x - b.x, a.y - b.y};
        }

        XY operator*(const real s, const XY& a) noexcept {
            return XY{s * a.x, s * a.y};
        }

        real dot(const XY& a, const XY& b) noexcept {
            return a.x * b.x + a.y * b.y;
        }

        real cross(const XY& a, const XY& b) noexcept {
            return a.x * b.y - a.y * b.x;
        }

        real norm2(const XY& a) noexcept {
            return dot(a, a);
        }

        real norm(const XY& a) noexcept {
            return std::sqrt(norm2(a));
        }

        bool approx_zero(const real x, const real tol) noexcept {
            return std::abs(x) <= tol;
        }

        bool in_unit_interval(const real t, const real tol) noexcept {
            return t >= -tol && t <= real(1.0) + tol;
        }

        real lerp_param(const Span& s, const real t) noexcept {
            return s.a + t * (s.b - s.a);
        }

        bool span_contains_nonperiodic(const Span& s, const real u, const real tol) noexcept {
            const real lo = std::min(s.a, s.b) - tol;
            const real hi = std::max(s.a, s.b) + tol;
            return u >= lo && u <= hi;
        }

        /**
         * @brief Match a periodic parameter value to the given bounded span.
         *
         * This is used for circle parameters, where the same geometric point may
         * be represented by infinitely many parameter values differing by a full
         * angular period.
         */
        std::optional<real> match_periodic_param(
            const Span& s,
            const real u,
            const IntersectionOptions& options) {

            const real period = options.angular_period;
            real best = 0.0;
            real best_dist = 0.0;
            bool found = false;

            for (int k = -2; k <= 2; ++k) {
                const real cand = u + real(k) * period;
                if (!span_contains_nonperiodic(s, cand, options.param_tolerance)) {
                    continue;
                }

                const real mid = real(0.5) * (s.a + s.b);
                const real d = std::abs(cand - mid);
                if (!found || d < best_dist) {
                    found = true;
                    best = cand;
                    best_dist = d;
                }
            }

            if (!found) {
                return std::nullopt;
            }
            return best;
        }

        /**
         * @brief Create a consistent unsupported-operation diagnostic.
         */
        std::string unsupported_message(const char* lhs, const char* rhs) {
            return std::string("CurveIntersection: unsupported bounded-span intersection between ")
                + lhs + " and " + rhs;
        }

        /**
         * @brief Append one isolated point result item.
         */
        void append_point(
            IntersectionResult& out,
            const Point& point,
            const real u_on_first,
            const real u_on_second,
            const IntersectionPointKind kind) {

            out.items.emplace_back(IntersectionPoint{
                point,
                u_on_first,
                u_on_second,
                kind
            });
        }

        /**
         * @brief Append one overlap result item.
         */
        void append_overlap(
            IntersectionResult& out,
            const Point& first_point,
            const Point& last_point,
            const real first_u0,
            const real first_u1,
            const real second_u0,
            const real second_u1) {

            out.items.emplace_back(IntersectionOverlap{
                first_point,
                last_point,
                first_u0,
                first_u1,
                second_u0,
                second_u1
            });
        }

#if defined(TONB_HAS_OCCT_ADAPTERS)
        /**
         * @brief Classify a bounded curve span for dispatch.
         */
        SpanKind classify_span_kind(const Curve& c, const Span& s) {
            const auto handle = geometry::occt::core::occt_curve_2d_access::get(c);
            Geom2dAdaptor_Curve adaptor(handle, std::min(s.a, s.b), std::max(s.a, s.b));

            switch (adaptor.GetType()) {
                case GeomAbs_Line:
                    return SpanKind::line_like;
                case GeomAbs_Circle:
                    return SpanKind::circle_like;
                default:
                    return SpanKind::unsupported;
            }
        }

        /**
         * @brief Extract circle geometry from a circular span.
         */
        CircleData circle_data(const Curve& c, const Span& s) {
            const auto handle = geometry::occt::core::occt_curve_2d_access::get(c);
            Geom2dAdaptor_Curve adaptor(handle, std::min(s.a, s.b), std::max(s.a, s.b));
            const gp_Circ2d circ = adaptor.Circle();

            return CircleData{
                XY{circ.Location().X(), circ.Location().Y()},
                circ.Radius()
            };
        }

        /**
         * @brief Compute a circle parameter corresponding to a point and match it
         *        back into the bounded periodic span.
         */
        std::optional<real> circle_parameter_in_span(
            const Curve& c,
            const Span& s,
            const XY& p,
            const IntersectionOptions& options) {

            const auto handle = geometry::occt::core::occt_curve_2d_access::get(c);
            Geom2dAdaptor_Curve adaptor(handle, std::min(s.a, s.b), std::max(s.a, s.b));
            const gp_Circ2d circ = adaptor.Circle();
            const real u = ElCLib::Parameter(circ, gp_Pnt2d(p.x, p.y));
            return match_periodic_param(s, u, options);
        }
#else
        SpanKind classify_span_kind(const Curve&, const Span&) {
            return SpanKind::unsupported;
        }

        CircleData circle_data(const Curve&, const Span&) {
            return CircleData{};
        }

        std::optional<real> circle_parameter_in_span(
            const Curve&,
            const Span&,
            const XY&,
            const IntersectionOptions&) {

            return std::nullopt;
        }
#endif

        /**
         * @brief Evaluate the geometric endpoints of a line-like span.
         */
        topo::Result<std::pair<XY, XY>> line_span_points(const Curve& c, const Span& s) {
            return topo::Result<std::pair<XY, XY>>(std::make_pair(
                to_xy(value(c, s.a)),
                to_xy(value(c, s.b))
            ));
        }

        /**
         * @brief Intersect two line-like bounded spans deterministically.
         *
         * This path is implemented manually and does not depend on the geometry
         * kernel for the core segment-segment logic.
         */
        topo::Result<IntersectionResult> intersect_segment_segment(
            const Curve& first,
            const Span& sa,
            const Curve& second,
            const Span& sb,
            const IntersectionOptions& options) {

            IntersectionResult out{};

            const auto ra = line_span_points(first, sa);
            const auto rb = line_span_points(second, sb);
            if (!ra) {
                return topo::Result<IntersectionResult>(ra.error());
            }
            if (!rb) {
                return topo::Result<IntersectionResult>(rb.error());
            }

            const XY p = ra.value().first;
            const XY p1 = ra.value().second;
            const XY q = rb.value().first;
            const XY q1 = rb.value().second;

            const XY r = p1 - p;
            const XY s = q1 - q;
            const XY qp = q - p;

            const real rxs = cross(r, s);
            const real qpxr = cross(qp, r);
            const real tol = options.point_tolerance;

            if (!approx_zero(rxs, tol)) {
                const real t = cross(qp, s) / rxs;
                const real u = cross(qp, r) / rxs;

                if (in_unit_interval(t, options.param_tolerance) &&
                    in_unit_interval(u, options.param_tolerance)) {
                    const XY ip = p + t * r;
                    append_point(
                        out,
                        to_point(ip),
                        lerp_param(sa, t),
                        lerp_param(sb, u),
                        IntersectionPointKind::simple);
                }

                return topo::Result<IntersectionResult>(out);
            }

            if (!approx_zero(qpxr, tol)) {
                return topo::Result<IntersectionResult>(out);
            }

            const real rr = norm2(r);
            const real ss = norm2(s);
            if (approx_zero(rr, tol) || approx_zero(ss, tol)) {
                return topo::Result<IntersectionResult>(topo::ResultError{
                    "CurveIntersection: degenerate segment span encountered",
                    topo::ErrorCode::degenerate
                });
            }

            const real t0 = dot(q - p, r) / rr;
            const real t1 = dot(q1 - p, r) / rr;
            const real ta = std::max(real(0.0), std::min(t0, t1));
            const real tb = std::min(real(1.0), std::max(t0, t1));

            if (tb < ta - options.param_tolerance) {
                return topo::Result<IntersectionResult>(out);
            }

            if (std::abs(tb - ta) <= options.param_tolerance) {
                const XY ip = p + ta * r;
                const real ub = dot(ip - q, s) / ss;

                append_point(
                    out,
                    to_point(ip),
                    lerp_param(sa, ta),
                    lerp_param(sb, ub),
                    IntersectionPointKind::simple);

                return topo::Result<IntersectionResult>(out);
            }

            const XY ia = p + ta * r;
            const XY ib = p + tb * r;
            const real ua0 = lerp_param(sa, ta);
            const real ua1 = lerp_param(sa, tb);
            const real vb0 = lerp_param(sb, dot(ia - q, s) / ss);
            const real vb1 = lerp_param(sb, dot(ib - q, s) / ss);

            append_overlap(
                out,
                to_point(ia),
                to_point(ib),
                ua0,
                ua1,
                vb0,
                vb1);

            return topo::Result<IntersectionResult>(out);
        }

        /**
         * @brief Intersect one line-like bounded span with one circular span.
         */
        topo::Result<IntersectionResult> intersect_segment_circle(
            const Curve& line_curve,
            const Span& line_span,
            const Curve& circle_curve,
            const Span& circle_span,
            const IntersectionOptions& options) {

            IntersectionResult out{};

            const auto rline = line_span_points(line_curve, line_span);
            if (!rline) {
                return topo::Result<IntersectionResult>(rline.error());
            }

            const XY p0 = rline.value().first;
            const XY p1 = rline.value().second;
            const XY d = p1 - p0;
            const CircleData cd = circle_data(circle_curve, circle_span);
            const XY f = p0 - cd.center;

            const real A = dot(d, d);
            const real B = real(2.0) * dot(f, d);
            const real C = dot(f, f) - cd.radius * cd.radius;

            const real disc = B * B - real(4.0) * A * C;
            const real tol = options.point_tolerance;

            if (disc < -tol) {
                return topo::Result<IntersectionResult>(out);
            }

            const auto emit_point = [&](const real t, const bool tangent) {
                if (!in_unit_interval(t, options.param_tolerance)) {
                    return;
                }

                const XY ip = p0 + t * d;
                const auto uc = circle_parameter_in_span(circle_curve, circle_span, ip, options);
                if (!uc.has_value()) {
                    return;
                }

                append_point(
                    out,
                    to_point(ip),
                    lerp_param(line_span, t),
                    *uc,
                    tangent ? IntersectionPointKind::tangent
                            : IntersectionPointKind::simple);
            };

            if (std::abs(disc) <= tol) {
                const real t = -B / (real(2.0) * A);
                emit_point(t, true);
            } else {
                const real sdisc = std::sqrt(std::max(real(0.0), disc));
                const real t0 = (-B - sdisc) / (real(2.0) * A);
                const real t1 = (-B + sdisc) / (real(2.0) * A);

                emit_point(t0, false);
                if (std::abs(t1 - t0) > options.param_tolerance) {
                    emit_point(t1, false);
                }
            }

            std::sort(
                out.items.begin(),
                out.items.end(),
                [](const IntersectionItem& lhs, const IntersectionItem& rhs) {
                    const auto& a = std::get<IntersectionPoint>(lhs);
                    const auto& b = std::get<IntersectionPoint>(rhs);
                    if (a.u_on_first != b.u_on_first) return a.u_on_first < b.u_on_first;
                    if (a.u_on_second != b.u_on_second) return a.u_on_second < b.u_on_second;
                    if (a.point.x() != b.point.x()) return a.point.x() < b.point.x();
                    return a.point.y() < b.point.y();
                });

            return topo::Result<IntersectionResult>(out);
        }

        /**
         * @brief Intersect two circular bounded spans.
         */
        topo::Result<IntersectionResult> intersect_circle_circle(
            const Curve& first,
            const Span& sa,
            const Curve& second,
            const Span& sb,
            const IntersectionOptions& options) {

            IntersectionResult out{};

            const CircleData c0 = circle_data(first, sa);
            const CircleData c1 = circle_data(second, sb);

            const XY delta = c1.center - c0.center;
            const real d = norm(delta);
            const real tol = options.point_tolerance;

            if (d <= tol && std::abs(c0.radius - c1.radius) <= tol) {
                return topo::Result<IntersectionResult>(topo::ResultError{
                    "CurveIntersection: coincident circle spans are not implemented in the current API",
                    topo::ErrorCode::geometry_error
                });
            }

            if (d > c0.radius + c1.radius + tol) {
                return topo::Result<IntersectionResult>(out);
            }

            if (d < std::abs(c0.radius - c1.radius) - tol) {
                return topo::Result<IntersectionResult>(out);
            }

            if (d <= tol) {
                return topo::Result<IntersectionResult>(out);
            }

            const real a = (c0.radius * c0.radius - c1.radius * c1.radius + d * d) / (real(2.0) * d);
            const real h2 = c0.radius * c0.radius - a * a;

            const XY ex = (real(1.0) / d) * delta;
            const XY base = c0.center + a * ex;
            const XY perp{-ex.y, ex.x};

            const auto emit_point = [&](const XY& ip, const bool tangent) {
                const auto u0 = circle_parameter_in_span(first, sa, ip, options);
                const auto u1 = circle_parameter_in_span(second, sb, ip, options);
                if (!u0.has_value() || !u1.has_value()) {
                    return;
                }

                append_point(
                    out,
                    to_point(ip),
                    *u0,
                    *u1,
                    tangent ? IntersectionPointKind::tangent
                            : IntersectionPointKind::simple);
            };

            if (std::abs(h2) <= tol) {
                emit_point(base, true);
            } else if (h2 > 0.0) {
                const real h = std::sqrt(h2);
                emit_point(base + h * perp, false);
                emit_point(base - h * perp, false);
            }

            std::sort(
                out.items.begin(),
                out.items.end(),
                [](const IntersectionItem& lhs, const IntersectionItem& rhs) {
                    const auto& a = std::get<IntersectionPoint>(lhs);
                    const auto& b = std::get<IntersectionPoint>(rhs);
                    if (a.u_on_first != b.u_on_first) return a.u_on_first < b.u_on_first;
                    if (a.u_on_second != b.u_on_second) return a.u_on_second < b.u_on_second;
                    if (a.point.x() != b.point.x()) return a.point.x() < b.point.x();
                    return a.point.y() < b.point.y();
                });

            return topo::Result<IntersectionResult>(out);
        }

        /**
         * @brief Swap the curve-parameter roles in one successful result when the
         *        low-level implementation was called with reversed input order.
         */
        void swap_result_parameter_roles(IntersectionResult& r) {
            for (auto& item : r.items) {
                if (std::holds_alternative<IntersectionPoint>(item)) {
                    auto& p = std::get<IntersectionPoint>(item);
                    std::swap(p.u_on_first, p.u_on_second);
                } else {
                    auto& o = std::get<IntersectionOverlap>(item);
                    std::swap(o.first_u0, o.second_u0);
                    std::swap(o.first_u1, o.second_u1);
                }
            }
        }

        /**
         * @brief Human-readable kind string used in unsupported diagnostics.
         */
        const char* kind_name(const SpanKind kind) noexcept {
            switch (kind) {
                case SpanKind::line_like:   return "segment";
                case SpanKind::circle_like: return "arc";
                default:                    return "unsupported-span";
            }
        }

    } // namespace

    topo::Result<IntersectionResult> intersect_bounded_spans(
        const Curve& first,
        const real first_u0,
        const real first_u1,
        const Curve& second,
        const real second_u0,
        const real second_u1,
        const IntersectionOptions& options) {
        try {
            const Span sa{first_u0, first_u1};
            const Span sb{second_u0, second_u1};

            const auto kind_a = classify_span_kind(first, sa);
            const auto kind_b = classify_span_kind(second, sb);

            if (kind_a == SpanKind::line_like && kind_b == SpanKind::line_like) {
                return intersect_segment_segment(first, sa, second, sb, options);
            }

            if (kind_a == SpanKind::line_like && kind_b == SpanKind::circle_like) {
                return intersect_segment_circle(first, sa, second, sb, options);
            }

            if (kind_a == SpanKind::circle_like && kind_b == SpanKind::line_like) {
                auto r = intersect_segment_circle(second, sb, first, sa, options);
                if (!r) {
                    return r;
                }
                swap_result_parameter_roles(r.value());
                return r;
            }

            if (kind_a == SpanKind::circle_like && kind_b == SpanKind::circle_like) {
                return intersect_circle_circle(first, sa, second, sb, options);
            }

            return topo::Result<IntersectionResult>(topo::ResultError{
                unsupported_message(kind_name(kind_a), kind_name(kind_b)),
                topo::ErrorCode::geometry_error
            });
        }
#if defined(TONB_HAS_OCCT_ADAPTERS)
        catch (const Standard_Failure& err) {
            return topo::Result<IntersectionResult>(topo::ResultError{
                std::string("CurveIntersection: OCCT failure: ") + err.GetMessageString(),
                topo::ErrorCode::geometry_error
            });
        }
#endif
        catch (const std::exception& err) {
            return topo::Result<IntersectionResult>(topo::ResultError{
                std::string("CurveIntersection: failure: ") + err.what(),
                topo::ErrorCode::geometry_error
            });
        }
    }
}
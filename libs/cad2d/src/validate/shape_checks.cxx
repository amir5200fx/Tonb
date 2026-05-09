//
// Created by amir on 1/24/26.
//
/**
 * @file shape_checks.cxx
 * @brief Implements high-level validation entry points for topo::Shape.
 */
#include <tonb/cad2d/validate/shape_checks.hxx>

#include <tonb/cad2d/validate/halfedge_checks.hxx>
#include <tonb/cad2d/validate/edge_checks.hxx>
#include <tonb/cad2d/validate/wire_checks.hxx>
#include <tonb/cad2d/validate/face_checks.hxx>
#include <tonb/cad2d/validate/halfedge_geometry.hxx>

#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/edge.hxx>
#include <tonb/cad2d/topo/wire.hxx>
#include <tonb/cad2d/topo/face.hxx>
#include <tonb/cad2d/topo/id.hxx>

namespace tonb::cad2d::validate {
    namespace {
        std::string ctx(const topo::Shape& shape) {
            return "ShapeChecks (shape id=" + topo::to_string(shape.id()) + ")";
        }

        topo::Result<void> fail(std::string msg, const topo::ErrorCode code) {
            return topo::Result<void>(topo::ResultError{std::move(msg), code});
        }

        template<class T>
        topo::Result<void> check_no_nulls(const topo::Shape& shape,
                                          const std::vector<std::shared_ptr<T>>& items,
                                          const char* kind) {
            for (std::size_t i = 0; i < items.size(); ++i) {
                if (!items[i]) {
                    return fail(ctx(shape) + ": " + kind + " registry contains a null entry at index " + std::to_string(i),
                                topo::ErrorCode::internal);
                }
            }
            return {};
        }

        topo::Result<void> check_vertices_basic(const topo::Shape& shape,
                                                const std::vector<std::shared_ptr<topo::Vertex>>& vertices) {
            if (auto r = check_no_nulls(shape, vertices, "vertex"); !r) return r;
            for (const auto& v : vertices) {
                if (v->id() == 0) {
                    return fail(ctx(shape) + ": vertex with invalid id=0 detected", topo::ErrorCode::topology_error);
                }
                if (v->tolerance() < 0.0) {
                    return fail(ctx(shape) + ": vertex id=" + topo::to_string(v->id()) + " has a negative tolerance",
                                topo::ErrorCode::invalid_input);
                }
            }
            return {};
        }

        topo::Result<void> check_shape_impl(const topo::Shape& shape,
                                            const geom::CurveStore* store,
                                            const topo::Tolerance& tol,
                                            const ShapeCheckOptions& opt) {
            const auto vertices = shape.vertices();
            const auto halfedges = shape.halfedges();
            const auto edges = shape.edges();
            const auto wires = shape.wires();
            const auto faces = shape.faces();

            if (opt.check_vertices) {
                if (auto r = check_vertices_basic(shape, vertices); !r) return r;
            }

            if (opt.check_halfedges) {
                if (auto r = check_no_nulls(shape, halfedges, "half-edge"); !r) return r;
                for (const auto& e : halfedges) {
                    if (auto r = check_halfedge(e); !r) {
                        return fail(ctx(shape) + ": half-edge validation failed (" + r.error().message + ")", r.error().code);
                    }
                    if (opt.check_geometry && store != nullptr) {
                        if (auto r = check_halfedge_geometry(e, *store, tol); !r) {
                            return fail(ctx(shape) + ": half-edge geometry validation failed (" + r.error().message + ")", r.error().code);
                        }
                    }
                }
            }

            if (opt.check_edges) {
                if (auto r = check_no_nulls(shape, edges, "edge"); !r) return r;
                for (const auto& edge : edges) {
                    if (auto r = check_edge(edge); !r) {
                        return fail(ctx(shape) + ": edge validation failed (" + r.error().message + ")", r.error().code);
                    }
                }
            }

            if (opt.check_wires) {
                if (auto r = check_no_nulls(shape, wires, "wire"); !r) return r;
                for (const auto& w : wires) {
                    if (auto r = check_wire(w, tol, opt.require_closed_wires, opt.verify_open_wire_ends); !r) {
                        return fail(ctx(shape) + ": wire validation failed (" + r.error().message + ")", r.error().code);
                    }
                }
            }

            if (opt.check_faces) {
                if (auto r = check_no_nulls(shape, faces, "face"); !r) return r;
                for (const auto& f : faces) {
                    if (auto r = check_face(f, tol, opt.require_closed_wires); !r) {
                        return fail(ctx(shape) + ": face validation failed (" + r.error().message + ")", r.error().code);
                    }
                }
            }

            return {};
        }
    }

    topo::Result<void> check_shape(const topo::Shape& shape, const topo::Tolerance& tol, const ShapeCheckOptions& opt) {
        return check_shape_impl(shape, nullptr, tol, opt);
    }

    topo::Result<void> check_shape(const topo::Shape& shape, const geom::CurveStore& store, const topo::Tolerance& tol,
                                   const ShapeCheckOptions& opt) {
        return check_shape_impl(shape, &store, tol, opt);
    }
}

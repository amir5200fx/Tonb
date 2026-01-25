//
// Created by amir on 1/24/26.
//
#include <tonb/cad2d/validate/shape_checks.hxx>

#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/wire.hxx>
#include <tonb/cad2d/topo/face.hxx>

#include <tonb/cad2d/validate/halfedge_checks.hxx>
#include <tonb/cad2d/validate/wire_checks.hxx>
#include <tonb/cad2d/validate/face_checks.hxx>

namespace tonb::cad2d::validate {
    namespace {
        /**
         * @brief Stable context label for error messages.
         */
        std::string ctx(const topo::Shape& s) {
            return "ShapeChecks (shape id=" + topo::to_string(s.id()) + ")";
        }

        /**
         * @brief Sort a vector of shared_ptr by the entity id, deterministically.
         *
         * If any pointer is null, sorting still succeeds (nulls are pushed to the end).
         */
        template<class T>
        void sort_by_id(std::vector<std::shared_ptr<T>> & v) {
            std::sort(v.begin(), v.end(),
           [](const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) {
             if (!a && !b) return false;
             if (!a) return false;          // nulls after non-nulls
             if (!b) return true;
             return a->id() < b->id();
           });
        }

        template<class T>
        topo::Result<void> check_no_nulls(const topo::Shape& s, const std::vector<std::shared_ptr<T>>& items, const char* what) {
            for (std::size_t i = 0; i < items.size(); ++i) {
                if (!items[i]) {
                    return topo::Result<void>(topo::ResultError{
                      ctx(s) + ": " + what + " registry snapshot contains a null pointer at index " + std::to_string(i),
                      topo::ErrorCode::internal
                    });
                }
            }
            return {};
        }


    }

    topo::Result<void> check_shape(const topo::Shape &shape, const topo::Tolerance &tol, const ShapeCheckOptions &opt) {
        // Snapshot registries first. This keeps behaviour consistent even if
        // validation is called while other code is mutating the shape (not recommended,
        // but snapshotting makes failure behaviour less surprising).
        auto vertices = shape.vertices();
        auto halfedges = shape.halfedges();
        auto wires = shape.wires();
        auto faces = shape.faces();

        // Deterministic ordering: sort by id so tests are repeatable.
        sort_by_id(vertices);
        sort_by_id(halfedges);
        sort_by_id(wires);
        sort_by_id(faces);

        // ---- Vertex checks (minimal) -----
        if (opt.check_vertices) {
            // At the moment, vertices hav no deep invariants beyond non-null presence.
            // Future extensions may validate incident edge sanity, tolerance sanity, etc.
            if (auto rv = check_no_nulls(shape, vertices, "vertex"); !rv) return rv;
        }

        // ---- Half-edge checks ----
        if (opt.check_halfedges) {
            if (auto re = check_no_nulls(shape, halfedges, "half-edge"); !re) return re;

            for (const auto& e : halfedges) {
                // Each half-edge check already returns contextual messages (edge ids).
                if (auto r = check_halfedge(e); !r) {
                    return topo::Result<void>(topo::ResultError{
                        ctx(shape) + ": half-edge validation failed (" + r.error().message + ")",
                        r.error().code
                    });
                }
            }
        }

        // ---- Wire checks ----
        if (opt.check_wires) {
            if (auto rw = check_no_nulls(shape, wires, "wire"); !rw) return rw;

            for (const auto& w : wires) {
                if (auto r  = check_wire(w, tol, opt.require_closed_wires, opt.verify_open_wire_ends); !r) {
                    return topo::Result<void>(topo::ResultError{
                        ctx(shape) + ": wire validation failed (" + r.error().message + ")",
                        r.error().code
                    });
                }
            }
        }

        // ---- Face checks ----
        if (opt.check_faces) {
            if (auto rf = check_no_nulls(shape, faces, "face"); !rf) return rf;

            for (const auto& f : faces) {
                // Faces should always have closed wires in the canonical model, but the
                // caller can override require_closed_wires for partial construction stages.
                auto r = check_face(f, tol, opt.require_closed_wires);
                if (!r) {
                    return topo::Result<void>(topo::ResultError{
                        ctx(shape) + ": face validation failed (" + r.error().message + ")",
                        r.error().code
                    });
                }
            }
        }
        return {};

    }
}

//
// Created by amir on 1/22/26.
//
#include <ranges>
#include <tonb/cad2d/topo/shape.hxx>

#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/cad2d/topo/face.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/wire.hxx>

namespace tonb::cad2d::topo {
    std::shared_ptr<Vertex> Shape::make_vertex(Pnt2d position, double tol) {
        const Id vid = ids_();
        const auto v = std::make_shared<Vertex>(vid, std::move(position), tol);
        vertices_.emplace(vid, v);
        return v;
    }

    std::shared_ptr<HalfEdge> Shape::make_halfedge(Id curveId, double u0, double u1, Orientation dir, double tol) {
        const Id eid = ids_();
        const auto e = std::make_shared<HalfEdge>(eid, curveId, u0, u1, dir, tol);
        halfedges_.emplace(eid, e);
        return e;
    }

    std::shared_ptr<Wire> Shape::make_wire() {
        const Id wid = ids_();
        const auto w = std::make_shared<Wire>(wid);
        wires_.emplace(wid, w);
        return w;
    }

    std::shared_ptr<Face> Shape::make_face() {
        const Id fid = ids_();
        const auto f = std::make_shared<Face>(fid);
        faces_.emplace(fid, f);
        return f;
    }

    std::shared_ptr<Vertex> Shape::vertex(const Id id) const noexcept {
        const auto it = vertices_.find(id);
        return it == vertices_.end() ? nullptr : it->second;
    }

    std::shared_ptr<HalfEdge> Shape::halfedge(const Id id) const noexcept {
        const auto it = halfedges_.find(id);
        return it == halfedges_.end() ? nullptr : it->second;
    }

    std::shared_ptr<Wire> Shape::wire(const Id id) const noexcept {
        const auto it = wires_.find(id);
        return it == wires_.end() ? nullptr : it->second;
    }

    std::shared_ptr<Face> Shape::face(const Id id) const noexcept {
        const auto it = faces_.find(id);
        return it == faces_.end() ? nullptr : it->second;
    }

    std::vector<std::shared_ptr<Vertex>> Shape::vertices() const {
        std::vector<std::shared_ptr<Vertex>> out;
        out.reserve(vertices_.size());
        for (const auto &val: vertices_ | std::views::values) out.push_back(val);
        return out;
    }

    std::vector<std::shared_ptr<HalfEdge>> Shape::halfedges() const {
        std::vector<std::shared_ptr<HalfEdge>> out;
        out.reserve(halfedges_.size());
        for (const auto &val: halfedges_ | std::views::values) out.push_back(val);
        return out;
    }

    std::vector<std::shared_ptr<Wire>> Shape::wires() const {
        std::vector<std::shared_ptr<Wire>> out;
        out.reserve(wires_.size());
        for (const auto &val: wires_ | std::views::values) out.push_back(val);
        return out;
    }

    std::vector<std::shared_ptr<Face>> Shape::faces() const {
        std::vector<std::shared_ptr<Face>> out;
        out.reserve(faces_.size());
        for (const auto &val: faces_ | std::views::values) out.push_back(val);
        return out;
    }

    bool Shape::erase_vertex(Id id) noexcept {
        return vertices_.erase(id) > 0;
    }

    bool Shape::erase_halfedge(Id id) noexcept {
        return halfedges_.erase(id) > 0;
    }

    bool Shape::erase_wire(Id id) noexcept {
        return wires_.erase(id) > 0;
    }

    bool Shape::erase_face(Id id) noexcept {
        return faces_.erase(id) > 0;
    }

    Result<void> Shape::check_basic(const Tolerance &tol, bool requireClosed) const {
        // Verify registries contain non-null pointers
        for (const auto& kv : vertices_) {
            if (!kv.second) {
                return Result<void>(ResultError{
                    "shape basic check failed: a stored vertex pointer is null",
                    ErrorCode::internal
                });
            }
        }
        for (const auto& kv: halfedges_) {
            if (!kv.second) {
                return Result<void>(ResultError{
                    "Shape basic check failed: a stored half-edge pointer is null",
                    ErrorCode::internal
                });
            }
        }
        for (const auto& kv: wires_) {
            if (!kv.second) {
                return Result<void>(ResultError{
                    "Shape basic check failed: a stored wire pointer is null",
                    ErrorCode::internal
                });
            }
        }
        for (const auto& kv: faces_) {
            if (!kv.second) {
                return Result<void>(ResultError{
                    "Shape basic check failed: a stored face pointer is null",
                    ErrorCode::internal
                });
            }
        }

        // Verify each face has basic boundary integrity.
        for (const auto& kv: faces_) {
            const auto& f = kv.second;
            const auto r = f->check_basic(tol, requireClosed);
            if (!r) {
                return Result<void>(ResultError{
                    "Shape basic check failed: face boundary check failed for face id=" + std::to_string(f->id()) +
                        " (" + r.error().message + ")",
                    r.error().code
                });
            }
        }
        return Result<void>{};
    }
}

//
// Created by amir on 11/8/25.
//
#pragma once

namespace tonb::mesh::topology3d {
    inline CellHandle VolumeMesh::add_tet(const index_t a, const index_t b, const index_t c, const index_t d) {
        const Tri f0{{b, c, a}};
        const Tri f1{{a, c, d}};
        const Tri f2{{a, d, b}};
        const Tri f3{{b, d, c}};
        const std::array<HalffaceHandle, 4> hfs{
        make_halfface(f0), make_halfface(f1), make_halfface(f2), make_halfface(f3)};
        Cell cell{};
        cell.arity = 4;
        cell.hfaces = {hfs[0], hfs[1], hfs[2], hfs[3], HalffaceHandle{}, HalffaceHandle{}};
        cells_.push_back(cell);
        const CellHandle ch{static_cast<index_t>(cells_.size() - 1)};
        for (int i = 0; i < 4; ++i) {
            halffaces_[core::idx(hfs[i])].owner = ch;
        }
        return ch;
    }

    inline CellHandle VolumeMesh::add_hex(const index_t v0, const index_t v1, const index_t v2, const index_t v3, const index_t v4, const index_t v5,
        const index_t v6, const index_t v7) {
        const Quad qb{{v0,v1,v2,v3}}; // bottom (z-)
        const Quad qt{{v4,v5,v6,v7}}; // top (z+)
        const Quad qf{{v0,v1,v5,v4}}; // front (y-)
        const Quad qk{{v3,v2,v6,v7}}; // back (y+)
        const Quad ql{{v0,v4,v7,v3}}; // left (x-)
        const Quad qr{{v1,v2,v6,v5}}; // right (x+)

        const std::array<HalffaceHandle,6> hfs{
            make_halfface(qb), make_halfface(qt), make_halfface(qf),
            make_halfface(qk), make_halfface(ql), make_halfface(qr)
            };
        Cell cell{}; cell.arity = 6;
        cell.hfaces = {hfs[0],hfs[1],hfs[2],hfs[3],hfs[4],hfs[5]};
        cells_.push_back(cell);
        const CellHandle ch{static_cast<index_t>(cells_.size() - 1)};
        for (int i = 0; i < 6; ++i) halffaces_[core::idx(hfs[i])].owner = ch;
        return ch;
    }

    inline std::vector<FaceHandle> VolumeMesh::boundary_faces() const {
        std::vector<FaceHandle> out;
        out.reserve(faces_.size());
        for (index_t i = 0; i < static_cast<index_t>(faces_.size()); ++i) {
            if (!faces_[i].hf1) out.emplace_back(i);
        }
        return out;
    }

    inline HalffaceHandle VolumeMesh::make_halfface(const Tri & t) {
        const FaceKey key = make_face_key(t);
        auto [fh, created] = get_or_create_face(key, 3, {t.v[0], t.v[1], t.v[2], npos});
        (void)created;
        Halfface hf;
        hf.face = fh;
        hf.arity = 3;
        hf.v = {t.v[0], t.v[1], t.v[2], npos};
        halffaces_.push_back(hf);
        const HalffaceHandle h{static_cast<index_t>(halffaces_.size() - 1)};
        wire_halfface(h, fh);
        return h;
    }

    inline HalffaceHandle VolumeMesh::make_halfface(const Quad & q) {
        const FaceKey key = make_face_key(q);
        auto [fh, created] = get_or_create_face(key, 4, {q.v[0], q.v[1], q.v[2], q.v[3]});
        (void)created;
        Halfface hf;
        hf.face = fh;
        hf.arity = 4;
        hf.v = {q.v[0], q.v[1], q.v[2], q.v[3]};
        halffaces_.push_back(hf);
        const HalffaceHandle h{static_cast<index_t>(halffaces_.size() - 1)};
        wire_halfface(h, fh);
        return h;
    }

    inline std::pair<FaceHandle, bool> VolumeMesh::get_or_create_face(const FaceKey &key, const std::uint8_t arity,
        const std::array<index_t, 4> v) {
        if (const auto it = face_lut.find(key); it != face_lut.end()) {
            return {FaceHandle(it->second), false};
        }
        Face f;
        f.arity = arity;
        f.v = v;
        f.hf0 = HalffaceHandle{};
        f.hf1 = HalffaceHandle{};
        faces_.push_back(f);
        auto idx = static_cast<index_t>(faces_.size() - 1);
        face_lut.emplace(key, idx);
        return {FaceHandle(idx), true};
    }

    inline void VolumeMesh::wire_halfface(const HalffaceHandle h, const FaceHandle fh) {
        Face& f = faces_[core::idx(fh)];
        Halfface& hh = halffaces_[core::idx(h)];
        if (!f.hf0) {
            f.hf0 = h; hh.twin = HalffaceHandle{};  // boundary for now
        } else if (!f.hf1) {
            f.hf1 = h; hh.twin = f.hf0;             // pair with first
            halffaces_[core::idx(f.hf0)].twin = h;  // wire twin back
        } else {
            // Non-manifold: more than two incident cells on a face (not supported yet)
            assert(false && "Non-manifold face insertion");
        }
    }
}

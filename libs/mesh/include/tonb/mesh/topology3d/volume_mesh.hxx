//
// Created by amir on 11/8/25.
//
#pragma once
#ifndef TONB_MESH_TOPOLOGY3D_VOLUME_MESH_HXX
#define TONB_MESH_TOPOLOGY3D_VOLUME_MESH_HXX

#include <tonb/mesh/core/handles.hxx>
#include <tonb/geometry/utils/hash.hxx>
#include <array>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <cassert>
#include <initializer_list>
#include <algorithm>

namespace tonb::mesh::topology3d {

    using core::npos;
    using core::VertexHandle;
    using core::FaceHandle;
    using core::HalffaceHandle;
    using core::CellHandle;

    // ============================================================================
    // Small helpers
    // ============================================================================

    /** @brief Triangle face as 3 vertex indices. */
    struct Tri {index_t v[3];};
    /** @brief Quad face as 4 vertex indices. */
    struct Quad {index_t v[4];};

    /** @brief Discrete face arity {triangle or quad}. */
    enum class FaceType : std::uint8_t {triangle = 3, quad = 4};

    /**
     * @brief Canonical, orientation-independent key for a face.
     *
     * Faces are deduplicated using a sorted tuple of their vertex indices and
     * their arity (3 or 4). This ensures that two cells referencing the same
     * geometric face (possibly with different local orientation) map to the same
     * shared `Face` record and thus their halffaces can be paired as twins.
     */
    struct FaceKey {
        std::array<index_t, 4> v{npos, npos, npos, npos};
        std::uint8_t arity = 0;
        bool operator==(const FaceKey & o) const noexcept {return v == o.v && arity == o.arity;}
    };

    /** @brief Build a canonical FaceKey from a triangle (order-insensitive).*/
    inline FaceKey make_face_key(const Tri& t) {
        std::array<index_t, 3> a{t.v[0], t.v[1], t.v[2]};
        std::ranges::sort(a);
        FaceKey k; k.v = {a[0], a[1], a[2], npos}; k.arity = 3; return k;
    }

    /** @brief Build a canonical FaceKey from a quad (order-insensitive).*/
    inline FaceKey make_face_key(const Quad& q) {
        std::array<index_t, 4> a{q.v[0], q.v[1], q.v[2], q.v[3]};
        std::ranges::sort(a);
        FaceKey k; k.v = {a[0], a[1], a[2], a[3]}; k.arity = 4; return k;
    }

    // ============================================================================
    // Core topology records
    // ============================================================================

    /**
     * @brief Directed face that belongs to exactly one cell.
     *
     * A Halfface stores the outward-oriented vertex loop of a face as seen from
     * its owning cell. If the face is shared by two cells, the other cell will
     * own the opposite halfface; the two are connected via `twin`.
     */
    struct Halfface {
        /// Vertex loop in CCW order as seen from *outside* the owner cell
        /// (size is 3 for tri, 4 fro quad). Unused entries are `invalid_index`.
        std::array<index_t, 4> v {npos, npos, npos, npos};
        std::uint8_t arity = 0;         ///< 3 or 4

        FaceHandle face;                ///< Shared, orientation-agnostic face entity
        HalffaceHandle twin;            ///< Opposite halfface across the face (invalid for boundary)
        CellHandle owner;               ///< Owning cell
    };

    /**
     * @brief Shared face record (orientation-agnostic).
     *
     * A Face is a shared entity referenced by up to two halffaces (one per cell).
     * If only `hf0` is present, the face is a **boundary** face.
     */
    struct Face {
        std::array<index_t, 4> v{npos, npos, npos, npos};
        std::uint8_t arity = 0;             ///< 3 or 4
        HalffaceHandle hf0;                 ///< First incident halfface
        HalffaceHandle hf1;                 ///< Second incident halfface (or invalid)
    };

    /**
     * @brief Volumetric cell.
     *
     * Stores up to 6 halffaces (hexahedra) or 4 (tetrahedra). Unused slots are
     * invalid. The `arity` stores the number of active halffaces.
     */
    struct Cell {
        std::array<HalffaceHandle, 6> hfaces;  ///< Incident halffaces
        std::uint8_t arity = 0;                ///< Number of faces
    };

    /**
     * @brief Placeholder vertex record for symmetry; geometry lives elsewhere.
     */
    struct Vertex { /* position lives in attributes elsewhere */};

    // ============================================================================
    // Mesh container
    // ============================================================================

    /**
     * @brief Minimal volume mesh topology container.
     *
     * Owns pools of `Vertex`, `Face`, `Halfface`, and `Cell` records and provides
     * builders form common element types (tets, hexes). Topology is wired on insert;
     * faces are deduplicated by canonical keys and halffaces are paired as twins
     * when the same face is referenced by two cells.
     */
    class VolumeMesh {
    public:
        // ----------------------------- creation ----------------------------------

        /** @brief Add a vertex and return its handle. */
        auto add_vertex() {
            vertices_.emplace_back();
            return VertexHandle(static_cast<index_t>(vertices_.size() - 1));
        }

        /**
         * @brief Add a tetrahedron by vertex indices with outward orientation.
         *
         * The tet is defined by vertices (a,b,c,d). Faces are inserted with
         * outward CCW cycles: (b,c,a), (a,c,d), (a,d,b), (b,d,c).
         */
        CellHandle add_tet(index_t a, index_t b, index_t c, index_t d);

        /**
         * @brief Add a hexahedron by vertex indices (standard cube convention).
         *
         * Vertex order: bottom v0 v1 v2 v3 (CCW seen from +z), top v4 v5 v6 v7.
         * Inserts 6 outward-oriented quads.
         */
        CellHandle add_hex(index_t v0, index_t v1, index_t v2, index_t v3, index_t v4, index_t v5, index_t v6, index_t v7);

        // ----------------------------- queries -----------------------------------

        /** @brief Return all boundary faces (faces referenced by exactly one cell).*/
        std::vector<FaceHandle> boundary_faces() const;

        // ----------------------------- accessors ---------------------------------

        /** @name Read-only accessors*/
        ///@{
        const Face&     face(const FaceHandle fh)        const {return faces_[core::idx(fh)];}
        const Halfface& halfface(const HalffaceHandle h) const {return halffaces_[core::idx(h)];}
        const Cell&     cell(const CellHandle ch)        const {return cells_[core::idx(ch)];}
        ///@}

        /** @name Sizes */
        ///@{
        std::size_t nb_vertices()   const {return vertices_.size();}
        std::size_t nb_faces()      const {return faces_.size();}
        std::size_t nb_halffaces()  const {return halffaces_.size();}
        std::size_t nb_cells()      const {return cells_.size();}
        ///@}

    private:
        // ---------------------------- internals ----------------------------------

        /** @brief Create or fetch a shared face; create a hlafface and wire twin.*/
        HalffaceHandle make_halfface(const Tri& );

        /** @brief Create or fetch a shared face; create a halfface and wire twin.*/
        HalffaceHandle make_halfface(const Quad&);

        /**
         * @brief Get or create a shared face record.
         * @return (FaceHandle, created?) where `created` is true if a new Face was inserted.
         */
        std::pair<FaceHandle, bool> get_or_create_face(const FaceKey& key, std::uint8_t arity, std::array<index_t, 4> v);

        /**
         * @brief Wire a new halfface to a shared face and set its twin if possible.
         *
         * If a face has no previous halfface, the new one becomes `hf0` (boundary so
         * far). If `hf0` exists but `hf1` is empty, the new halfface becomes `hf1`
         * and the two are paired as twins. More than two incidents are treated as a
         * non-manifold error (asset) in this minimal skeleton.
         */
        void wire_halfface(HalffaceHandle h, FaceHandle fh);
        // Pools
        std::vector<Vertex>     vertices_;     ///< Vertex storage (geometry external)
        std::vector<Face>       faces_;        ///< Shared faces
        std::vector<Halfface>   halffaces_;    ///< Cell-owned directed faces
        std::vector<Cell>       cells_;        ///< Cells (tets/hexes)

        // canonical key -> face index
        std::unordered_map<FaceKey, index_t, geometry::utils::hash::FaceKeyHash<FaceKey>> face_lut;
    };
}
#include <tonb/mesh/topology3d/private/volume_mesh_imp.hxx>
#endif //TONB_MESH_TOPOLOGY3D_VOLUME_MESH_HXX
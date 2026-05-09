//
// Created by amir on 11/8/25.
//
#pragma once
#ifndef TONB_MESH_AFT2D_TOPOLOGY_HXX
#define TONB_MESH_AFT2D_TOPOLOGY_HXX

#include <tonb/mesh/core/handles.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/geometry/pnt_2d.hxx>
#include <vector>
#include <queue>
#include <limits>
#include <cstdint>
#include <optional>
#include <cmath>
#include <cassert>
#include <cstdint>
#include <unordered_map>

namespace tonb::mesh::aft2d {
    using base::index_t;
    using base::real;
    using core::VertexHandle;
    using core::HalfedgeHandle;
    using core::FaceHandle;
    using core::EdgeHandle;

    using geometry::Pnt2d;
    // ---------------------------------------------------------------------------
    // Core records
    // ---------------------------------------------------------------------------

    /**
     * @brief Bit flags describing edge properties in AFT (orthogonal attributes).
     *
     * Rationale:
     *  - An edge can be both FRONT and CONSTRAINED (typical for initial boundary).
     *  - INTERIOR is often derivable (not on front and has an incident face),
     *    but keeping a flag is fine if it simplifies your logic.
     */
    enum class EdgeFlags : std::uint8_t {
        none         = 0,
        front        = 1u << 0,     ///< edge is part of the active advancing front
        constrained  = 1u << 1,     ///< edge is a constraint (must not be altered/removed)
        interior     = 1u << 2      ///< edge is interior to the mesh (optional convenience)
    };

    constexpr inline EdgeFlags operator|(EdgeFlags a, EdgeFlags b) noexcept {
        return static_cast<EdgeFlags>(static_cast<std::uint8_t>(a) | static_cast<std::uint8_t>(b));
    }
    constexpr inline EdgeFlags operator&(EdgeFlags a, EdgeFlags b) noexcept {
        return static_cast<EdgeFlags>(static_cast<std::uint8_t>(a) & static_cast<std::uint8_t>(b));
    }
    constexpr inline EdgeFlags& operator|=(EdgeFlags& a, const EdgeFlags b) noexcept { return a = (a | b); }
    constexpr inline EdgeFlags& operator&=(EdgeFlags& a, const EdgeFlags b) noexcept { return a = (a & b); }
    constexpr inline EdgeFlags operator~(EdgeFlags a) noexcept {
        return static_cast<EdgeFlags>(~static_cast<std::uint8_t>(a));
    }

    constexpr inline bool has_flag(const EdgeFlags v, const EdgeFlags f) noexcept {
        return (static_cast<std::uint8_t>(v & f) != 0);
    }
    constexpr inline void set_flag(EdgeFlags& v, const EdgeFlags f) noexcept {v |= f;}
    constexpr inline void clear_flag(EdgeFlags& v, const EdgeFlags f) noexcept {v &= ~f;}

    /** @brief 2D vertex with position. */
    struct Vertex2D {
        Pnt2d pos;
        HalfedgeHandle out;         ///< one outgoing halfedge (if any)
    };

    struct Edge2D {
        HalfedgeHandle h0;          ///< one direction
        HalfedgeHandle h1;          ///< opposite direction
        EdgeFlags flags = EdgeFlags::front; ///< default: newly created edges are front edges
    };

    // Queries
    inline bool is_front(const Edge2D& e) noexcept {return has_flag(e.flags, EdgeFlags::front);}
    inline bool is_constrained(const Edge2D& e) noexcept {return has_flag(e.flags, EdgeFlags::constrained);}
    inline bool is_interior(const Edge2D& e) noexcept {return has_flag(e.flags, EdgeFlags::interior);}

    // Transitions
    inline void mark_front(Edge2D& e) noexcept {set_flag(e.flags, EdgeFlags::front); clear_flag(e.flags, EdgeFlags::interior);}
    inline void mark_interior(Edge2D& e) noexcept { clear_flag(e.flags, EdgeFlags::front); set_flag(e.flags, EdgeFlags::interior);}
    inline void mark_constrained(Edge2D& e) noexcept {set_flag(e.flags, EdgeFlags::constrained);}

    /**
     * @brief Directed halfedge for planar 2D triangulation.
     *
     * Advancing fron needs access to (from, to) even when prev/next are not yet
     * a valid face loop. Therefore `from` is stored explicitly.
     *
     * Invariants:
     *  - h.twin is valid and twin(twin(h)) == h
     *  - h.edge is valid and refers to an Edge2D that contains h and h.twin
     *  - If h.face is valid, then h.next and h.prev are valid and from a 3-cycle
     *    for a triangle face (CCW orientation around the left face).
     *  - If h.face is invalid, h.next and h.prev may still e valid if the halfedge
     *    is participating in a front ring.
     */
    struct Halfedge2D {
        VertexHandle from;          ///< tail vertex
        VertexHandle to;            ///< head vertex (halfedge is v_from -> to)

        HalfedgeHandle twin;        ///< opposite halfedge

        // Face loop adjacency (valid only when face is valid)
        HalfedgeHandle next;        ///< next halfedge around left face
        HalfedgeHandle prev;        ///< prev halfedge around left face

        // Front ring adjacency (valid only when undirected edge is FRONT)
        HalfedgeHandle front_next{};
        HalfedgeHandle front_prev{};

        FaceHandle face;            ///< left face (triangle) or invalid for boundary/front
        EdgeHandle edge;            ///< owning undirected edge
    };

    /**
     * @brief Triangular face.
     *
     * Holds one halfedge of the face. The remaining two are reachable via next.
     */
    struct Face2D {
        HalfedgeHandle h;           ///< one of the 3 halfedges (CCW)
    };

    // ---------------------------------------------------------------------------
    // Mesh container
    // ---------------------------------------------------------------------------

    /**
     * @brief 2D halfedge topology container aimed at advancing-front triangulation.
     *
     * This class provides a robust handle-based topology kernel:
     *  - Vertices, halfedges, edges, and faces are stored in contiguous pools.
     *  - Undirected edges are first-class entities addressed by EdgeHandle.
     *  - Halfedges store `from` and `to` explicitly, which avoids reliance on
     *    face loops for basic segment queries.
     *  - A boundary loop builder wires a front ring and marks boundary edges as
     *    constrained and front.
     *  - Triangle insertion wires a face loop and updates edge flags.
     *  - A front edge split utility supports common advancing-front workflows.
     *
     * Geometry and predicates:
     *  - This topology does not perform intersection tests, quality tests, or
     *    sizing-field evaluation. Those belong to the meshing algorithm layer.
     */
    class Mesh2D {
    public:
        // ------------------------------------------------------------------------
        // Creation and access
        // ------------------------------------------------------------------------

        /** @brief Add a vertex. */
        auto add_vertex(const Pnt2d& pt) {
            vertices_.push_back(Vertex2D{pt, HalfedgeHandle{}});
            return VertexHandle(static_cast<index_t>(vertices_.size() - 1));
        }

        /**
         * @brief Reserve storage for expected sizes.
         *
         * Reserving is recommended because advancing-front algorithms can create
         * many small entities. Reserving reduces reallocation churn.
         */
        void reserve(const std::size_t n_vertices, const std::size_t n_edges, const std::size_t n_faces)
        {
            vertices_.reserve(n_vertices);
            edges_.reserve(n_edges);
            halfedges_.reserve(n_edges * 2);
            faces_.reserve(n_faces);
            edge_lut_.reserve(n_edges);
        }

        // Accessors
        const Vertex2D& V(const VertexHandle vh) const {return vertices_.at(static_cast<std::size_t>(core::idx(vh)));}
        Vertex2D&       V(const VertexHandle vh)       {return vertices_.at(static_cast<std::size_t>(core::idx(vh)));}

        const Halfedge2D& H(const HalfedgeHandle hh) const {return halfedges_.at(static_cast<std::size_t>(core::idx(hh)));}
        Halfedge2D&       H(const HalfedgeHandle hh)       {return halfedges_.at(static_cast<std::size_t>(core::idx(hh)));}

        const Face2D& F(const FaceHandle fh) const {return faces_.at(static_cast<std::size_t>(core::idx(fh)));}
        Face2D&       F(const FaceHandle fh)       {return faces_.at(static_cast<std::size_t>(core::idx(fh)));}

        const Edge2D& E(const EdgeHandle eh) const {return edges_.at(static_cast<std::size_t>(core::idx(eh)));}
        Edge2D&       E(const EdgeHandle eh)       {return edges_.at(static_cast<std::size_t>(core::idx(eh)));}

        // ------------------------------------------------------------------------
        // Undirected edge creation and lookup
        // ------------------------------------------------------------------------

        /**
         * @brief Get or create the directed halfedge u -> v.
         *
         * If the undirected edge (u,v) does not exist, this method creates:
         *  - two halfedges: u->v and v->u
         *  - one undirected edge entity Edge2D that owns the pair
         *  - a LUT entry mapping the undirected vertex pair to EdgeHandle
         *
         * New edges are flagged as front by default. The meshing algorithm may
         * later clear the front flag when an edge is consumed.
         *
         * @return The directed halfedge handle whose orientation is exactly u -> v.
         */
        HalfedgeHandle edge(const VertexHandle u, const VertexHandle v) {
            assert(u && v);
            assert(core::idx(u) != core::idx(v) && "Self-edge is not supported.");

            const std::uint64_t key = key_of(u, v);
            if (const auto it = edge_lut_.find(key); it != edge_lut_.end()) {
                const EdgeHandle eh = it->second;
                return directed_halfedge(eh, u, v);
            }

            // Create the directed twin pair
            Halfedge2D hu{};
            Halfedge2D hv{};
            hu.from = u; hu.to = v;
            hv.from = v; hv.to = u;

            halfedges_.push_back(hu);
            const HalfedgeHandle huv{static_cast<index_t>(halfedges_.size() - 1)};

            halfedges_.push_back(hv);
            const HalfedgeHandle hvu{static_cast<index_t>(halfedges_.size() - 1)};

            // Twin wiring
            halfedges_[core::idx(huv)].twin = hvu;
            halfedges_[core::idx(hvu)].twin = huv;

            // Create undirected edge entity
            Edge2D e{};
            const HalfedgeHandle rep = choose_rep(huv, hvu);
            e.h0 = rep;
            e.h1 = halfedges_[core::idx(rep)].twin;
            e.flags = EdgeFlags::front;

            edges_.push_back(e);
            const EdgeHandle eh{static_cast<index_t>(edges_.size() - 1)};

            // Back-reference from halfedges to undirected edge handle
            halfedges_[core::idx(huv)].edge = eh;
            halfedges_[core::idx(hvu)].edge = eh;

            // Set vertex outgoing pointers if empty
            if (!vertices_[core::idx(u)].out) vertices_[core::idx(u)].out = huv;
            if (!vertices_[core::idx(v)].out) vertices_[core::idx(v)].out = hvu;

            // LUT maps undirected pair to EdgeHandle
            edge_lut_.emplace(key, eh);

            return directed_halfedge(eh, u, v);
        }

        // ------------------------------------------------------------------------
        // Edge flag queries and transitions
        // ------------------------------------------------------------------------

        /** @brief Return flags of the undirected edge containing the given halfedge. */
        EdgeFlags edge_flags(const HalfedgeHandle h) const {
            const EdgeHandle eh = H(h).edge;
            assert(eh);
            return E(eh).flags;
        }

        /** @brief True if this undirected edge is currently part of the active front. */
        bool is_front_edge(const HalfedgeHandle h) const {
            return has_flag(edge_flags(h), EdgeFlags::front);
        }

        /** @brief True if this undirected edge is constrained. */
        bool is_constrained_edge(const HalfedgeHandle h) const {
            return has_flag(edge_flags(h), EdgeFlags::constrained);
        }

        /** @brief Mark an undirected edge as constrained. */
        void mark_constrained(const HalfedgeHandle h) {
            Edge2D& e = E(H(h).edge);
            set_flag(e.flags, EdgeFlags::constrained);
        }

        /**
         * @brief Mark an undirected edge as interior.
         *
         * Clears the front flag and sets the interior flag. Constrained is preserved.
         */
        void mark_interior(const HalfedgeHandle h) {
            Edge2D& e = E(H(h).edge);
            clear_flag(e.flags, EdgeFlags::front);
            set_flag(e.flags, EdgeFlags::interior);
        }

        /**
         * @brief Mark an undirected edge as front.
         *
         * Sets the front flag and clears the interior flag.
         */
        void mark_front(const HalfedgeHandle h) {
            Edge2D& e = E(H(h).edge);
            set_flag(e.flags, EdgeFlags::front);
            clear_flag(e.flags, EdgeFlags::interior);
        }

        // ------------------------------------------------------------------------
        // Front loop initialisation
        // ------------------------------------------------------------------------

        /**
         * @brief Build a single boundary loop and wire it as a front ring.
         *
         * Input:
         *  - `loop` is a sequence of vertex handles describing a closed polygon.
         *  - The loop must be ordered CCW with respect to the interior domain.
         *
         * Behaviour:
         *  - Creates directed edges v[i] -> v[i+1] (with wrap-around).
         *  - Wires `front_next` and `front_prev` among those directed halfedges to form a ring.
         *  - Marks each undirected edge as front and constrained.
         *
         * Output:
         *  - Returns one halfedge on the front ring, oriented along the loop.
         *
         * Important:
         *  - Faces are not created here. `face` remains invalid on boundary halfedges.
         */
        HalfedgeHandle build_boundary_loop(const std::vector<VertexHandle>& loop) {
            assert(loop.size() >= 3);

            const std::size_t n = loop.size();
            std::vector<HalfedgeHandle> ring;
            ring.reserve(n);

            for (std::size_t i = 0; i < n; ++i) {
                const VertexHandle a = loop[i];
                const VertexHandle b = loop[(i + 1) % n];
                const HalfedgeHandle h = edge(a, b);
                ring.push_back(h);
            }

            for (std::size_t i = 0; i < n; ++i) {
                const HalfedgeHandle h = ring[i];
                const HalfedgeHandle hn = ring[(i + 1) % n];
                const HalfedgeHandle hp = ring[(i + n - 1) % n];

                H(h).front_next = hn;
                H(h).front_prev = hp;
            }

            for (const HalfedgeHandle h : ring) {
                mark_front(h);
                mark_constrained(h);
            }

            return ring.front();
        }

        /**
         * @brief Return representatives of all undirected edges that are flagged as front.
         *
         * The representatives returned are `Edge2D::h0`, so the orientation may not
         * correspond to an ordered loop traversal. Use `next` pointers from a known
         * boundary halfedge for ordered traversal along one loop.
         */
        std::vector<HalfedgeHandle> front_edges() const {
            std::vector<HalfedgeHandle> out;
            out.reserve(edges_.size());
            for (const auto& e : edges_) {
                if (has_flag(e.flags, EdgeFlags::front)) out.push_back(e.h0);
            }
            return out;
        }

        // ------------------------------------------------------------------------
        // Face creation
        // ------------------------------------------------------------------------

        /**
         * @brief Add a CCW triangle (a,b,c) as a topological face.
         *
         * Preconditions:
         *  - The algorithm has validated the geometric correctness of the triangle.
         *  - The order (a,b,c) is CCW with respect to the interior domain.
         *
         * Behaviour:
         *  - Obtain directed halfedges a->b, b->c, c->a (creating edges if needed).
         *  - Wires a CCW face loop through next/prev.
         *  - Creates a Face2D and assigns it to the three halfedges.
         *  - Marks the involved undirected edges as interior (consumed).
         *
         * Notes:
         *  - This method wires `next` and `prev` for the face loop. If you are also
         *    using `next` and `prev` for front-ring adjacency, the advancing-front algorithm
         *    should manage when and how these fields are rewired.
         */
        FaceHandle add_triangle(const VertexHandle a, const VertexHandle b, const VertexHandle c) {
            const HalfedgeHandle ab = edge(a, b);
            const HalfedgeHandle bc = edge(b, c);
            const HalfedgeHandle ca = edge(c, a);

            // Wire CCW face loop: ab -> bc -> ca
            H(ab).next = bc; H(bc).prev = ab;
            H(bc).next = ca; H(ca).prev = bc;
            H(ca).next = ab; H(ab).prev = ca;

            faces_.push_back(Face2D{ab});
            const FaceHandle f{static_cast<index_t>(faces_.size() - 1)};

            H(ab).face = f;
            H(bc).face = f;
            H(ca).face = f;

            mark_interior(ab);
            mark_interior(bc);
            mark_interior(ca);

            return f;
        }

        // ------------------------------------------------------------------------
        // Front edge split
        // ------------------------------------------------------------------------

        /**
         * @brief Split a front edge by inserting a new vertex and rewiring the front ring.
         *
         * Input:
         *  - `h` must be a halfedge that is part of the front ring.
         *  - `pt` is the new vertex position.
         *
         * Behaviour:
         *  - Creates a new vertex w at pt.
         *  - Creates two new front edges u->w and w->v along the ring direction.
         *  - Rewires the front ring so that the old segment u->v is replaced by two
         *    segments u->w and w->v.
         *  - If the original undirected edge was constrained, the constraint is
         *    propagated to the two new undirected edges.
         *  - The original undirected edge is demoted from front to interior.
         *
         * Output:
         *  - Returns the new vertex handle w.
         *
         * Important:
         *  - This is a topological operation. Geometric intersection and quality
         *    checks belong ot he
         */
        VertexHandle split_front_edge(const HalfedgeHandle h, const Pnt2d& pt) {
            assert(h);
            assert(is_front_edge(h) && "split_front_edge requires a front edge.");

            const VertexHandle u = H(h).from;
            const VertexHandle v = H(h).to;

            const HalfedgeHandle hp = H(h).front_prev;
            const HalfedgeHandle hn = H(h).front_next;

            const bool was_constrained = is_constrained_edge(h);

            const VertexHandle w = add_vertex(pt);

            const HalfedgeHandle uw = edge(u, w);
            const HalfedgeHandle wv = edge(w, v);

            // Rewire front ring: hp -> uw -> wv -> hn
            H(uw).front_prev = hp;
            H(uw).front_next = wv;
            H(wv).front_prev = uw;
            H(wv).front_next = hn;

            if (hp) H(hp).front_next = uw;
            if (hn) H(hn).front_prev = wv;

            mark_front(uw);
            mark_front(wv);

            if (was_constrained) {
                mark_constrained(uw);
                mark_constrained(wv);
            }

            // Demote old edge from front; optional: clear its front links
            mark_interior(h);
            H(h).front_prev = HalfedgeHandle{};
            H(h).front_next = HalfedgeHandle{};

            return w;
        }

        // ------------------------------------------------------------------------
        // Validation
        // ------------------------------------------------------------------------

        /**
         * @brief Validate core invariants of the topology container.
         *
         * Checks performed:
         *  - twin symmetry for every halfedge
         *  - halfedge edge handle validity
         *  - edge records contain twin halfedges
         *  - edge representatives are consistent with stored halfedge edge handles
         *
         * This function is intended for debug builds and unit tests.
         */
        bool validate_basic() const {
            // Halfedge checks
            for (std::size_t i = 0; i < halfedges_.size(); ++i) {
                const HalfedgeHandle h{static_cast<index_t>(i)};
                const Halfedge2D& hh = halfedges_[i];

                if (!hh.twin) return false;

                const Halfedge2D& ht = halfedges_.at(static_cast<std::size_t>(core::idx(hh.twin)));
                if (core::idx(ht.twin) != core::idx(h)) return false;

                if (!hh.edge) return false;
                const index_t eid = core::idx(hh.edge);
                if (eid < 0) return false;
                if (static_cast<std::size_t>(eid) >= edges_.size()) return false;
            }

            // Edge checks
            for (std::size_t i = 0; i < edges_.size(); ++i) {
                const EdgeHandle eh{static_cast<index_t>(i)};
                const Edge2D& e = edges_[i];

                if (!e.h0 || !e.h1) return false;

                const Halfedge2D& h0 = H(e.h0);
                const Halfedge2D& h1 = H(e.h1);

                if (core::idx(h0.twin) != core::idx(e.h1)) return false;
                if (core::idx(h1.twin) != core::idx(e.h0)) return false;

                if (core::idx(h0.edge) != core::idx(eh)) return false;
                if (core::idx(h1.edge) != core::idx(eh)) return false;
            }
            return true;
        }

    private:
        // ------------------------------------------------------------------------
        // Internals
        // ------------------------------------------------------------------------

        /**
         * @brief Build undirected LUT key from vertex pair (sorted).
         *
         * Ensures a unique key for edge(u, v) and edge (v, u).
         */
        static std::uint64_t key_of(const VertexHandle u, const VertexHandle v) {
            const auto a = static_cast<std::uint32_t>(core::idx(u));
            const auto b = static_cast<std::uint32_t>(core::idx(v));
            const std::uint32_t lo = std::min(a, b);
            const std::uint32_t hi = std::max(a, b);
            return (static_cast<std::uint64_t>(hi) << 32) | lo;
        }

        /**
         * @brief Choose deterministic representative among two twins.
         *
         * Representative is the halfedge whose (from, to) has from_idx < to_idx.
         * This does not depend on faces or prev pointers.
         */
        HalfedgeHandle choose_rep(const HalfedgeHandle huv, const HalfedgeHandle hvu) const {
            const Halfedge2D& a = halfedges_[core::idx(huv)];
            const auto af = static_cast<std::uint32_t>(core::idx(a.from));
            const auto at = static_cast<std::uint32_t>(core::idx(a.to));
            if (af < at) return huv; return hvu;
        }

        /**
         * @brief Return the directed halfedge in an undirected edge that matches u -> v.
         */
        HalfedgeHandle directed_halfedge(const EdgeHandle eh, const VertexHandle u, const VertexHandle v) const {
            const Edge2D& e = E(eh);

            const Halfedge2D& h0 = H(e.h0);
            if (core::idx(h0.from) == core::idx(u) && core::idx(h0.to) == core::idx(v)) return e.h0;

            const Halfedge2D& h1 = H(e.h1);
            if (core::idx(h1.from) == core::idx(u) && core::idx(h1.to) == core::idx(v)) return e.h1;

            assert(false && "directed_halfedge: requested direction does not match stored twins.");
            return HalfedgeHandle{};
        }
    private:
        std::vector<Vertex2D>   vertices_;
        std::vector<Halfedge2D> halfedges_;
        std::vector<Edge2D>     edges_;
        std::vector<Face2D>     faces_;

        // undirected edge LUT: key(u,v) -> edge id
        std::unordered_map<std::uint64_t, EdgeHandle> edge_lut_;
    };
}
#endif //TONB_MESH_AFT2D_TOPOLOGY_HXX
//
// Created by amir on 5/7/26.
//
/**
 * @file edge.hxx
 * @brief Declares the Edge class, the first-class owner of a twin half-edge pair
 *        in the cad2d topology layer.
 *
 * The cad2d topology model continues to use topo::HalfEdge as the directed
 * traversal primitive for wires and faces. This file introduces topo::Edge as a
 * stronger identity and ownership abstraction above the incidental twin
 * relationship stored directly on individual half-edges.
 *
 * Design intent
 * -------------
 * A topological undirected edge should exist as a first-class object even when
 * the model is traversed through directed half-edges. The Edge class therefore
 * groups the two opposite half-edges that represent the same underlying
 * topological edge and provides a stable identity for that pair.
 *
 * Responsibilities of Edge
 * ------------------------
 * - own the concept of the half-edge pair via forward/reverse references,
 * - provide a stable identity distinct from either child half-edge id,
 * - enable validators to treat edge invariants as stronger than ad hoc
 *   half-edge twin symmetry,
 * - support future algorithms that need explicit edge identity without scanning
 *   or inferring pairs from half-edge links.
 *
 * Important scope note
 * --------------------
 * Edge does not duplicate the detailed directed state that already belongs to
 * topo::HalfEdge. In particular, start/end vertices, local parameter range,
 * next/prev links, and left-face adjacency remain properties of the half-edge.
 * Edge only stores the pairing relation.
 */
#pragma once
#ifndef TONB_CAD2D_TOPO_EDGE_HXX
#define TONB_CAD2D_TOPO_EDGE_HXX

#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/module.hxx>

#include <memory>

namespace tonb::cad2d::topo {

    class HalfEdge;

    /**
     * @class Edge
     * @brief First-class owner of a forward/reverse half-edge pair.
     *
     * Edge stores non-owning references to the two directed half-edges that form
     * a single undirected topological edge. Lifetime is controlled by the owning
     * topo::Shape, which stores both the Edge object itself and the HalfEdge
     * objects referenced here.
     *
     * Invariants expected by builders and validators:
     * - forward() and reverse() refer to distinct half-edge objects,
     * - both half-edges point back to this Edge through HalfEdge::edge(),
     * - the two half-edges are twins of one another,
     * - they share the same curve id and opposite orientation,
     * - they represent opposite directions of the same endpoint pair.
     */
    class Edge {
    public:
        /// @name Construction
        /// @{

        /**
         * @brief Default constructor creating an empty edge with id = 0.
         */
        Edge() = default;

        /**
         * @brief Construct an edge with a stable identifier.
         * @param id Stable unique identifier within the owning shape.
         */
        explicit Edge(const Id id) noexcept : id_(id) {}

        /// @}

        /// @name Identity
        /// @{

        /**
         * @brief Return the stable unique identifier of this edge.
         */
        TNB_NODISCARD Id id() const noexcept { return id_; }

        /// @}

        /// @name Half-edge access
        /// @{

        /**
         * @brief Return the designated forward half-edge.
         *
         * The term "forward" here is purely the stored slot name for one member of
         * the pair. It does not impose any global geometric convention.
         */
        TNB_NODISCARD std::shared_ptr<HalfEdge> forward() const noexcept { return forward_.lock(); }

        /**
         * @brief Return the designated reverse half-edge.
         */
        TNB_NODISCARD std::shared_ptr<HalfEdge> reverse() const noexcept { return reverse_.lock(); }

        /**
         * @brief Store the forward half-edge reference.
         * @param e Non-owning reference to the forward half-edge.
         */
        void set_forward(std::weak_ptr<HalfEdge> e) noexcept { forward_ = std::move(e); }

        /**
         * @brief Store the reverse half-edge reference.
         * @param e Non-owning reference to the reverse half-edge.
         */
        void set_reverse(std::weak_ptr<HalfEdge> e) noexcept { reverse_ = std::move(e); }

        /**
         * @brief Return true if both half-edge slots currently resolve.
         */
        TNB_NODISCARD bool has_valid_pair() const noexcept {
            return !forward_.expired() && !reverse_.expired();
        }

        /// @}

    private:
        Id id_{0};
        std::weak_ptr<HalfEdge> forward_;
        std::weak_ptr<HalfEdge> reverse_;
    };
}

#endif // TONB_CAD2D_TOPO_EDGE_HXX

//
// Created by amir on 1/21/26.
//
/**
 * @file wire.hxx
 * @brief Declares the Wire class for the cad2d topology layer.
 *
 * A Wire represents an ordered boundary chain of half-edges. It is used as a
 * building block for faces, where one wire defines the outer boundary and
 * optional additional wires define inner holes.
 *
 * This header is part of the pure topology layer:
 *  - It contains no OCCT types and no geometry kernel dependencies.
 *  - It does not perform geometric intersection tests.
 *  - It focuses on connectivity, ordering, and basic topological consistency.
 *
 * Ownership model:
 *  - Wires do not own half-edges. The owning shape (or model) owns all entities.
 *  - The wire stores non-owning references to half-edges using std::weak_ptr.
 */
#pragma once
#ifndef TONB_CAD2D_TOPO_WIRE_HXX
#define TONB_CAD2D_TOPO_WIRE_HXX

#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/module.hxx>

#include <vector>
#include <memory>
/**
 * @class Wire
 * @brief Ordered boundary chain of half-edges.
 *
 * A Wire is a topological entity that stores an ordered sequence of boundary
 * half-edges. The sequence is expected to request a continuous chain. It may
 * be open (for sketch or partial boundaries) or closed (for face boundaries).
 *
 * The Wire class does not require that each half-edge has next or prev pointers
 * set, because the wire itself provides an explicit boundary ordering. However,
 * if next or prev are also set, they should be consistent with the wire order.
 *
 * Invariants (intended, enforced by builders and validators):
 *  - Wire id is stable and immutable after construction.
 *  - Each stored half-edge reference is either valid or may expire, but must
 *    never be a dangling raw pointer.
 *  - A closed wire forms a loop where each edge end vertex matches the next
 *    edge star vertex within a provided tolerance.
 *
 * Notes:
 *  - This class provides basic consistency checks that rely only on vertex
 *    positions and tolerance. More advanced checks, such as self-intersection,
 *    belong in the algorithm and validation layers.
 */
namespace tonb::cad2d::topo {
    class HalfEdge;
    class Wire {
    public:
        /// @name Constructors
        /// @{

        /**
         * @brief Default constructor. Creates an empty wire with id = 0.
         */
        Wire() = default;

        /**
         * @brief Construct a wire with a stable id.
         * @param id Stable unique identifier within the owning shape.
         */
        explicit Wire(const Id id) noexcept : id_{id} {}

        /// @}

        /// @name Identity
        /// @{

        /**
         * @brief Return the unique identifier of this wire.
         */
        TNB_NODISCARD Id id() const noexcept { return id_;}

        /// @}

        /// @name Boundary access
        /// @{

        /**
         * @brief Return the number of half-edges in the boundary sequence.
         */
        TNB_NODISCARD size_t size() const noexcept {return boundary_.size();}

        /**
         * @brief Return true if the wire boundary sequence is empty.
         */
        TNB_NODISCARD bool empty() const noexcept {return boundary_.empty();}

        /**
         * @brief Return the boundary half-edge at index i as a shared pointer.
         *
         * This method locks the internal weak pointer. It may return nullptr if the
         * referenced half-edge has expired.
         *
         * @param i Boundary index.
         * @return Shared pointer to the i-th half-edge, or nullptr if expired.
         * @throws std::out_of_range if i is out of range.
         */
        TNB_NODISCARD std::shared_ptr<HalfEdge> edge(const size_t i) const {
            return boundary_.at(i).lock();
        }

        /**
         * @brief Return a snapshot of all boundary half-edges as hared pointers.
         *
         * Any expired entries are returned as nullptr. This is useful for debug dumps
         * and validators that want a stable list of handles.
         */
        TNBCAD2D_ND_EXPORT std::vector<std::shared_ptr<HalfEdge>> edges_locked() const;

        /// @}

        /// @name Builder-facing mutation
        /// @{

        /**
         * @brief Replace the wire boundary sequence.
         *
         * This function is intended to be called by builders or editors that construct
         * wires. The wire stores non-owning references; therefore, the caller must
         * ensure the owning shape keeps the half-edges alive.
         *
         * @param edges Ordered boundary half-edges.
         */
        void set_boundary(std::vector<std::weak_ptr<HalfEdge>> edges) {
            boundary_ = std::move(edges);
        }

        /**
         * @brief Append one boundary half-edge reference to the end of the sequence.
         *
         * This is a convenience for incremental builders. It does not validate
         * continuity. Validation should be done by the builder or validator.
         *
         * @param edge Half-edge reference to append.
         */
        void push_back(const std::weak_ptr<HalfEdge>& edge) {
            boundary_.push_back(edge);
        }

        /**
         * @brief Clear the boundary sequence.
         *
         * This does not delete half-edges. It only removes references from the wire.
         */
        void clear() noexcept { boundary_.clear(); }

        /// @}

        /// @name Topological checks
        /// @{

        /**
         * @brief Check whether the wire is closed within a tolerance.
         *
         * A wire is considered closed if:
         *  - it has at least one edge, and
         *  - for every consecutive pair (ei, e(i+1)), end(ei) matches start(e(i+1))
         *    within tolerance, and
         *  - end(last) matches start(first) within tolerance.
         *
         * This check is purely topological and uses vertex positions and tolerance.
         * It does not test for self-intersection or geometric validity.
         *
         * @param tol Tolerance policy for comparing vertex positions.
         * @return Result<void> success if closed; otherwise a descriptive error.
         */
        TNBCAD2D_ND_EXPORT Result<void> check_closed(const Tolerance& tol) const;

        /**
         * @brief Check whether consecutive edges form a continuous chain.
         *
         * This is similar to @ref check_closed but does not require the last edge to
         * connect to the first edge. It is useful for open sketch chains.
         *
         * @param tol Tolerance policy for comparing vertex positions.
         * @return Result<void> success fi continuous; otherwise a descriptive error.
         */
        TNBCAD2D_ND_EXPORT Result<void> check_continuous(const Tolerance& tol) const;
    private:
        Id id_{0}; ///< Stable identity key for this wire
        std::vector<std::weak_ptr<HalfEdge>> boundary_; ///< Ordered boundary half-edges
    };
}
#endif //TONB_CAD2D_TOPO_WIRE_HXX
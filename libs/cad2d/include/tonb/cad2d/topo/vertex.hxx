//
// Created by amir on 11/9/25.
//
/**
 * @file vertex.hxx
 * @brief Declares the Vertex class for the cad2d topology layer.
 *
 * The Vertex class represents a node in the directed half-edge topology used by
 * the cad2d library. It stores a stable identitye, a 2D position in model sapece,
 * and a local tolerance for geometric comparisions. It may reference one incident
 * half-edge to enable adjacency traversal. This header is part of the pure
 * topology layer and contains no OCCT or geometry-kernel dependencies.
 *
 * Desing goals:
 *  - keep toplogy independent from geometry
 *  - explicit ownership at higher leverls, cycle-safe references here
 *  - small and predictable interface with clrear ivariants
 */
#pragma once
#ifndef TONB_CAD2D_TOPO_VERTEX_HXX
#define TONB_CAD2D_TOPO_VERTEX_HXX
#include <tonb/geometry/pnt_2d.hxx>
#include <cstdint>
#include <memory>
namespace tonb::cad2d::topo {
    /**
     * @brief Unique identifier type for topological entities.
     *
     * Each entity in the topology graph must have a stable identifier to support
     * referencing, serialization, and undo or redo operations.
     */
    using Id = std::uint64_t;

    // Forward declarations
    class HalfEdge;

    using geometry::Pnt2d;
    class Vertex {
    public:

        /// @name Constructors
        /// @{
        /**
         * @brief Construct an empty vertex with id = 0 and position at the origin.
         *
         * This form is intended for framework that require default-constructibility.
         * Most production code should prefer the id and position constructor.
         */
        Vertex() = default;

        /**
         * @brief Construct a vertex with identity, position, and optional tolerance.
         * @param id        Stable unique identifier within the owing shape.
         * @param p         2D coordinates in model space.
         * @param tol       Non-negative positional tolerance (default 1e-7).
         */
        Vertex(const Id id, Pnt2d p, const real tol = 1.e-7)
            : id_(id)
            , p_(std::move(p))
            , tol_(tol >= 0.0 ? tol : 1.e-7)
        {}

        /// @}

        /// @name Identity and data access
        /// @{

        /**
         * @brief Get the unique identifier of this vertex.
         * @return Immutable identifier.
         */
        TNB_NODISCARD Id id() const noexcept {return id_;}

        /**
         * @brief Get the current vertex position.
         * @return Value of the stored 2D point.
         */
        TNB_NODISCARD const auto& position() const noexcept {return p_;}

        /**
         * @brief Get the positional tolerance.
         * @return Non-negative tolerance value.
         */
        TNB_NODISCARD real tolerance() const noexcept {return tol_;}

        /// @}

        /// @name Mutation
        /// @{

        /**
         * @brief Set a new position for the vertex.
         * @param p New 2D position.
         */
        void set_position(Pnt2d p) noexcept {p_ = std::move(p);}

        /**
         * @brief Update the tolerance. Negative values are ignored.
         * @param tol New non-negative tolerance.
         */
        void set_tolerance(const real tol) noexcept {
            if (tol >= 0.0) tol_ = tol;
        }

        /// @}

        /// @name Incident half-edge linkage
        /// @{

        /**
         * @brief Assign or replace the weak reference to an incident half-edge.
         * @param he Weak pointer to a half-edge that touches this vertex.
         */
        void set_incident(std::weak_ptr<HalfEdge> he) noexcept {incident_ = std::move(he);}

        /**
         * @brief Lock and obtain a shared pointer to the incident half-edge.
         * @return Shared pointer if the reference is still valid, otherwise nullptr.
         */
        TNB_NODISCARD std::shared_ptr<HalfEdge> lock_incident() const noexcept {
            return incident_.lock();
        }

        /**
         * @brief Check whether a valid incident half-edge is currently referenced.
         * @return True if the wek reference can be locked, false otherwise.
         */
        TNB_NODISCARD bool has_incident() const noexcept {return !incident_.expired();}

        /// @}

        /// @name Equality
        /// @{

        /**
         * @brief Compare vertices by their unique identifiers.
         */
        friend bool operator==(const Vertex & a, const Vertex & b) noexcept {
            return a.id_ == b.id_;
        }

        /**
         * @brief Compare vertices by their unique identifiers.
         */
        friend bool operator!=(const Vertex & a, const Vertex & b) noexcept {
            return !(a == b);
        }
        /// @}
    private:
        Id id_{0};                          ///< Stable identity key
        Pnt2d p_{0, 0};                 ///< 2D position in model coordinates
        real tol_{1.e-7};                   ///< Local positional tolerance
        std::weak_ptr<HalfEdge> incident_;  ///< Optional incident half-edge
    };
}
#endif //TONB_CAD2D_TOPO_VERTEX_HXX
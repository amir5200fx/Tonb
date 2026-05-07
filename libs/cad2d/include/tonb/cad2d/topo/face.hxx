//
// Created by amir on 1/21/26.
//
/**
 * @file face.hxx
 * @brief Declares the Face class for the cad2d topology layer.
 *
 * A Face represents a bounded region in a 2D topological model. it is defined
 * by one outer boundary wire and an optional collection of inner boundary wires
 * representing holes. The Face type is part of the pure topology layer:
 *
 * - No OCCT or geometry kernel types appear in this header.
 * - No geometric intersection testing or point location is performed here.
 * - Basic integrity checks are provided to support builders and validators.
 *
 * Ownership model:
 * - The owning shape (top-level model) owns wires and faces using std::shared_prt.
 * - Face stores non-owning references to wires using std::weak_ptr to avoid cycles.
 */
#pragma once
#ifndef TONB_CAD2D_TOPO_FACE_HXX
#define TONB_CAD2D_TOPO_FACE_HXX

#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/module.hxx>

#include <vector>
#include <memory>

namespace tonb::cad2d::topo {
    class Wire;
    /**
     * @class Face
     * @brief Bounded region defined by an outer wire and optional hole wires.
     *
     * The Face class expresses the topological concept of a region. It stores a
     * weak reference to an outer boundary wire and weak references to any number of
     * hole wires. The ordering and orientation conventions for wires (e.g.
     * CCW outer, CW holes) are not enforced here because that requires geometric
     * interpretation. Those policies belong in builders and validators.
     *
     * Invariants (intended, established by builders and validators):
     * - id_ is stable and immutable after construction.
     * - outer_ references an existing wire for a valid face.
     * - holes_ contains no null references for a valid face.
     * - Each referenced wire is expected to be closed for a proper face boundary.
     *
     * A Face is also the natural target for `HalfEdge::left_face` links. A builder
     * typically assigns the same face as the left face for each half-edge along the
     * outer and hole boundaries, depending on orientation conventions.
     */
    class Face {
    public:
        /// @name Construction
        /// @{

        /**
         * @brief Default constructor. Creates an emtpy face with id = 0.
         *
         * This exists primarily for frameworks requiring default-constructibility.
         * Most production code should construct faces with explicit ids and wires.
         */
        Face() = default;

        /**
         * @brief Construct a face with a stable identity.
         * @param id Stable unique identifier within the owning shape.
         */
        explicit Face(const Id id) noexcept : id_{id} {}

        /**
         * @brief Construct a face with identity, outer wire, and optional holes.
         *
         * This constructor does not validate closure of the wires. Builders should
         * validate wire closure and overall face consistency before committing.
         *
         * @param id    Stable unique identifier.
         * @param outer Outer boundary wire.
         * @param holes Hole boundary wires (optional).
         */
        Face(const Id id, std::weak_ptr<Wire> outer, std::vector<std::weak_ptr<Wire>> holes = {})
            : id_(id)
            , outer_(std::move(outer))
            , holes_(std::move(holes)) {}

        /// @}

        /// @name Identity
        /// @{

        /**
         * @brief Return the unique identifier of this face.
         */
        TNB_NODISCARD Id id() const noexcept { return id_; }

        /// @}

        /// @name Boundary access
        /// @{

        /**
         * @brief Lock and return the outer boundary wire.
         * @return Shared pointer to the outer wire, or nullptr if expired.
         */
        TNB_NODISCARD std::shared_ptr<Wire> outer() const noexcept {return outer_.lock();}

        /**
         * @brief Lock and return the i-th hole boundary wire.
         * @param i Hole index.
         * @return Shared pointer to the hole wire, or nullptr if expired.
         * @throws std::out_of_range if i is out of range.
         */
        TNB_NODISCARD std::shared_ptr<Wire> hole(const std::size_t i) const noexcept {return holes_.at(i).lock();}

        /**
         * @brief REturn the number of hole wires referenced by this face.
         */
        TNB_NODISCARD std::size_t hole_count() const noexcept {return holes_.size();}

        /**
         * @brief Return a snapshot of all hole wires as shared pointers.
         *
         * Any expired entries are returned as nullptr.
         */
        TNBCAD2D_ND_EXPORT std::vector<std::shared_ptr<Wire>> holes_locked() const;

        /// @}

        /// @name Builder-facing mutation
        /// @{

        /**
         * @brief Set the outer boundary wire reference.
         * @param outer Outer boundary wire.
         */
        void set_outer(std::weak_ptr<Wire> outer) noexcept {outer_ = std::move(outer);}

        /**
         * @brief Replace the hole wire collection.
         * @param holes New hole collection.
         */
        void set_holes(std::vector<std::weak_ptr<Wire>> holes) {holes_ = std::move(holes);}

        /**
         * @brief Append a hole wire.
         * @param hole Hole wire to append.
         */
        void add_hole(std::weak_ptr<Wire> hole) {holes_.push_back(std::move(hole));}

        /**
         * @brief Remove all hole wires.
         */
        void clear_holes() noexcept {holes_.clear();}

        /**
         * @brief BAsic integrity check for face boundaries.
         *
         * This check is intentionally topology-only. It verifies:
         * - outer wire reference is present and not expired.
         * - hole references are present and not expired,
         * - no hole wire is the same object as the outer wire,
         * - optionally, each wire is closed within the given tolerance.
         *
         * It does not verify:
         * - wire orientation conventions (CCW/CW),
         * - wire self-intersections,
         * - holes inside outer boundary,
         * - hole-hole overlap.
         *
         * Those checks belong in higher-level validators and geometric algorithms.
         *
         * @param tol Tolerance policy used for closure checks.
         * @param requireClosed If true, requires outer and hole wires to be closed.
         * @return Result<void> success if the face is topologically consistent.
         */
        TNBCAD2D_ND_EXPORT Result<void> check_basic(const Tolerance& tol, bool requireClosed = true) const;

        /// @}

        /// @name Equality
        /// @{

        /**
         * @brief Compare faces by unique identifier.
         */
        friend bool operator==(const Face& a, const Face& b) noexcept {return a.id_ == b.id_;}

        /**
         * @brief Compare faces by unique identifier.
         */
        friend bool operator!=(const Face& a, const Face& b) noexcept {return !(a == b);}

        /// @}

    private:
        Id id_{0};  ///< Stable identity key for this face

        std::weak_ptr<Wire> outer_;                 ///< Outer boundary wire (non-owning)
        std::vector<std::weak_ptr<Wire>> holes_;    ///< Hole boundary wires (non-owning)
    };
}
#endif //TONB_CAD2D_TOPO_FACE_HXX
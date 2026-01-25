//
// Created by amir on 1/22/26.
//
/**
 * @file shape.hxx
 * @brief Declares the Shape class, the ownership root of cad2d topology.
 *
 * The Shape class is the top-level container that owns all topological entities
 * of a 2D model: vertices, half-edges, wires, and faces. It is part of the pure
 * topology layer and intentionally has no dependency on OCCT or any geometry
 * kernel. Geometry binging is handled in higher layers (builders/adapters).
 *
 * Key responsibilities:
 * - Provide stable ownership and lifetime management of entities.
 * - Provide deterministic access by Id.
 * - Provide creation helpers that allocate new entities with unique Ids.
 * - Provide basic integrity and query helpers suitable for builders/validators.
 *
 * Ownership model:
 * - Shape owns entities through std::shared_ptr.
 * - Entities link to each other through std::weak_ptr to avoid cycles.
 *
 * Notes:
 * - This class does not attempt to "snap" or deduplicate vertices. That belongs
 *   in the build layer.
 * - This class does not perform geometric checks (self-intersection, nesting).
 *   Those belong in validate/algo layers.
 */
#pragma once
#ifndef TONB_CAD2D_TOPO_SHAPE_HXX
#define TONB_CAD2D_TOPO_SHAPE_HXX

#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>
#include <tonb/cad2d/topo/orientation.hxx>
#include <tonb/cad2d/module.hxx>
#include <tonb/geometry/pnt_2d.hxx>

#include <unordered_map>
#include <memory>
#include <vector>

namespace tonb::cad2d::topo {

    class Vertex;
    class HalfEdge;
    class Wire;
    class Face;

    /**
     * @class Shape
     * @brief root owner and registry for cad2d topology entities.
     *
     * Shape owns and registers all topological entities. The typical workflow is:
     *  (1) Builders create vertices/edges/wires/faces via Shape factory functions.
     *  (2) Builders set cross-links (weak_ptr connections) among entities.
     *  (3) Validators operate on the resulting graph.
     *
     * The class exposes retrieval by Id, enumeration helpers, and minimal
     * existence/consistency checks.
     *
     * Invariants:
     *  - Each stored entity has a unique Id within its category.
     *  - The Id generator monotonically increasing identifiers.
     *  - Removing an entity does not automatically repair topology. Builders and
     *    editors must ensure consistency after modifications.
     *
     */
    class Shape {
    public:

        using Pnt2d = geometry::Pnt2d;

        /// @name Construction
        /// @{

        /**
         * @brief Construct an emtpy Shape with a fresh Id generator.
         *
         * The shape itself also ahs an Id. This is useful for serialisation and for
         * distinguishing multiple shapes in a scene or project.
         */
        Shape() : id_(ids_()) {}

        /**
         * @brief Construct an empty Shape with a specified identity and id counter start.
         *
         * This is primarily intended for deserialisation scenarios where entity Ids
         * are known and the geenerator must be reset accordingly.
         *
         * @param shapeId Stable identifier for this Shape.
         * @param idStart Initial value for the internal Id generator counter. The next issued Id is idStart + 1.
         */
        explicit Shape(const Id shapeId, const Id idStart = 0) : id_(shapeId), ids_(idStart) {}

        /// @}

        /// @name Identity
        /// @{

        /**
         * @brief Get the shape id.
         */
        Id id() const noexcept {return id_;}

        /// @}

        /// @name Entity counts
        /// @{

        std::size_t vertex_count() const noexcept {return vertices_.size();}
        std::size_t halfedge_count() const noexcept {return halfedges_.size();}
        std::size_t wire_count() const noexcept {return wires_.size();}
        std::size_t face_count() const noexcept {return faces_.size();}

        /// @}

        /// @name Creation helpers
        /// @{

        /**
         * @brief Create and register a new Vertex.
         *
         * The created vertex is owned by this Shape and can be retrieved by Id.
         *
         * @param position Vertex position in model space.
         * @param tol Per-vertex positional tolerance.
         * @return Shared pointer to the newly created vertex.
         */
        TNBCAD2D_ND_EXPORT std::shared_ptr<Vertex> make_vertex(Pnt2d position, double tol = 1.e-7);

        /**
         * @brief Create and register a new Halfedge.
         *
         * The created half-edge initially has no connectivity links set.
         *
         * @param curveId Opaque curve identifier used by higher layers for geometry binding.
         * @param u0 Start parameter along ghe curve segment.
         * @param u1 End parameter along the curve segment.
         * @param dir Traversal orientation along the curve segment.
         * @param tol Local tolerance for this edge.
         * @return Shared pointer to the newly created half-edge.
         */
        TNBCAD2D_ND_EXPORT std::shared_ptr<HalfEdge> make_halfedge(Id curveId, double u0, double u1, Orientation dir, double tol = 1.e-9);

        /**
         * @brief Create and register a new wire.
         *
         * @return Shared pointer to the newly created wire.
         */
        TNBCAD2D_ND_EXPORT std::shared_ptr<Wire> make_wire();

        /**
         * @brief Create and register a new Face.
         *
         * @return Shared pointer to the newly created face.
         */
        TNBCAD2D_ND_EXPORT std::shared_ptr<Face> make_face();

        /// @}

        /// @name Retrieval by Id
        /// @{

        /**
         * @brief Get a Vertex by Id.
         * @return Shared pointer if found, otherwise nullptr.
         */
        TNBCAD2D_ND_EXPORT std::shared_ptr<Vertex> vertex(Id id) const noexcept;

        /**
         * @brief Get a HalfEdge by Id.
         * @return Shared pointer if found, otherwise nullptr.
         */
        TNBCAD2D_ND_EXPORT std::shared_ptr<HalfEdge> halfedge(Id id) const noexcept;

        /**
         * @brief Get a wire by Id.
         * @return Shared pointer if found, otherwise nullptr.
         */
        TNBCAD2D_ND_EXPORT std::shared_ptr<Wire> wire(Id id) const noexcept;

        /**
         * @brief Get a Face by Id.
         * @return Shared pointer if found, otherwise nullptr.
         */
        TNBCAD2D_ND_EXPORT std::shared_ptr<Face> face(Id id) const noexcept;

        /// @}

        /// @name Enumeration helpers
        /// @{

        /**
         * @brief Return a snapshot list of all vertices.
         */
        TNBCAD2D_ND_EXPORT std::vector<std::shared_ptr<Vertex>> vertices() const;

        /**
         * @brief Return a snapshot list of all half-edges.
         */
        TNBCAD2D_ND_EXPORT std::vector<std::shared_ptr<HalfEdge>> halfedges() const;

        /**
         * @brief Return a snapshot list of all wires.
         */
        TNBCAD2D_ND_EXPORT std::vector<std::shared_ptr<Wire>> wires() const;

        /**
         * @brief Return a snapshot list of all faces.
         */
        TNBCAD2D_ND_EXPORT std::vector<std::shared_ptr<Face>> faces() const;

        /// @}

        /// @name Removal helpers
        /// @{

        /**
         * @brief Remove a vertex from the registry.
         *
         * This does not repair topology. Any existing weak references to the removed
         * vertex will subsequently expire. builders/editors must ensure consistency.
         *
         * @param id Vertex identifier.
         * @return True if removed, false if not found.
         */
        TNBCAD2D_ND_EXPORT bool erase_vertex(Id id) noexcept;

        /**
         * @brief Remove a half-edge from the registry.
         * @param id Half-edge identifier.
         * @return True if removed, false if not found.
         */
        TNBCAD2D_ND_EXPORT bool erase_halfedge(Id id) noexcept;

        /**
         * @brief Remove a wire from the registry.
         * @param id Face identifier.
         * @return True if removed, false if not found.
         */
        TNBCAD2D_ND_EXPORT bool erase_wire(Id id) noexcept;

        /**
         * @brief Remove a face from the registry.
         * @param id Face identifier.
         * @return True if removed, false if not found.
         */
        TNBCAD2D_ND_EXPORT bool erase_face(Id id) noexcept;

        /// @}

        /// @name Basic validation entry points
        /// @{

        /**
         * @brief Perform a lightweight topology sanity check.
         *
         * This check is intentionally minimal. It verifies that:
         *  - All stored shared_ptr entries are non-null.
         *  - Face boundaries pass Face::check_basic with the provided tolerance policy.
         *
         * This does not validate:
         *  - edge twin/next/prev consistency
         *  - manifoldness
         *  - wire self-intersection or face nesting
         *
         * @param tol Tolerance policy used for face boundary closure checks.
         * @param requireClosed If tur, requires face wires to be closed.
         * @return Result<void> success if basic checks pass.
         */
        TNBCAD2D_ND_EXPORT Result<void> check_basic(const Tolerance& tol, bool requireClosed = true) const;

        /// @}

        /// @name Id generator control
        /// @{

        /**
         * @brief Return th ecurrent internal Id counter.
         *
         * Useful for serialisation and deterministic debugging.
         */
        TNB_NODISCARD Id current_id_counter() const noexcept {return ids_.current();}

        /**
         * @brief Reset the internal Id generator counter.
         *
         * Intended primarily for deserialisation or controlled test scenarios.
         * The next issued Id will be start + 1.
         *
         * @param start New starting counter value.
         */
        void reset_id_counter(const Id start) noexcept {ids_.reset(start);}

    private:
        Id id_{0};
        IdGenerator ids_{0};

        std::unordered_map<Id, std::shared_ptr<Vertex>> vertices_;
        std::unordered_map<Id, std::shared_ptr<HalfEdge>> halfedges_;
        std::unordered_map<Id, std::shared_ptr<Wire>> wires_;
        std::unordered_map<Id, std::shared_ptr<Face>> faces_;
    };
}
#endif //TONB_CAD2D_TOPO_SHAPE_HXX
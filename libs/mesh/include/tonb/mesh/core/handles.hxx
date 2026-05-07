//
// Created by amir on 11/7/25.
//
#pragma once
#ifndef TONB_MESH_CORE_HANDLES_HXX
#define TONB_MESH_CORE_HANDLES_HXX
#include <tonb/base/module.hxx>
#include <tonb/base/index_types.hxx>

#include <iostream>
#include <limits>
namespace tonb::mesh::core {

    using base::npos;
    /**
     * @brief Utility function to test if an index is valid.
     *
     * @param i Index value to check.
     * @return True if the index is non-negative (valid).
     */
    constexpr inline bool is_valid(const index_t i) noexcept {return i >= 0;}

    /**
     * @struct HandleBase
     * @brief CRTP base struct providing shared logic for handle types.
     *
     * All Tonb handle types inherit from `HandleBase<Derived>` to share common
     * functionality like comparisons, validity checks, and conversions, without
     * introducing polymorphic overhead or runtime cost.
     *
     * @tparam Derived The concrete handle type (e.g. `VertexHandle`).
     */
    template<class Derived>
    struct HandleBase {
        index_t i = npos;   ///< Stored index value. -1 indicates invalid

        /// @name Construction
        /// @{

        /// Default from a raw index.
        constexpr HandleBase() noexcept = default;

        /// Construct from a raw index.
        explicit constexpr HandleBase(const index_t idx) noexcept : i(idx) {}

        /// @}

        /// @name Validity and access
        /// @{

        /// Returns true if the handle refers to a valid element.
        TNB_NODISCARD constexpr bool valid() const noexcept {return is_valid(i);}

        /// Implicit bool conversion - allows `if (handle) {...}` style usage.
        explicit constexpr operator bool() const noexcept {return valid();}

        /// Returns the raw index value.
        TNB_NODISCARD constexpr index_t idx() const noexcept {return i;}

        /// Resets the handle to an invalid state.
        void reset() noexcept {i = npos;}

        /// @}

        /// @name Comparisons
        /// @{
        friend constexpr bool operator==(const HandleBase a, const HandleBase b) noexcept {return a.i == b.i;}
        friend constexpr bool operator!=(const HandleBase a, const HandleBase b) noexcept {return a.i != b.i;}
        friend constexpr bool operator<(const HandleBase a, const HandleBase b) noexcept {return a.i < b.i;}
        friend constexpr bool operator>(const HandleBase a, const HandleBase b) noexcept {return a.i > b.i;}
        friend constexpr bool operator<=(const HandleBase a, const HandleBase b) noexcept {return a.i <= b.i;}
        friend constexpr bool operator>=(const HandleBase a, const HandleBase b) noexcept {return a.i >= b.i;}
        /// @}
    };

    // ============================================================================
    //  Concrete Handle Types
    // ============================================================================

    /**
     * @struct VertexHandle
     * @brief Identifier for a vertex element in the mesh.
     */
    struct VertexHandle : HandleBase<VertexHandle> {using HandleBase::HandleBase;};

    /**
     * @struct EdgeHandle
     * @brief Indentifier for an edge element (connects two vertices).
     */
    struct EdgeHandle : HandleBase<EdgeHandle> {using HandleBase::HandleBase;};

    /**
     * @struct HalfedgeHandle
     * @brief Identifier for a directed edge (used in surface meshes).
     *
     * Each edge is represented by two halfedges pointing in opposite directions.
     * Halfedges are the foundation of the halfedge mesh data structure, enabling
     * fast traversal of adjacency relationships.
     */
    struct HalfedgeHandle: HandleBase<HalfedgeHandle> {using HandleBase::HandleBase;};

    /**
     * @struct FaceHandle
     * @brief Identifier for a polygonal face in a surface mesh.
     */
    struct FaceHandle : HandleBase<FaceHandle> {using HandleBase::HandleBase;};

    /**
     * @struct HalffaceHandle
     * @brief Identifier for a directed face (used in volume meshes).
     *
     * Each face in a 3D mesh has one or two halffaces depending on whether it is a
     * boundary or shared between two cells. This enables consistent traversal of
     * cell adjacency in volumetric meshes.
     */
    struct HalffaceHandle : HandleBase<HalffaceHandle> {using HandleBase::HandleBase;};

    /**
     * @struct CellHandle
     * @brief Identifier for a volumetric cell (e.g. tetrahedron, hexahedron).
     */
    struct CellHandle : HandleBase<CellHandle> {using HandleBase::HandleBase;};

    // ============================================================================
    //  Free helper functions
    // ============================================================================

    /// @name Accessors
    /// @brief Convenience functions for consistent API naming
    /// @{
    constexpr inline index_t idx(const VertexHandle h) noexcept {return h.idx();}
    constexpr inline index_t idx(const EdgeHandle h) noexcept {return h.idx();}
    constexpr inline index_t idx(const HalfedgeHandle h) noexcept {return h.idx();}
    constexpr inline index_t idx(const FaceHandle h) noexcept {return h.idx();}
    constexpr inline index_t idx(const HalffaceHandle h) noexcept {return h.idx();}
    constexpr inline index_t idx(const CellHandle h) noexcept {return h.idx();}
    /// @}

    /// @name Validity helpers
    /// @{
    constexpr inline bool is_valid(const VertexHandle h) noexcept {return h.valid();}
    constexpr inline bool is_valid(const EdgeHandle h) noexcept {return h.valid();}
    constexpr inline bool is_valid(const HalfedgeHandle h) noexcept {return h.valid();}
    constexpr inline bool is_valid(const FaceHandle h) noexcept {return h.valid();}
    constexpr inline bool is_valid(const HalffaceHandle h) noexcept {return h.valid();}
    constexpr inline bool is_valid(const CellHandle h) noexcept {return h.valid();}
    /// @}

    // ============================================================================
    //  Stream output
    // ============================================================================

    inline std::ostream& operator<<(std::ostream& os, const VertexHandle h) {return os << "v(" << h.idx() << ")";}
    inline std::ostream& operator<<(std::ostream& os, const EdgeHandle h) {return os << "e(" << h.idx() << ")";}
    inline std::ostream& operator<<(std::ostream& os, const HalfedgeHandle h) {return os << "he(" << h.idx() << ")";}
    inline std::ostream& operator<<(std::ostream& os, const FaceHandle h) {return os << "f(" << h.idx() << ")";}
    inline std::ostream& operator<<(std::ostream& os, const HalffaceHandle h) {return os << "hf(" << h.idx() << ")";}
    inline std::ostream& operator<<(std::ostream& os, const CellHandle h) {return os << "c(" << h.idx() << ")";}

    // ============================================================================
    //  Hash specialisations
    // ============================================================================
}

/**
 * @brief Enables Tonb handle types to be used as keys in `std::unordered_map` or `std::unordered_set`.
 */
template<> struct std::hash<tonb::mesh::core::VertexHandle> {
    std::size_t operator()(const tonb::mesh::core::VertexHandle h) const noexcept {return std::hash<tonb::index_t>{}(h.idx());}
};
template<> struct std::hash<tonb::mesh::core::HalfedgeHandle> {
    std::size_t operator()(const tonb::mesh::core::HalfedgeHandle h) const noexcept {return std::hash<tonb::index_t>{}(h.idx());}
};
template<> struct std::hash<tonb::mesh::core::EdgeHandle> {
    std::size_t operator()(const tonb::mesh::core::EdgeHandle h) const noexcept {return std::hash<tonb::index_t>{}(h.idx());}
};
template<> struct std::hash<tonb::mesh::core::FaceHandle> {
    std::size_t operator()(const tonb::mesh::core::FaceHandle h) const noexcept {return std::hash<tonb::index_t>{}(h.idx());}
};
template<> struct std::hash<tonb::mesh::core::HalffaceHandle> {
    std::size_t operator()(const tonb::mesh::core::HalffaceHandle h) const noexcept {return std::hash<tonb::index_t>{}(h.idx());}
};
template<> struct std::hash<tonb::mesh::core::CellHandle> {
    std::size_t operator()(const tonb::mesh::core::CellHandle h) const noexcept {return std::hash<tonb::index_t>{}(h.idx());}
};
#endif //TONB_MESH_CORE_HANDLES_HXX
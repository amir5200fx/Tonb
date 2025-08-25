//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_CONNECTIVITY_HXX
#define TONB_GEOMETRY_META_CONNECTIVITY_HXX
/**
 * @file
 * @brief Compact container of mesh element node indices.
 *
 * `Connectivity` stores the node indices that define a topological element
 * (e.g., edge, triangle, quad, tetra, hexa). The type is a lightweight,
 * value-semantics container designed to interoperate with STL algorithms and
 * tonb mesh utilities.
 *
 * ## Semantics
 * - Holds integer node IDs that index into an external vertex array.
 * - Indices are assumed **0-based** unless explicitly documented otherwise.
 * - Degenerate elements (duplicate IDs) are permitted; use @ref is_unique()
 *   if you need to reject them.
 *
 * ## Typical usage
 * @code
 * std::vector<Connectivity> tris;
 * tris.emplace_back(Connectivity{0, 1, 2});
 * tris.emplace_back(Connectivity{2, 3, 0});
 *
 */

#include <tonb/geometry/module.hxx>
#include <array>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <array>
#include <type_traits>

namespace tonb::geometry::meta {

    using Id = std::size_t;

    // tags
    struct FaceTag {enum {dim = 2};};
    struct CellTag {enum {dim = 3};};

    template<std::size_t N, class Tag = void>
    class Connectivity {
    public:
        using Array = std::array<std::size_t, N>;
    private:
        /*Private Data*/

        Array components_;

    public:

        // default constructor
        constexpr Connectivity() noexcept = default;
        explicit Connectivity(const Array & cmpts) noexcept : components_(cmpts) {}

        // Access
        TNB_NODISCARD constexpr std::size_t size() const noexcept {return components_.size();}
        TNB_NODISCARD constexpr auto operator[](const std::size_t i) const noexcept {return components_[i];}
        constexpr auto& operator[](const std::size_t i) noexcept {return components_[i];}

        TNB_NODISCARD constexpr const auto& components() const noexcept {return components_;}
        constexpr auto& components() noexcept {return components_;}

        TNB_NODISCARD constexpr bool contains(const std::size_t i) const noexcept {
            for (auto x : components_) if (x == i) { return true; } return false;
        }
        void reverse();
        TNBGEOM_ND_EXPORT Connectivity reversed() const noexcept;

        friend constexpr bool operator==(const Connectivity & lhs, const Connectivity & rhs) = default;
    };

    namespace detail {
        using Edge = Connectivity<2>;
        using Tri = Connectivity<3>;
        using Quad = Connectivity<4>;
        using Tet = Connectivity<4, CellTag>;
        using Hexa6 = Connectivity<6>;
        using Octet = Connectivity<8>;

        TNBGEOM_ND_EXPORT std::vector<Edge> make_edges(std::size_t n);
        TNBGEOM_ND_EXPORT std::vector<Edge> make_chain_edges(std::size_t n, bool close_option = false);
    }

    TNBGEOM_ND_EXPORT detail::Tri promote(const detail::Edge&);
    TNBGEOM_ND_EXPORT detail::Quad promote(const detail::Tri&);
    TNBGEOM_ND_EXPORT detail::Hexa6 promote(const detail::Quad&);

    template<std::size_t N, class Tag>
    TNB_NODISCARD std::size_t find_max_id(const std::vector<Connectivity<N, Tag>>& components);

    template<std::size_t N, class Tag>
    TNB_NODISCARD std::vector<Connectivity<N, Tag> > merge(const std::vector<Connectivity<N, Tag> > &components1,
                                                           const std::vector<Connectivity<N, Tag> > &components2);
}
#include <tonb/geometry/meta/connectivity_i.hxx>
#endif //TONB_GEOMETRY_META_CONNECTIVITY_HXX
//
// Created by amir on 8/22/25.
//
#pragma once
#ifndef TONB_INDEX_TYPES_HXX
#define TONB_INDEX_TYPES_HXX
/** @file
 * @brief Central definitions of integer types for indices, counts, and sizes.
 *
 * \par Purpose
 * Keep the choice of 32-bit or 64-bit indices behind one header so the whole
 * codebase can switch width in a controlled way.
 *
 * \par Overview
 * \li \c index_t  — signed type for mesh and geometry indices. Defaults to 32-bit
 *     for memory efficiency and cache locality. Define \c MYLIB_INDEX_64 to
 *     switch to 64-bit when arrays can exceed about 2.1e9.
 * \li \c uindex_t — unsigned counterpart, useful for bit operations or hashing.
 * \li \c npos     — sentinel representing “no index”. With a signed \c index_t
 *     this is \c -1 without wrapping.
 * \li \c count_t  — used for totals and byte sizes. Always 64-bit to avoid
 *     overflow in accumulations even when \c index_t is 32-bit.
 * \li \c size_type — mirrors \c std::size_t for container sizes and STL interop.
 *
 * \par Guidance
 * \li Use \c index_t for identifiers and lookups.
 * \li Use \c count_t for totals and running sums.
 * \li Record index bit width in file headers so on-disk formats remain portable.
 * \li Convert at library boundaries where third-party APIs require a different type.
 */

/** \def MYLIB_INDEX_64
 * \brief Define to make \c index_t and \c uindex_t 64-bit instead of 32-bit.
 * \details Use this when indexable containers may exceed 2,147,483,647 elements.
 */

#include <cstdint>
#include <cstddef>

namespace tonb::base {
#if defined(TONB_INDEX_64)
    /// Signed index type for elements such as vertices, faces, edges.
    using index_t = std::int64_t;
    /// Unsigned variant for bitwise work or hashing
    using uindex_t = std::uint64_t;
#else
    /// Signed index type for elements such as vertices, faces, edges.
    using index_t = std::int32_t;
    /// Unsigned variant for bitwise work or hashing
    using uindex_t = std::uint32_t;
#endif

    /** \var constexpr index_t npos
     * \brief Sentinel representing “no index”.
     * \details Always equals \c -1 so it is distinguishable from valid non-negative indices.
     */
    inline constexpr index_t npos = static_cast<index_t>(-1);

    /** \typedef count_t
     * \brief Type for totals and byte sizes used in accumulations.
     * \details Always 64-bit to minimise overflow risk, regardless of \c index_t width.
     */
    using count_t = std::int64_t;

    /** \typedef size_type
     * \brief Alias that mirrors \c std::size_t for container sizes and STL interop.
     */
    using size_type = std::size_t;
}
namespace tonb {
    using index_t = base::index_t;
    using uindex_t = base::uindex_t;

    using count_t = base::count_t;
    using size_type = base::size_type;
}
#endif //TONB_INDEX_TYPES_HXX
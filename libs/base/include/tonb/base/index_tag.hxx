//
// Created by amir on 8/22/25.
//
#pragma once
#ifndef TONB_BASE_INDEX_TAG_HXX
#define TONB_BASE_INDEX_TAG_HXX

/**
 * \brief Lightweight tag that wraps an index value.
 * \details Encapsulates a single \c index_t and uses the library sentinel
 * \c npos to represent “no index”.
 *
 * \invariant Either \c index() equals \c npos to denote “no index”, or it is a
 * non-negative valid index according to your application’s rules.
 *
 * \note The default-constructed value initialises the index to \c 0 (valid).
 *       To create an “unset” tag, assign \c npos explicitly.
 *
 * \thread_safety Acts as a value type. Concurrent reads are safe; synchronise
 * if mutating the same instance from multiple threads.
 *
 * \code{.cpp}
 * using tonb::global::IndexTag;
 * IndexTag a;                 // index == 0 (valid)
 * IndexTag b{npos};           // if npos == -1, then b.valid() == false
 * a.setIndex(42);
 * if (a.valid()) {
 *     // do something
 * }
 * \endcode
 */

#include <tonb/base/module.hxx>
#include <tonb/base/index_types.hxx>

namespace tonb::base {
    class IndexTag {
        /*Private Data*/
        index_t index_{0};
    public:
        /** \brief Default constructor. Initialises the index to \c 0. */
        IndexTag() noexcept = default;

        /** \brief Construct from a concrete index value. */
        explicit IndexTag(const index_t index) noexcept : index_(index) {}

        // Public functions and operators

        /** \brief Get the stored index value. */
        TNB_NODISCARD index_t index() const noexcept { return index_; }

        /**
         * \brief Get a modifiable reference to the stored index.
         * \warning Preserve the invariant; use \c npos to denote “no index”.
         */
        auto& index() noexcept { return index_; }

        /** \brief Check whether the tag holds a valid index. */
        TNB_NODISCARD bool valid() const noexcept { return index_ != npos; }

        TNB_NODISCARD bool operator==(const IndexTag& other) const noexcept { return index_ == other.index_; }

        /** \brief Set the stored index value. */
        void set_index(const index_t index) noexcept { index_ = index; }
    };
}
#endif //TONB_BASE_INDEX_TAG_HXX
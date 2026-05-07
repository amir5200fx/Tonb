//
// Created by amir on 11/9/25.
//
/**
 * @file id.hxx
 * @brief Defines the Id type and basic utilities for unique identification
 *        of topological entities in the cad2d library.
 *
 * Each entity in the cad2d topology (vertices, half-edges, wires, faces)
 * carries a stable and unique identifier of type @ref Id. This header also
 * provides a simple generator for sequential IDs, intended for cases where
 * deterministic and reproducible ID assignment is enough.
 *
 * Design goals:
 *  - Small and self-contained.
 *  - No dependency on external libraries.
 *  - Deterministic behavior (no random UUIDs).
 *  - Thread-safe ID generation when needed.
 *
 * Usage example:
 * @code
 * IdGenerator next_id;
 * auto id1 = next_id();
 * auto id2 = next_id();
 * // id1 = 1, id2 = 2, etc.
 * @endcode
 */
#pragma once
#ifndef TONB_CAD2D_TOPO_ID_HXX
#define TONB_CAD2D_TOPO_ID_HXX
#include <tonb/system/module.hxx>
#include <cstdint>
#include <atomic>
#include <string>
#include <sstream>

namespace tonb::cad2d::topo {

    /**
     * @typedef Id
     * @brief Alias for the integral identifier type used by all topological entities.
     *
     * Chosen as 64-bit unsigned integer to avoid collisions even in large models.
     */
    using Id = std::uint64_t;

    /**
     * @class IdGenerator
     * @brief Lightweight thread-safe sequential identifier generator.
     *
     * The IdGenerator class provides monotonically increasing identifiers starting
     * from 1 (by default). It uses an internal atomic counter to support safe use
     * across multiple threads.
     */
    class IdGenerator {
    public:

        /// @name Construction
        /// @{

        /**
         * @brief Construct an Id generator with an optional starting value.
         * @param start Initial counter value (default 0). The first returned Id is start + 1.
         */
        explicit IdGenerator(const Id start = 0) noexcept : counter_(start) {}

        /// @}

        /// @name Operations
        /// @{

        /**
         * @brief Generate and return the next unique Id.
         * @return Monotonically increasing 64-bit identifier.
         */
        TNB_NODISCARD Id operator()() noexcept {return ++counter_;}

        /**
         * @brief Retrieve the current counter-value without incrementing.
         * @return The most recently issued identifier (or start if none issued yet).
         */
        TNB_NODISCARD Id current() const noexcept {return counter_.load();}

        /**
         * @brief Reset the generator to a new starting value.
         * @param start New base value; the next generated Id will be start + 1.
         */
        void reset(const Id start = 0) noexcept {counter_.store(start);}

        /// @}

    private:
        std::atomic<Id> counter_;
    };

    /**
     * @brief Convert an Id to a string (for debugging, logging, or serialization).
     */
    inline std::string to_string(const Id id) {
        std::ostringstream oss; oss << id; return oss.str();
    }
}
#endif //TONB_CAD2D_TOPO_ID_HXX
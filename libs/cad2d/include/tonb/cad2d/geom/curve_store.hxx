//
// Created by amir on 1/25/26.
//
/**
 * @file curve_store.hxx
 * @brief Registry and ownership store for cad2d curve objects.
 *
 * This is the first geometry-binding component for cad2d. It provides a stable
 * id-based registry for curves so that pure topology can reference geometry
 * using only an opaque identifier.
 *
 * Architectural rule (Tonb):
 *  - cad2d/topo MUST remain geometry-kernel-free
 *  - cand2d/geom may use Tonb geometry wrappers (e.g., cad2d::Curve), but MUST NOT
 *    include OpenCASCADE headers or expose OCCT types.
 *
 * Consequently:
 *  - CurveStore stores tonb::cad2d::Curve (which is a wrapper type)
 *  - Topology half-edges store topo::Id curve_id only
 *
 * Exception policy:
 *  - add(): throws std::invalid_argument if the curve is invalid (if detectable).
 *  - get(): throws std::invalid_argument for invalid id, std::out_of_range if id not found.
 *  - contains/remove(): throw std::invalid_argument for invalid id.
 *
 * Notes:
 * - Ids are stable for the lifetime of the store.
 * - Ids are not reused after remove(). This is deliberate for debugging clarity.
 */
#pragma once
#ifndef TONB_CAD2D_GEOM_CURVE_STORE_HXX
#define TONB_CAD2D_GEOM_CURVE_STORE_HXX

#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/curve.hxx>

#include <unordered_map>

namespace tonb::cad2d::geom {

    /**
     * @brief Stores and serves cad2d curve objects behind stable ids.
     *
     * CurveStore is intentionally minimal:
     *  - It does not deduplicate curves.
     *  - It does not perform geometric equivalence checks.
     *  - It does not manage trimming; trimming is owned by topology (u0/u1 on HalfEdge).
     *
     * This separation keeps topology deterministic and makes geometry optional.
     */
    class CurveStore final {
    public:
        CurveStore() = default;
        CurveStore(const CurveStore&) = delete;
        CurveStore& operator= (const CurveStore&) = delete;
        CurveStore(CurveStore&&) = default;
        CurveStore& operator=(CurveStore&&) = default;
        ~CurveStore() = default;

        /**
         * @brief Add a curve to the store and obtain a table id.
         *
         * @param c Curve object (wrapper). Must be valid.
         * @return  Newly generated id (non-zero).
         *
         * @throws std::invalid_argument if the curve is invalid (when detectable).
         */
        topo::Id add(const cad2d::Curve& c);

        /**
         * @brief Retrieve a curve by id.
         *
         * @param id Curve id returned by add().
         * @return Reference to stored curve.
         *
         * @throws std::invalid_argument if id id invalid.
         * @throws std::out_of_range if id is not present in this store.
         */
        const Curve& get(topo::Id id) const;

        /**
         * @brief Test whether a curve id exists.
         *
         * @thros std::invalid_argument if id is invalid.
         */
        bool contains(topo::Id id) const;

        /**
         * @brief Remove a curve by id.
         *
         * @return True if removed, false if id did not exist.
         *
         * @throws std::invalid_argument if id is invalid.
         */
        bool remove(topo::Id id);

        /// @brief Remove all entries; resets the id generator to its initial state.
        void clear() noexcept;

        /// @brief Number of stored curves.
        std::size_t size() const noexcept {return curves_.size();}

    private:

        // Developer note:
        // - We treat 0 as an invalid id to mirror topology invalid constants.
        // - Using a monotonic counter provides deterministic ids in tests.
        std::uint64_t next_id_ = 1;

        // We store the wrapper by value. The wrapper itself can internally share state
        // (e.g., via shared_ptr/pimpl); copying is expected to be cheap.
        std::unordered_map<std::uint64_t, cad2d::Curve> curves_;

    private:
        static void validate_id_(topo::Id id, const char* where);
    };
}

#endif //TONB_CAD2D_GEOM_CURVE_STORE_HXX
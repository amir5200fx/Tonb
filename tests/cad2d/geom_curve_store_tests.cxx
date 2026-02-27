//
// Created by amir on 1/25/26.
//
/**
 * @file geom_curve_store_tests.cxx
 * @brief Unit tests for cad2d geometry curve store.
 *
 * These tests validate that geometry binding at cad2d level:
 *  - does not expose OCCT types
 *  - provides stable id-based storage and retrieval
 *  - supports basic wrapper operations on retrieved curves
 */

#include <gtest/gtest.h>

#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/geom/curve_ops.hxx>
#include <tonb/cad2d/tools.hxx>

#include <tonb/config.hxx>

namespace tonb::cad2d::tests {
    TEST(Cad2dGeom, CurveStoreAddGetContainsRemove) {
#if !defined(TONB_WITH_OCCT)
        GTEST_SKIP() << "TONB_WITH_OCCT is not enabled; skipping cad2d geometry tests.";
#else
        geom::CurveStore store;

        // Create a simple curve through the official cad2d API.
        // This ensures the test follows the intended architecture.
        const Curve c = cad2d::Tools::make_segment({0,0}, {1, 0});

        const topo::Id id = store.add(c);
        EXPECT_TRUE(store.contains(id));

        const auto& cref = store.get(id);

        // Basic sanity: we can query domain through wrapper ops.
        const auto[u0, u1] = geom::domain(cref);
        EXPECT_LT(u0, u1);

        // Evaluate a point (mid parameter).
        const auto pm = geom::value(cref, 0.5*(u0 + u1));
        (void)pm; // The point type is not asserted here; successful call is the main contract.

        EXPECT_TRUE(store.remove(id));
        EXPECT_FALSE(store.contains(id));

        // After removal, get() should throw
        EXPECT_THROW((void)store.get(id), std::out_of_range);
#endif
    }

    TEST(Cad2dGeom, CurveStoreRejectsInvalidId) {
        geom::CurveStore store;

        // topo::Id invalid is expected to be 0 (or equivalent). If your Id type provides
        // a constant, use that instead.
        constexpr auto bad = static_cast<topo::Id>(0);

        EXPECT_THROW((void)store.contains(bad), std::invalid_argument);
        EXPECT_THROW((void)store.remove(bad), std::invalid_argument);
        EXPECT_THROW((void)store.get(bad), std::invalid_argument);
    }
}
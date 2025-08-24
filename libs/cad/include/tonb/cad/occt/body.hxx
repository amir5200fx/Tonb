/**
 * @file
 * @brief Kernel-agnostic geometric body handle.
 *
 * The `tonb::cad::Body` class is a lightweight value handle that references a
 * backend CAD shape without exposing the kernel in public headers. Copying a
 * `Body` is cheap and shares the same underlying implementation object.
 *
 * @par Build configuration
 * If the project is built with `TONB_WITH_OCCT=ON`, `Body` is backed by an
 * OpenCascade shape stored inside a private implementation. If
 * `TONB_WITH_OCCT=OFF`, `Body` is a valid type that never references a kernel
 * object. In that case `is_valid()` returns `false` and methods such as
 * `bbox()` return empty results.
 *
 * @par Design intent
 * - Keep the core API independent of any CAD kernel.
 * - Allow optional adapters (for example, OpenCascade) to wrap native shapes
 *   and provide functionality through separate modules.
 * - Preserve value semantics so bodies can be passed and stored easily.
 *
 * @par Typical usage
 * @code
 * #include <tonb/cad/occt/core/body_helpers.hxx>
 * #include <tonb/cad/occt/body.hxx> // harmless include even when OCCT is off
 * #include <tonb/geometry/occt/BBox.hxx>
 *
 * using tonb::cad::Body;
 *
 * Body a;                          // default constructed, not valid
 * bool ok = a.is_valid();          // false when no backend data
 *
 * #if defined(TONB_WITH_OCCT)
 *   TopoDS_Shape s = /* build or read a shape * /;
 *   Body b = tonb::cad::occt::core::from_topo(s);  // wrap native shape
 *   if (b.is_valid()) {
 *     tonb::geometry::occt::BBox bb = b.bbox();          // axis-aligned bounds in model space
 *     if (!bb.empty()) {
 *       // use bb.min[] and bb.max[]
 *     }
 *   }
 * #endif
 * @endcode
 *
 * @section body_invariants Invariants
 * - Default constructed `Body` does not reference a kernel object.
 * - When OCCT is enabled, `is_valid()` returns true if and only if the
 *   underlying `TopoDS_Shape` is non-null.
 * - `bbox()` returns an empty box when the body is not valid.
 *
 * @section body_perf Performance notes
 * - Copying and moving `Body` are constant time operations.
 * - The cost of `bbox()` depends on the backend. With OCCT it is proportional
 *   to the complexity of the shape and may use existing triangulation when
 *   available.
 *
 * @section body_thread Thread safety
 * - Multiple threads may read distinct `Body` instances that share the same
 *   underlying implementation, provided no thread mutates the backend object.
 * - Construction of new bodies from native shapes and heavy modelling
 *   operations should be considered thread-hostile unless the backend
 *   explicitly documents safety.
 *
 * @section body_errors Error handling
 * - `is_valid()` is `noexcept` and never throws.
 * - `bbox()` does not throw under normal circumstances, but may allocate
 *   internally in the backend. Allocation failure can raise exceptions as per
 *   the C++ runtime.
 *
 * @see tonb::geometry::occt::BBox
 * @see tonb::cad::occt::core::from_topo
 * @see tonb::cad::occt::core::to_topo
 */

#pragma once
#ifndef TONB_CAD_OCCT_BODY_HXX
#define TONB_CAD_OCCT_BODY_HXX
#include <tonb/cad/module.hxx>
#include <memory>
#include <string>

// Forward Declarations
namespace tonb::geometry::occt {
    class BBox;
}
namespace tonb::cad::occt {
    class Body {
    public:

        using BBox = geometry::occt::BBox;

        // default constructor

        Body() noexcept = default;

        // Value semantics
        Body(const Body&) noexcept = default;
        Body(Body&&) noexcept = default;
        Body& operator=(const Body&) noexcept = default;
        Body& operator=(Body&&) noexcept = default;

        // Public functions and operators

        /**
         * @brief Reports whether this handle references a valid backend shape.
         *
         * @return `true` if the body is backed by a live kernel object.
         *         `false` for default bodies or when built without a backend.
         */
        TNBCAD_ND_EXPORT bool is_valid() const noexcept;

        TNBCAD_ND_EXPORT BBox bbox() const;

    private:
        struct Impl;
        std::shared_ptr<Impl> p_{};   // type erased backend

        // Private constructor

        explicit Body(std::shared_ptr<Impl> p) noexcept : p_(std::move(p)) {}

        // Private functions and operators

        // Friend for backend adapters to construct/extract safely
        friend struct occt_access;  // for adapters only
    };
}
#endif //TONB_CAD_OCCT_BODY_HXX
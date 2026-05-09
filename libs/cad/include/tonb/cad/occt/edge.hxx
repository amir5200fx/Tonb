#ifndef TONB_CAD_OCCT_EDGE_HXX
#define TONB_CAD_OCCT_EDGE_HXX

#include <tonb/cad/module.hxx>
#include <tonb/geometry/occt/bbox.hxx>
#include <tonb/geometry/occt/curve.hxx>

#include <array>
#include <memory>
#include <optional>
#include <utility>

/**
 * @file
 * @brief Kernel-agnostic CAD edge handle.
 *
 * `tonb::cad::Edge` wraps a backend edge (TopoDS_Edge when TONB_WITH_OCCT=ON).
 * Default-constructed edges are invalid. Public headers do not include OCCT.
 */

namespace tonb::cad::occt {

    // Forward Declarations
    namespace core {
        struct occt_edge_access;
    }
    class Edge {
    public:

        using Point3 = std::array<double, 3>;
        using BBox = geometry::occt::BBox;
        using Curve = geometry::occt::Curve;

        Edge() noexcept = default;

        // Value semantics
        Edge(const Edge&) noexcept = default;
        Edge(Edge&&) noexcept = default;
        Edge& operator=(const Edge&) noexcept = default;
        Edge& operator=(Edge&&) noexcept = default;

        // Public functions and operators

        /// True if the handle references a backend edge.
        TNBCAD_ND_EXPORT bool is_valid() const noexcept;

        /// Axis-aligned bounding box in mode space.
        TNBCAD_ND_EXPORT BBox bbox() const;

        /// Geometric length of the edge. Returns 0 on failure.
        TNBCAD_ND_EXPORT real length(real tol = 1.e-7) const;

        /// Parameter range [u0, u1] of the underlying 3D curve if bounded.
        TNBCAD_ND_EXPORT std::optional<std::pair<real, real>> parameter_range() const;

        /// Evaluate a 3D point on the edge at parameter u.
        TNBCAD_ND_EXPORT Point3 value(real u) const;

        /// Unit tangent at parameter u. Returns {0,0,0} if not available.
        TNBCAD_ND_EXPORT Point3 tangent(real u) const;

        /// Endpoints (start, end). If not available, returns {{0,0,0},{0,0,0}}
        TNBCAD_ND_EXPORT std::pair<Point3, Point3> endpoints() const;

        /// Return the underlying geometric curve as a kernel-agnostic wrapper.
        TNBCAD_ND_EXPORT Curve curve() const;

    private:

        /*Private Data*/

        struct Impl;
        std::shared_ptr<Impl> pimple_{};

        explicit Edge(std::shared_ptr<Impl> pimple) noexcept : pimple_(std::move(pimple)) {}

        friend struct core::occt_edge_access;
    };
}

#endif //TONB_CAD_OCCT_EDGE_HXX
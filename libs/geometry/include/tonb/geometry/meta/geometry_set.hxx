//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_TOPOLOGY_HXX
#define TONB_GEOMETRY_META_TOPOLOGY_HXX

/**
 * @file
 * @brief Light container tying points and element connectivities into a mesh set.
 *
 * `tonb::geometry::meta::GeometrySet<Point, IDs>` binds a point collection with
 * a collection of element connectivities (IDs). It is intended as a simple
 * carrier for geometric datasets (e.g., a 2D triangulation or 3D tet mesh)
 * without imposing a specific storage policy.
 *
 * ## Templates
 * @tparam Point  Point type for vertex positions (e.g. `Pnt2d`, `Pnt3d`).
 * @tparam IDs    Connectivity type for elements (e.g. `Connectivity<3, void>`).
 *
 * ## Semantics
 * - **Ownership/Storage**: The class holds points and element ID sets. Exact
 *   storage policy (by value / by reference / view) depends on the implementation.
 * - **Indexing**: Element connectivity refers to *zero-based* indices into the
 *   point array unless otherwise documented.
 * - **Arity**: The arity of an element (e.g., 3 for triangles) is defined by
 *   `IDs` (e.g., `Connectivity<3, void>`).
 *
 * ## Invariants
 * - Each element’s indices must be in range: `0 <= id < points_count`.
 * - No assumption is made about uniqueness or manifoldness of topology.
 *
 * ## Typical usage
 * @code
 * using tonb::geometry::Pnt2d;
 * using tonb::geometry::meta::Connectivity;
 * using tonb::geometry::meta::GeometrySet;
 *
 * GeometrySet<Pnt2d, Connectivity<3, void>> tri;
 *
 * // Pseudocode — align with your actual API:
 * tri.points().push_back(Pnt2d{0,0});
 * tri.points().push_back(Pnt2d{1,0});
 * tri.points().push_back(Pnt2d{0,1});
 *
 * tri.elements().push_back( Connectivity<3,void>{0,1,2} );
 *
 * // Validate an element against the point count (example helper):
 * // bool ok = tri.valid_element(0); // implementation dependent
 * @endcode
 *
 * ## Complexity
 * - Access to points/elements is O(1); bulk operations are linear in the number
 *   of affected items.
 *
 * ## Thread safety
 * - Read-only access from multiple threads is safe if no mutation occurs.
 * - Mutating operations require external synchronisation.
 *
 * @note See `Triangulation2d` in the forward header:
 *       `using Triangulation2d = GeometrySet<Pnt2d, Connectivity<3, void>>;`
 *
 * @see tonb::geometry::Pnt2d, tonb::geometry::Pnt3d,
 *      tonb::geometry::meta::Connectivity
 */


#include <tonb/base/precision.hxx>

#include <vector>
#include <memory>
#include <string>
#include <iosfwd>

namespace tonb::geometry::meta {

    // Forward Declarations
    template<class Point> class Box;

    template<class Point, class IDs>
    class GeometrySet {
    public:
        using PntList = std::vector<Point>;
        using IdList = std::vector<IDs>;
        using box_t = Box<Point>;

    private:

        /*Private Data*/

        PntList points_;
        IdList ids_;
        std::unique_ptr<box_t> box_{};

    public:

        using point_t = Point;

        // default constructor

        GeometrySet() noexcept = default;

        // constructors

        GeometrySet(PntList points, IdList ids,
                    std::unique_ptr<box_t> box = nullptr) noexcept : points_(std::move(points)), ids_(std::move(ids)),
                                                                     box_(std::move(box)) {
        }

        // move-only (unique ownership)
        GeometrySet(const GeometrySet& other)
            : points_(other.points_), ids_(other.ids_),
              box_(other.box_ ? std::make_unique<box_t>(*other.box_) : nullptr) {
        }
        GeometrySet(GeometrySet&& other) noexcept = default;

        // Public functions and operators

        GeometrySet& operator=(const GeometrySet& other) {
            if (this != &other) {return *this;}
            points_ = other.points_;
            ids_ = other.ids_;
            box_ = other.box_ ? std::make_unique<box_t>(*other.box_) : nullptr;
            return *this;
        }
        GeometrySet& operator=(GeometrySet&& other) noexcept = default;

        // Access

        TNB_NODISCARD size_t point_count() const noexcept {return points_.size();}
        TNB_NODISCARD size_t id_count() const noexcept {return ids_.size();}
        TNB_NODISCARD bool contains_bounding_box() const noexcept {return static_cast<bool>(box_);}

        const auto& points() const noexcept {return points_;}
        const auto& ids() const noexcept {return ids_;}
        const auto& bounding_box() const noexcept {return box_;}

        void set_bounding_box(std::shared_ptr<box_t> box) noexcept {box_ = std::move(box);}

        // geometrical operations

        GeometrySet merged(real res, real radius) const;
        void merge(real res, real radius);
        void merge(const GeometrySet& other, real res, real radius);

        GeometrySet added(const GeometrySet& other) const;

        void calc_bounding_box() noexcept;

        // memory

        void clear() noexcept;

        // io functions

        void export_to_plt(std::ostream& os) const;
        void export_to_vtk(const std::string& path, bool binary = true) const;
    };
}
#endif //TONB_GEOMETRY_META_TOPOLOGY_HXX
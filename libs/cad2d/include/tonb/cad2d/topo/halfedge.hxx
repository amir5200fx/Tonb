//
// Created by amir on 11/9/25.
//
/**
 * @file halfedge.hxx
 * @brief Declares the HalfEdge class, representing the directed connection
 *        between two vertices in the cad2d topology graph.
 *
 * The Halfedge class is a fundamental element of the DCEL-stype topology
 * model used in the cad2d library. Each Halfedge represents a *directed*
 * connection between two vertices, possibly linked to a geometric curve
 * via a numerical identifier. The class maintains references to adjacent
 * half-edges and the face that lies to its left, forming a navigable
 * topological network.
 *
 * This file belongs to the **pure topology layer**, meaning it contains
 * no geometric or OCCT dependencies. Geometry binding is handled externally
 * through builders or adapters in higher-level modules.
 */
#pragma once
#ifndef TONB_CAD2D_TOPO_HALFEDGE_HXX
#define TONB_CAD2D_TOPO_HALFEDGE_HXX
#include <tonb/base/precision.hxx>
#include <tonb/cad2d/topo/orientation.hxx>
#include <memory>
namespace tonb::cad2d::topo {

    // Forward Declarations
    class Vertex;
    class Face;
    class Edge;

    using Id = std::uint64_t;

    class HalfEdge {
    public:

        /// @name Constructors
        /// @{

        /**
         * @brief Default constructor. Produces an uninitialized half-edge.
         */
        HalfEdge() = default;

        /**
         * @brief Construct a half-edge with an explicit identity and curve reference.
         *
         * @param id        Unique identifier for this half-edge.
         * @param curve_id  Opaque reference to the geometric curve (if any).
         * @param u0        Start parameter along the curve domain.
         * @param u1        End parameter along the curve domain.
         * @param orien     Direction of traversal along the curve.
         * @param tol       Local tolerance for numerical comparisons.
         */
        HalfEdge(const Id id, const Id curve_id, const real u0, const real u1,
                 const Orientation orien = Orientation::forward, const real tol = 1.e-9)
            : id_(id)
            , curve_id_(curve_id)
            , u0_(u0)
            , u1_(u1)
            , orien_(orien)
            , tol_(tol >= 0.0 ? tol : 1.e-9)
        {}

        /// @}

        /// @name Identity and curve association
        /// @{

        /**
         * @brief Get the unique identifier of this half-edge.
         */
        TNB_NODISCARD auto id() const noexcept {return id_;}

        /**
         * @brief Get the identifier of the curve associated with this half-edge.
         * @return A numeric handle identifying the referenced geometric curve.
         */
        TNB_NODISCARD auto curve_id() const noexcept {return curve_id_;}

        /**
         * @brief Get the parameter range of the associated curve segment.
         * @return A pair (u0, u1) representing the trimmed domain of the curve.
         */
        TNB_NODISCARD std::pair<real, real> param_range() const noexcept {return {u0_, u1_};}
        TNB_NODISCARD real u0() const noexcept {return u0_;}
        TNB_NODISCARD real u1() const noexcept {return u1_;}

        /**
         * @brief Get the traversal orientation along the curve.
         */
        TNB_NODISCARD Orientation orientation() const noexcept {return orien_;}

        /**
         * @brief Retrieve the local tolerance value.
         */
        TNB_NODISCARD real tolerance() const noexcept {return tol_;}

        /// @}

        /// @name Topological links
        /// @{
        ///

        /// Return the owning topological edge, if one is assigned.
        TNB_NODISCARD std::shared_ptr<Edge> edge() const noexcept {return edge_.lock();}

        /// Reference to the starting vertex (non-owning).
        TNB_NODISCARD std::shared_ptr<Vertex> start() const noexcept {return v_start_.lock();}

        /// Reference to the ending vertex (non-owning).
        TNB_NODISCARD std::shared_ptr<Vertex> end() const noexcept {return v_end_.lock();}

        /// Reference to the opposite half-edge (if exists).
        TNB_NODISCARD std::shared_ptr<HalfEdge> twin() const noexcept {return twin_.lock();}

        /// Next half-edge in a wire or face boundary loop.
        TNB_NODISCARD std::shared_ptr<HalfEdge> next() const noexcept {return next_.lock();}

        /// Previous half-edge in a wire or face boundary loop.
        TNB_NODISCARD std::shared_ptr<HalfEdge> prev() const noexcept {return prev_.lock();}

        /// The face that lies to the left of this half-edge.
        TNB_NODISCARD std::shared_ptr<Face> left_face() const noexcept {return left_face_.lock();}

        /// Setters (called by topology builders or editors)
        void set_start(std::weak_ptr<Vertex> v) noexcept {v_start_ = std::move(v);}
        void set_end(std::weak_ptr<Vertex> v) noexcept {v_end_ = std::move(v);}
        void set_twin(std::weak_ptr<HalfEdge> he) noexcept {twin_=std::move(he);}
        void set_next(std::weak_ptr<HalfEdge> he) noexcept {next_ = std::move(he);}
        void set_prev(std::weak_ptr<HalfEdge> he) noexcept {prev_ = std::move(he);}
        void set_left_face(std::weak_ptr<Face> f) noexcept {left_face_ = std::move(f);}

        /**
         * @brief Assign the owning topological edge.
         * @param e Non-owning reference to the owner edge.
         */
        void set_edge(std::weak_ptr<Edge> e) noexcept {edge_ = std::move(e);}

        /// @}

        /// @name Utility
        /// @{

        /**
         * @brief Reverse the parametric direction of this half-edge.
         *
         * Swaps the start and end parameters and flips the orientation flag.
         * This doesn't modify connectivity; only the local curve mapping.
         */
        void reverse_direction() noexcept {
            std::swap(u0_, u1_);
            orien_ = (orien_ == Orientation::forward)
                    ? Orientation::reversed
                    : Orientation::forward;
        }

        /**
         * @brief Check whether this half-edge references valid start and end vertices.
         */
        TNB_NODISCARD bool has_valid_vertices() const noexcept {
            return !v_start_.expired() && !v_end_.expired();
        }

        /// @}

        /// @name Comparison
        /// @{

        /**
         * @brief Equality is defined by unique ID.
         */
        friend bool operator==(const HalfEdge& a, const HalfEdge& b) noexcept {
            return a.id_ == b.id_;
        }

        /**
         * @brief Inequality comparison.
         */
        friend bool operator!=(const HalfEdge& a, const HalfEdge& b) noexcept {
            return !(a == b);
        }

        /// @}

    private:

        // ---- identity and geometry association ----
        Id id_{0};              ///< Stable unique identifier within the owning shape
        Id curve_id_{0};        ///< Opaque reference to the associated curve
        real u0_{0.0};          ///< Start parameter along the curve
        real u1_{0.0};          ///< End parameter along the curve
        Orientation orien_{Orientation::forward};   ///< Traversal orientation
        real tol_{1.e-9};       ///< Local numerical tolerance

        // ---- topological links (non-owning) ----
        std::weak_ptr<Vertex> v_start_;     ///< Starting vertex
        std::weak_ptr<Vertex> v_end_;       ///< Ending vertex
        std::weak_ptr<HalfEdge> twin_;      ///< Opposite half-edge
        std::weak_ptr<HalfEdge> next_;      ///< Next edge in boundary loop
        std::weak_ptr<HalfEdge> prev_;      ///< Previous edge in boundary loop
        std::weak_ptr<Face> left_face_;     ///< Adjacent face on the left
        std::weak_ptr<Edge> edge_;
    };
}
#endif //TONB_CAD2D_TOPO_HALFEDGE_HXX
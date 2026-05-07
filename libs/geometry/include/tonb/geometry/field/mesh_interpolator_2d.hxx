/** @file
*  @brief 2D mesh–based scattered-data interpolation (percentage-over-base aware).
 *
 *  @defgroup tonb_geometry_field_2d tonb::geometry::field — 2D field interpolation
 *  @ingroup tonb_geometry
 *
 *  This module turns scattered 2D samples into a continuous scalar field over a
 *  triangulated mesh. It supports:
 *
 *  - Absolute-value interpolation.
 *  - Percentage-over-base interpolation (samples given as % deltas over a base).
 *  - Optional smoothing (Laplacian or biharmonic).
 *  - Optional robust reweighting (Huber with MAD scale).
 *  - Fast point location (grid + triangle walking).
 *
 *  The field is represented by per-vertex values and evaluated piecewise-linearly
 *  inside each triangle using barycentric coordinates.
 */

/** @page field2d_usage Quick usage
@code{.cpp}
using namespace tonb::geometry::field;

// 1) Build a mesh
MeshInterpolator2d::TriMesh M;
M.set_vertices(V);     // std::vector<std::array<double,2>>
M.set_faces(F);        // std::vector<std::array<int,3>>
M.build_adjacency();

// 2) Construct interpolator
MeshInterpolator2d interp(M);

// 3a) Absolute samples
std::vector<MeshInterpolator2d::Sample> samples = ...;
MeshInterpolator2d::SolveOptions sopt; sopt.alpha = 1e-6; sopt.biharmonic = true;
MeshInterpolator2d::RobustOptions ropt; ropt.iters = 0;
auto v_abs = interp.interpolate(samples, sopt, ropt);

// 3b) Percent-over-base (uniform base)
double base = 100.0;
auto v_pct = interp.interpolate_percent_with_base_scalar(samples, base,
/*percent_scale=1.0, sopt, ropt);

// 4) Evaluate anywhere
double fxy = interp.evaluate(v_pct, {0.42,0.58});
@endcode
*/

/** @page field2d_notes Notes & conventions
 *  - **Units**: For percent mode, set @c percent_scale = 1.0 when sample values are fractions
 *    (e.g., 0.20 → +20%), or 0.01 when samples are percent points (e.g., 20 → +20%).
 *  - **Smoothing**: On a unit-box mesh, Laplacian @c alpha ≈ 1e-6 is a good start;
 *    biharmonic yields smoother contours with @c alpha in 1e-7…1e-6.
 *  - **Robust**: Enable at most 1 iteration with @c huber_k≈2.0 and a MAD @e sigma floor
 *    inside the implementation to avoid collapsing weights on sharp peaks.
 *  - **Numerics**: Sparse matrices are column-major and compressed; the RHS is built as
 *    @c Pt * (w ⊙ s) to avoid forming dense diagonals.
 */
#pragma once
#ifndef TONB_GEOMETRY_FIELD_MESH_INTERPOLATOR_2D_HXX
#define TONB_GEOMETRY_FIELD_MESH_INTERPOLATOR_2D_HXX

#include <tonb/geometry/pnt_2d.hxx>
#include <tonb/base/index_types.hxx>

#include <vector>
#include <array>
#include <memory>
#include <string>


namespace tonb::geometry::field {

    /**
     * @class tonb::geometry::field::MeshInterpolator2d
     * @ingroup tonb_geometry_field_2d
     * @brief Interpolates scattered samples onto a 2D triangulated mesh.
     *
     * @section algo Overview
     * Let @f$v\\in\\mathbb{R}^{|V|}@f$ be vertex values. For each sample @f$p_\\ell@f$,
     * we locate its triangle and compute barycentric weights @f$(\\lambda_0,\\lambda_1,\\lambda_2)@f$,
     * forming a sparse sampling matrix @f$P\\in\\mathbb{R}^{|S|\\times|V|}@f$ such that
     * @f$(Pv)_\\ell@f$ equals the barycentric interpolation at @f$p_\\ell@f$.
     *
     * We solve a Tikhonov-regularized least squares:
     * - **Absolute mode:** @f$\\min_v\\,\\|W^{1/2}(Pv-s)\\|^2 + \\alpha\\|Lv\\|^2@f$ (or @f$\\alpha\\|L^2v\\|^2@f$).
     * - **Percent-over-base:** solve for a delta @f$d@f$ with targets
     *     @f$\\hat s = (PB)\\odot(1 + \\texttt{percent\\_scale}\\cdot s)@f$ and fit @f$Pd\\approx \\hat s - PB@f$,
     *     then set @f$v=B+d@f$.
     *
     *   Smoothing uses a cotangent Laplacian @f$L@f$ (Laplacian or biharmonic).
     *   Robust reweighting (optional) applies Huber weights with a MAD-based scale (with a small floor).
     *
     *   @note Implementation hides Eigen in the .cxx; the public header exports STL-only types.
     */
    class MeshInterpolator2d {
    public:

        struct PointLocationResult {
            index_t triangle_id{-1};
            std::array<real, 3> bary{0, 0, 0};
        };

        /**
         * @brief Lightweight triangle mesh holder for interpolation.
         *
         * The mesh holds vertex positions (2D) and tringle for connectivity.
         * Adjacency is build for fast triangle walking during point location.
         */
        class TriMesh {
        public:

            /// default constructor
            TNBGEOM_EXPORT TriMesh();

            /// move/copy lifecylce.
            TNBGEOM_EXPORT TriMesh(const TriMesh&);
            TNBGEOM_EXPORT TriMesh(TriMesh&&) noexcept;

            TNBGEOM_EXPORT TriMesh& operator=(const TriMesh&);
            TNBGEOM_EXPORT TriMesh& operator=(TriMesh&&) noexcept;

            TNBGEOM_EXPORT ~TriMesh();

            // Public functions and operators

            /// @brief Set mesh vertices from raw coordinates.
            TNBGEOM_EXPORT void set_vertices(const std::vector<std::array<real, 2>>&);
            /// @brief Set mesh vertices from @ref tonb::geometry::Pnt2d.
            TNBGEOM_EXPORT void set_vertices(const std::vector<Pnt2d>&);
            /// @brief Set triangular faces (each as 3 vertex indices, 0-based).
            TNBGEOM_EXPORT void set_faces(const std::vector<std::array<index_t, 3>>&);
            /// @brief Build per-face adjacency (across edges) for triangle walking.
            TNBGEOM_EXPORT void build_adjacency();

            /// @return Number of vertices
            TNBGEOM_ND_EXPORT index_t vertex_count() const;
            /// @return Number of triangles
            TNBGEOM_ND_EXPORT index_t face_count() const;

            /**
             * @name Lightweight IO helpers
             * These are convenience functions for quick inspection and plotting.
             */
            TNBGEOM_ND_EXPORT bool write_obj(const std::string& filename) const;
            /**
             * @brief Dump CSV triples: `<prefix>_verts.csv`, `<prefix>_faces.csv`, `<prefix>_values.csv`.
             * @param prefix output path prefix (without extension).
             * @param vertex_values Optional per-vertex scalar (same length as vertices).
             */
            TNBGEOM_ND_EXPORT bool write_mesh_csv(const std::string& prefix, const std::vector<real>* vertex_values = nullptr) const;

        public:

            /*Private Data*/
            struct Impl;  // defined in .cxx
            std::unique_ptr<Impl> pimpl_;

            friend class MeshInterpolator2d;
        };

        /**@brief Solve options*/
        struct SolveOptions {
            real alpha = 1.e-4;             /// smoothing weight (=1e-7..1e-5 on unit box)
            bool biharmonic = false;        /// if true, penalize L^T L instead of L
            real diag_jitter = 1e-12;       /// tiny diagonal added to A for SPD safety
        };

        /**@brief Robust fitting options (Huber).*/
        struct RobustOptions {
            int iters = 3;                  /// robust reweighting iterations (0=off)
            real huber_k = 1.345;           /// Huber threshold (=2.0 recommended)
        };

        ///@brief A single scattered sample.
        struct Sample {
            std::array<real, 2> x{};        /// sample position (x, y) in mesh coordinates
            real value{};                   /// sample value (absolute, or precent depending on API)
            real weight = 1.0;              /// non-negative weight (0 disables the sample)
        };

        // Constructors
        explicit TNBGEOM_EXPORT MeshInterpolator2d(const TriMesh&, int grid_cells_per_axis=-1);

        TNBGEOM_EXPORT MeshInterpolator2d(const MeshInterpolator2d&);
        TNBGEOM_EXPORT MeshInterpolator2d(MeshInterpolator2d&&) noexcept;

        TNBGEOM_EXPORT MeshInterpolator2d& operator=(const MeshInterpolator2d&);
        TNBGEOM_EXPORT MeshInterpolator2d& operator=(MeshInterpolator2d&&) noexcept;

        TNBGEOM_EXPORT ~MeshInterpolator2d();

        // Public functions and operators

        /**
         * @brief Interpolate absolute samples onto mesh vertices.
         *
         * @param samples Scattered absolute samples.
         * @param sopt    Solver (smoothing) options.
         * @param ropt    Robust options (0 iterations disables robust).
         * @return Per-vertex values defining the piecewise-linear field.
         */
        TNBGEOM_ND_EXPORT std::vector<real> interpolate(const std::vector<Sample> &samples, const SolveOptions &sopt,
                                                        const RobustOptions &ropt) const;

        /**
         * @brief Interpolate percentage samples over a *uniform* base value.
         *
         * @param samples_percent Samples with values expressed as fractions (e.g. 0.2 = +20%) or percent points.
         * @param base_scalar     Base value B applied to all vertices.
         * @param percent_scale   Use 1.0 if samples are factions (0.2); use 0.01 if samples are in percent points (20).
         * @param sopt, ropt      Solver/robust options.
         * @return Per-vertex absolute values @f$v=B+d@f$.
         *
         * @note Method name in .cxx may appear as `interplate_percent_with_base_scalar` in one implementation;
         *       the intent is the "percent-with-base (scalar)" variant.
         */
        TNBGEOM_ND_EXPORT std::vector<real> interplate_percent_with_base_scalar(
            const std::vector<Sample> &samples_percent, real base_scalar, real percent_scale, const SolveOptions &sopt,
            const RobustOptions &ropt) const;

        /**
         * @brief Interpolate percentage samples over a *per-vertex* base feild.
         *
         * @param samples_percent Samples with values expressed as fractions or percent points.
         * @param base_per_vertex Base @f$B\\in\\mathbb{R}^{|V|}@f$ (same length as vertex count).
         * @param percent_scale   Use 1.0 if samples are fractions; 0.01 if they're percent points.
         * @param sopt, ropt      Solver/robust options.
         * @return Per-vertex absolute values.
         */
        TNBGEOM_ND_EXPORT std::vector<real> interpolate_percent_with_base(
            const std::vector<Sample> &samples_percent, const std::vector<double> &base_per_vertex, real percent_scale,
            const SolveOptions &sopt, const RobustOptions &ropt) const;

        /**
         * @brief Evaluate the piecewise-linear field at a query point.
         * @param vertex_values Per-vertex values (from any interpolation call).
         * @param p             Query point (x,y).
         * @param seed_face     Optional starting face for the locator (-1 less locator choose).
         * @return Interpolated value at @p p. If @p p is outside, the evaluator clamps on the boundary triangle.
         */
        TNBGEOM_ND_EXPORT real evaluate(const std::vector<real> &vertex_values, const std::array<real, 2> &p,
                                        int seed_face = -1) const;
    private:

        /*Private Data*/

        struct Impl;        // defined in .cxx
        std::unique_ptr<Impl> pimpl_;
    };
}
#endif //TONB_GEOMETRY_FIELD_MESH_INTERPOLATOR_2D_HXX
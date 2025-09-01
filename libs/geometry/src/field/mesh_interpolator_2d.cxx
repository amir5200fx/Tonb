//
// Created by amir on 8/31/25.
//

#include <memory>
#include <tonb/config.hxx>

#if defined(TONB_HAS_EIGEN)
#include <tonb/geometry/field/mesh_interpolator_2d.hxx>

#include <Eigen/Core>
#include <Eigen/Sparse>
#include <map>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace tonb::geometry::field {
    using SpMat = Eigen::SparseMatrix<real, Eigen::RowMajor>;
    using Triplet = Eigen::Triplet<real>;
    using Vec2 = Eigen::Vector2d;
    using RowMat2 = Eigen::Matrix<real, Eigen::Dynamic, 2, Eigen::RowMajor>;
    using RowMat3i = Eigen::Matrix<index_t, Eigen::Dynamic, 3, Eigen::RowMajor>;

    using PointLocationResult = MeshInterpolator2d::PointLocationResult;

    // --------------------- TriMesh PIMPL -----------------------------------
    struct MeshInterpolator2d::TriMesh::Impl {
        RowMat2 V; // nV x 2
        RowMat3i F; // nF x 3
        std::vector<std::array<index_t, 3>> neighbors; // nF
        std::vector<index_t> v2f;                      // nV
    };

    MeshInterpolator2d::TriMesh::TriMesh() : pimpl_(new Impl{}) {}
    MeshInterpolator2d::TriMesh::~TriMesh() = default;
    MeshInterpolator2d::TriMesh& MeshInterpolator2d::TriMesh::operator=(const TriMesh& other) {
        if (this != &other) {
            pimpl_ = std::make_unique<Impl>(*other.pimpl_);
        }
        return *this;
    }
    MeshInterpolator2d::TriMesh::TriMesh(TriMesh&&) noexcept = default;
    MeshInterpolator2d::TriMesh& MeshInterpolator2d::TriMesh::operator=(TriMesh&&) noexcept = default;

    void MeshInterpolator2d::TriMesh::set_vertices(const std::vector<std::array<real, 2> > & V) {
        pimpl_->V.resize(static_cast<index_t>(V.size()), 2);
        for (index_t i = 0; i < static_cast<index_t>(V.size()); i++) {
            pimpl_->V(i, 0) = V[i][0];
            pimpl_->V(i, 1) = V[i][1];
        }
    }
    void MeshInterpolator2d::TriMesh::set_faces(const std::vector<std::array<index_t, 3> > & F) {
        pimpl_->F.resize(static_cast<index_t>(F.size()), 3);
        for (index_t i = 0; i < static_cast<index_t>(F.size()); i++) {
            pimpl_->F(i, 0) = F[i][0];
            pimpl_->F(i, 1) = F[i][1];
            pimpl_->F(i, 2) = F[i][2];
        }
    }

    void MeshInterpolator2d::TriMesh::build_adjacency() {
        const auto nF = static_cast<index_t>(pimpl_->F.rows());
        const auto nV = static_cast<index_t>(pimpl_->V.rows());
        pimpl_->neighbors.assign(nF, {-1,-1,-1});
        pimpl_->v2f.assign(nV, -1);

        struct EdgeKey { int a,b; bool operator<(const EdgeKey& o) const { return a<o.a || (a==o.a && b<o.b); } };
        std::map<EdgeKey, std::pair<int,int>> edgeOwner;
        auto key = [](const int u, const int v){ return EdgeKey{std::min(u,v), std::max(u,v)}; };

        for (index_t f = 0; f < nF; ++f) {
            const index_t i = pimpl_->F(f,0), j = pimpl_->F(f,1), k = pimpl_->F(f,2);
            if (pimpl_->v2f[i] < 0) pimpl_->v2f[i] = f;
            if (pimpl_->v2f[j] < 0) pimpl_->v2f[j] = f;
            if (pimpl_->v2f[k] < 0) pimpl_->v2f[k] = f;

            const index_t ev[3][2] = {{i,j}, {j, k}, {k, i}};
            for (index_t e = 0; e < 3; ++e) {
                EdgeKey ek = key(ev[e][0], ev[e][1]);
                auto it = edgeOwner.find(ek);
                if (it == edgeOwner.end()) {
                    edgeOwner[ek] = {f, e};
                } else {
                    const index_t f2 = it->second.first;
                    const index_t e2 = it->second.second;
                    pimpl_->neighbors[f][e] = f2;
                    pimpl_->neighbors[f2][e2] = f;
                }
            }
        }
    }


    index_t MeshInterpolator2d::TriMesh::vertex_count() const {
        return static_cast<index_t>(pimpl_->V.rows());
    }
    index_t MeshInterpolator2d::TriMesh::face_count() const {
        return static_cast<index_t>(pimpl_->F.rows());
    }

    bool MeshInterpolator2d::TriMesh::write_obj(const std::string &filename) const {
        std::ofstream ofs(filename);
        if (!ofs) return false;

        ofs <<"# TriMesh OBJ export from tonb::io\n";
        ofs << std::fixed << std::setprecision(8);

        // Access PIMPL internals
        const auto& pimpl = *pimpl_;

        // vertices
        for (index_t i = 0; i < static_cast<index_t>(pimpl.V.rows()); ++i) {
            ofs << "v " << pimpl.V(i, 0) << " "<< pimpl.V(i, 1) << " 0.0\n";
        }

        // faces
        for (index_t f = 0; f < static_cast<index_t>(pimpl.F.rows()); ++f) {
            ofs << "f "
            <<(pimpl.F(f,0) + 1) << " "
            <<(pimpl.F(f,1) + 1) << " "
            <<(pimpl.F(f,2) + 1) << "\n";
        }
        return true;
    }

    bool MeshInterpolator2d::TriMesh::write_mesh_csv(const std::string &prefix, const std::vector<real>* values) const {
        const auto& impl = *pimpl_;
        if (values && static_cast<int>(values->size()) != impl.V.rows()) return false;

        std::ofstream fv(prefix + "_verts.csv");
        std::ofstream ff(prefix + "_faces.csv");
        if (!fv || !ff) return false;

        fv.setf(std::ios::fixed); fv.precision(10);
        for (int i = 0; i < impl.V.rows(); ++i)
            fv << impl.V(i,0) << "," << impl.V(i,1) << "\n";

        for (int f = 0; f < impl.F.rows(); ++f)
            ff << impl.F(f,0) << "," << impl.F(f,1) << "," << impl.F(f,2) << "\n";

        if (values) {
            std::ofstream fs(prefix + "_values.csv");
            if (!fs) return false;
            fs.setf(std::ios::fixed); fs.precision(10);
            for (int i = 0; i < impl.V.rows(); ++i)
                fs << (*values)[static_cast<size_t>(i)] << "\n";
        }

        return true;
    }


    // ---------------- Helpers (private to .cxx) ----------------
    static inline double orient2d(const Vec2& a, const Vec2& b, const Vec2& c){
        return (b.x()-a.x())*(c.y()-a.y()) - (b.y()-a.y())*(c.x()-a.x());
    }


    std::array<double,3> barycentric(const Vec2& p, const Vec2& a, const Vec2& b, const Vec2& c){
        const real A2 = orient2d(a,b,c);
        if (std::abs(A2) < 1e-20) return {1.0/3,1.0/3,1.0/3};
        const real w0 = orient2d(b,c,p)/A2;
        const real w1 = orient2d(c,a,p)/A2;
        const real w2 = 1.0 - w0 - w1;
        return {w0,w1,w2};
    }
    bool insideBary(const std::array<double,3>& w, const double tol = 1e-14){ return w[0]>=-tol && w[1]>=-tol && w[2]>=-tol; }

    std::array<double,3> clampBaryToTriangle(const std::array<double,3>& w){
        if (w[0]>=0 && w[1]>=0 && w[2]>=0) return w;
        const auto x=w;
        auto proj_edge=[&](const int zero){
            const index_t i = (zero+1) % 3, j = (zero+2) % 3;
            const real sum = x[i]+x[j];
            if (sum<=0) {
                std::array<double,3> r{0,0,0};
                const int pick=(x[i]>=x[j])?i:j; r[pick]=1.0;
                return r;
            }
            const real ti = std::max(0.0,std::min(1.0,x[i]/sum));
            std::array<real,3> r{0,0,0};
            r[i] = ti;
            r[j] = 1.0 - ti;
            return r;
        };

        const std::array<real,3> cands[3] = {proj_edge(0), proj_edge(1), proj_edge(2)};
        auto d2 = [&](const std::array<real,3>& a,const std::array<real,3>& b) {
            const real d0 = a[0]-b[0], d1 = a[1]-b[1], d22 = a[2]-b[2];
            return d0*d0 + d1*d1 + d22*d22;
        };

        index_t best = 0;
        real bd = d2(cands[0],x);
        for ( int k = 1; k < 3; ++k) {
            if (const real dd = d2(cands[k],x); dd < bd) {bd=dd; best=k;}
        }
        return cands[best];
    }

    class UniformGridIndex {
    public:

        void build(const MeshInterpolator2d::TriMesh::Impl& M, const int target_cells_per_axis=-1) {
            min_.setConstant(std::numeric_limits<double>::infinity());
            max_.setConstant(-std::numeric_limits<double>::infinity());

            for (index_t i = 0; i < M.V.rows(); ++i) {
                min_.x() = std::min(min_.x(), M.V(i,0));
                min_.y() = std::min(min_.y(), M.V(i,1));
                max_.x() = std::max(max_.x(), M.V(i,0));
                max_.y() = std::max(max_.y(), M.V(i,1));
            }

            Vec2 ext = max_-min_;
            if ( ext.x() <= 0 || ext.y() <= 0) ext = Vec2(1,1);

            if (target_cells_per_axis <= 0) {
                const auto nF = static_cast<index_t>(M.F.rows());
                const index_t base = std::max(8,std::min(512,static_cast<index_t>(std::sqrt(std::max(1, nF)))));
                dims_={base,base};
            }
            else dims_={std::max(1,target_cells_per_axis), std::max(1,target_cells_per_axis)};
            hx_=ext.x()/dims_[0]; hy_=ext.y()/dims_[1]; buckets_.assign(static_cast<size_t>(dims_[0] * dims_[1]),{});
            for (index_t f = 0; f < M.F.rows(); ++f) {
                Vec2 a = M.V.row(M.F(f,0));
                Vec2 b = M.V.row(M.F(f,1));
                Vec2 c = M.V.row(M.F(f,2));
                Vec2 bmin(std::min({a.x(),b.x(),c.x()}), std::min({a.y(),b.y(),c.y()}));
                Vec2 bmax(std::max({a.x(),b.x(),c.x()}), std::max({a.y(),b.y(),c.y()}));
                const auto ijmin=clampIdx(toIdx(bmin));
                const auto ijmax=clampIdx(toIdx(bmax));

                for (index_t iy = ijmin.second; iy <= ijmax.second; ++iy)
                    for (index_t ix = ijmin.first; ix <= ijmax.first; ++ix)
                        buckets_[index(ix,iy)].push_back(f);
            }
            built_=true;
        }

        TNB_NODISCARD std::vector<index_t> query(const Vec2& p) const {
            std::vector<index_t> result;
            if (!built_) return result;
            const auto ij= clampIdx(toIdx(p));
            const auto& b= buckets_[index(ij.first,ij.second)];
            if(!b.empty()) return b;
            for (index_t dy = -1; dy <= 1; ++dy)
                for(index_t dx = -1; dx <= 1; ++dx) {
                    const index_t ix = ij.first + dx;
                    const index_t iy=ij.second+dy;
                    if (ix < 0 || iy < 0 || ix >= dims_[0] || iy >= dims_[1]) continue;
                    const auto& bb = buckets_[index(ix,iy)];
                    result.insert(result.end(), bb.begin(), bb.end());
                }
            return result;
        }

    private:
        Vec2 min_{0,0}, max_{1,1};
        std::array<index_t, 2> dims_{16,16};
        real hx_ = 1.0, hy_=1.0;
        std::vector<std::vector<index_t>> buckets_;
        bool built_=false;

        TNB_NODISCARD size_t index(const index_t ix, const index_t iy) const {
            return static_cast<size_t>(iy * dims_[0] + ix);
        }

        TNB_NODISCARD std::pair<index_t, index_t> toIdx(const Vec2& p) const {
            const real px=(p.x()-min_.x())/hx_, py=(p.y()-min_.y())/hy_;
            return { static_cast<index_t>(std::floor(px)), static_cast<index_t>(std::floor(py)) };
        }

       TNB_NODISCARD std::pair<int,int> clampIdx(const std::pair<int,int>& ij) const {
            int ix=std::max(0,std::min(dims_[0]-1, ij.first));
            int iy=std::max(0,std::min(dims_[1]-1, ij.second));
            return {ix,iy};
        }
    };

    class TriangleLocator {
    public:
        TriangleLocator(const MeshInterpolator2d::TriMesh::Impl& M, const index_t grid_cells_per_axis)
        : M_(M) { grid_.build(M_, grid_cells_per_axis); }

        TNB_NODISCARD PointLocationResult locate(const Vec2& p, const index_t seed_face = -1, const index_t max_hops = 128) const {
            PointLocationResult res; int f=seed_face;
            if (f < 0 || f >= M_.F.rows()) {
                const std::vector<index_t> cand = grid_.query(p);
                if (!cand.empty()) { real best = std::numeric_limits<double>::infinity();
                    for (const index_t cf: cand) {
                        Vec2 a = M_.V.row(M_.F(cf,0));
                        Vec2 b = M_.V.row(M_.F(cf,1));
                        Vec2 c = M_.V.row(M_.F(cf,2));
                        Vec2 g = (a + b + c) / 3.0;
                        const real d2 = (g - p).squaredNorm();
                        if (d2 < best) {
                            best = d2;
                            f = cf;
                        }
                    }
                } else {
                    real best = std::numeric_limits<double>::infinity();
                    for (index_t cf = 0; cf < M_.F.rows(); ++cf) {
                        Vec2 a = M_.V.row(M_.F(cf,0));
                        Vec2 b = M_.V.row(M_.F(cf,1));
                        Vec2 c = M_.V.row(M_.F(cf,2));
                        Vec2 g=(a+b+c)/3.0;
                        const real d2 = (g-p).squaredNorm();
                        if(d2 < best) {
                            best = d2;
                            f = cf;
                        }
                    }
                }
            }
            if (f<0) return res;
            for (index_t hop = 0; hop < max_hops; ++hop) {
                Vec2 a = M_.V.row(M_.F(f,0));
                Vec2 b = M_.V.row(M_.F(f,1));
                Vec2 c = M_.V.row(M_.F(f,2));
                auto w= barycentric(p,a,b,c);
                if (insideBary(w)) {
                    res.triangle_id = f;
                    res.bary = w;
                    return res;
                }

                // pick most negative weight and step
                index_t neg = 0;
                real mn = w[0];
                if (w[1] < mn) {
                    mn = w[1]; neg = 1;
                }
                if (w[2] < mn) {
                    mn=w[2]; neg=2;
                }
                // neighbours[f] is ordered by edges: 0:(i,j), 1:(j,k), 2:(k,i)
                // map vertex -> opposite edge
                static const index_t opp_edge[3] = {
                    /* w0 -> cross (j,k) */ 1,
                    /* w1 -> cross (k,i) */ 2,
                    /* w2 -> cross (i,j) */ 0
                };

                index_t e  = opp_edge[neg];
                index_t fn = M_.neighbors.empty() ? -1 : M_.neighbors[f][e];
                if (fn < 0) { // boundary: clamp and return
                    res.triangle_id = f;
                    res.bary = clampBaryToTriangle(w);
                    return res;
                }
                f = fn;
            }
            res.triangle_id = f;
            const Vec2 a = M_.V.row(M_.F(f,0));
            const Vec2 b = M_.V.row(M_.F(f,1));
            const Vec2 c = M_.V.row(M_.F(f,2));
            res.bary = clampBaryToTriangle(barycentric(p,a,b,c));
            return res;
        }


    private:
        const MeshInterpolator2d::TriMesh::Impl& M_;
        UniformGridIndex grid_;
    };

    // static SpMat cotangent_laplacian(const MeshInterpolator2d::TriMesh::Impl& M) {
    //     const auto nV = static_cast<index_t>(M.V.rows());
    //     std::vector<std::map<index_t, real>> adj(nV);
    //
    //     auto cot = [&](const Vec2& u, const Vec2& v) {
    //         const real dot = u.dot(v);
    //         const real cross = std::abs(u.x()*v.y()-u.y()*v.x());
    //         if(cross<1e-20) return 0.0;
    //         return dot/cross;
    //     };
    //
    //     for (index_t f = 0; f < M.F.rows(); ++f) {
    //         const index_t i = M.F(f,0);
    //         const index_t j = M.F(f,1);
    //         const index_t k = M.F(f,2);
    //         Vec2 vi = M.V.row(i);
    //         Vec2 vj = M.V.row(j);
    //         Vec2 vk = M.V.row(k);
    //         const real cij = cot(vk-vi, vk-vj);
    //         const real cjk = cot(vi-vj, vi-vk);
    //         const real cki = cot(vj-vk, vj-vi);
    //         auto add = [&](const int a, const int b, const double w) {
    //             adj[a][b]+=0.5*w; adj[b][a]+=0.5*w;
    //         };
    //         add(i,j,cij);
    //         add(j,k,cjk);
    //         add(k,i,cki);
    //     }
    //
    //     std::vector<Triplet> trips; trips.reserve(nV*6);
    //     for (index_t i = 0; i < nV; ++i) {
    //         real diag = 0.0;
    //         for (const auto& kv: adj[i]) {
    //             index_t j = kv.first;
    //             const real w = kv.second;
    //             if (w != 0.0) {
    //                 trips.emplace_back(i,j,-w); diag+=w;
    //             }
    //         }
    //         trips.emplace_back(i,i,diag);
    //     }
    //     SpMat L(nV,nV);
    //     L.setFromTriplets(trips.begin(), trips.end());
    //     return L;
    // }

    static SpMat cotangent_laplacian(const MeshInterpolator2d::TriMesh::Impl& M) {
        const auto nV = static_cast<index_t>(M.V.rows());
        std::vector<std::map<index_t, real>> adj(nV);

        auto cot = [&](const Vec2& u, const Vec2& v) {
            const real dot = u.dot(v);
            const real cross = std::abs(u.x()*v.y()-u.y()*v.x());
            if (cross < 1e-20) return 0.0;
            return dot/cross;
        };

        for (index_t f = 0; f < M.F.rows(); ++f) {
            const index_t i = M.F(f,0);
            const index_t j = M.F(f,1);
            const index_t k = M.F(f,2);
            Vec2 vi = M.V.row(i);
            Vec2 vj = M.V.row(j);
            Vec2 vk = M.V.row(k);
            const real cij = cot(vk-vi, vk-vj);
            const real cjk = cot(vi-vj, vi-vk);
            const real cki = cot(vj-vk, vj-vi);
            auto add = [&](const index_t a, const index_t b, const real w) {
                adj[a][b] += 0.5*w;
                adj[b][a] += 0.5*w;
            };
            add(i,j, cij);
            add(j,k, cjk);
            add(k,i, cki);
        }
        std::vector<Triplet> trips; trips.reserve(nV*6);
        for (index_t i = 0; i < nV; ++i) {
            real diag = 0.0;
            for (const auto& kv: adj[i]) {
                index_t j = kv.first;
                const real w = kv.second;
                if (w != 0.0 ) {
                    trips.emplace_back(i,j,-w);
                    diag += w;
                }
            }
            trips.emplace_back(i,i,diag);
        }
        SpMat L(nV,nV);
        L.setFromTriplets(trips.begin(), trips.end());
        return L;
    }

    // --------------- MeshInterpolator2d PIMPL ----------------
    struct MeshInterpolator2d::Impl {
        const TriMesh::Impl* M; // not owning
        TriangleLocator locator;
        SolveOptions sopt_default{}; RobustOptions ropt_default{};


        Impl(const TriMesh::Impl* m, const int grid_cells) : M(m), locator(*m, grid_cells) {}


        struct SamplingSystem { SpMat P; Eigen::VectorXd s; Eigen::VectorXd w; };

        TNB_NODISCARD SamplingSystem build_sampling(const std::vector<Sample>& samples) const {
            const auto nS = static_cast<index_t>(samples.size());
            const auto nV = static_cast<index_t>(M->V.rows());

            std::vector<Triplet> trips; trips.reserve(nS*3);
            Eigen::VectorXd s(nS), w(nS);

            int hits = 0;
            index_t seed = -1;
            for (index_t i = 0; i < nS; ++i) {
                Vec2 px(samples[i].x[0], samples[i].x[1]);
                // ReSharper disable once CppDFAConstantConditions
                if (auto hit= locator.locate(px, seed); hit.triangle_id >= 0) {
                    ++hits;
                    seed = hit.triangle_id;
                    index_t v0 = M->F(hit.triangle_id,0);
                    index_t v1 = M->F(hit.triangle_id,1);
                    index_t v2 = M->F(hit.triangle_id,2);
                    trips.emplace_back(i,v0,hit.bary[0]);
                    trips.emplace_back(i,v1,hit.bary[1]);
                    trips.emplace_back(i,v2,hit.bary[2]);
                    s(i)=samples[i].value;
                    w(i)=samples[i].weight;
                } else {
                    w(i)=0.0;
                    s(i)=0.0;
                    //continue;
                }

            }
            SpMat P(nS,nV);
            P.setFromTriplets(trips.begin(), trips.end());
            return {std::move(P), std::move(s), std::move(w)};
        }

        static real sigma_MAD(const Eigen::VectorXd& r) {
            std::vector<real> a; a.reserve(r.size());
            for (index_t i = 0; i < r.size(); ++i)
                a.push_back(std::abs(r(i)));
            if (a.empty()) return 0.0;
            std::nth_element(a.begin(), a.begin() + a.size()/2, a.end());
            const real med = a[a.size()/2];
            return 1.4826*med;
        }

        static Eigen::VectorXd solve_field(const SamplingSystem& S, const SpMat& L, const SolveOptions& opt) {
            const auto nS=static_cast<index_t>(S.s.size());
            const auto nV=static_cast<index_t>(L.rows());
            SpMat W(nS,nS);
            std::vector<Triplet> wtr; wtr.reserve(nS);
            const double data_gain = 1.0;  // try 5–20
            for (index_t i = 0; i < nS; ++i)
                if (S.w(i) > 0.0) wtr.emplace_back(i,i,data_gain * S.w(i));
            W.setFromTriplets(wtr.begin(), wtr.end());
            SpMat Pt = S.P.transpose();
            SpMat dataTerm = Pt*W*S.P;
            SpMat smoothTerm = opt.biharmonic ? (L.transpose()*L) : L;
            SpMat A = dataTerm + opt.alpha * smoothTerm;
            {
                std::vector<Triplet> jtr; jtr.reserve(nV);
                for (index_t i = 0; i < nV; ++i) jtr.emplace_back(i,i,opt.diag_jitter);
                SpMat J(nV,nV);
                J.setFromTriplets(jtr.begin(), jtr.end());
                A += J;
            }
            Eigen::VectorXd rhs = Pt * (S.w.asDiagonal() * S.s);
            Eigen::SimplicialLDLT<SpMat> solver;
            solver.compute(A);
            if (solver.info() != Eigen::Success)
                throw std::runtime_error("Factorisation failed");
            Eigen::VectorXd v = solver.solve(rhs);
            if (solver.info() != Eigen::Success)
                throw std::runtime_error("Solve failed");
            return v;
        }
    };

    // ---- MeshInterpolator2d public API delegations ----

    MeshInterpolator2d::MeshInterpolator2d(const TriMesh & mesh, int grid_cells_per_axis)
        : pimpl_(std::make_unique<Impl>(mesh.pimpl_.get(), grid_cells_per_axis)){}

    MeshInterpolator2d::~MeshInterpolator2d() = default;
    MeshInterpolator2d::MeshInterpolator2d(const MeshInterpolator2d & other) {
        if (this != &other) {
            pimpl_.reset(std::make_unique<Impl>(*other.pimpl_).get());
        }
    }
    MeshInterpolator2d& MeshInterpolator2d::operator=(const MeshInterpolator2d & other) {
        if (this != &other) {
            pimpl_.reset(std::make_unique<Impl>(*other.pimpl_).get());
        }
        return *this;
    }
    MeshInterpolator2d::MeshInterpolator2d(MeshInterpolator2d &&) noexcept = default;
    MeshInterpolator2d& MeshInterpolator2d::operator=(MeshInterpolator2d &&) noexcept = default;

    std::vector<real> MeshInterpolator2d::interpolate(const std::vector<Sample> &samples, const SolveOptions &sopt, const RobustOptions &ropt) const {
        const auto& M = *pimpl_->M;
        if (M.F.rows() == 0 || M.V.rows() == 0)
            return {};
        const SpMat L = cotangent_laplacian(M);
        auto S = pimpl_->build_sampling(samples);
        Eigen::VectorXd v = Impl::solve_field(S, L, sopt);

        for (index_t it = 0; it < ropt.iters; ++it) {
            Eigen::VectorXd pred = S.P*v;
            Eigen::VectorXd r = S.s - pred;
            real sigma = Impl::sigma_MAD(r);
            if (!(sigma > 0)) sigma = 1e-12;
            for (index_t i = 0; i < S.w.size(); ++i) {
                if (S.w(i) <= 0.0) continue;
                const real t = r(i) / (sigma*ropt.huber_k + 1e-12);
                const real hi = (std::abs(t)<=1.0) ? 1.0:(1.0/std::abs(t));
                S.w(i) = std::max(1e-6, S.w(i)*hi);
            }
            v = Impl::solve_field(S, L, sopt);
        }
        std::vector<real> out(static_cast<size_t>(M.V.rows()));
        for (index_t i = 0; i < M.V.rows(); ++i)
            out[static_cast<size_t>(i)] = v(i);
        return out;
    }

    std::vector<real> MeshInterpolator2d::interplate_percent_with_base_scalar(
        const std::vector<Sample> &samples_percent, const real base_scalar, const real percent_scale,
        const SolveOptions &sopt, const RobustOptions &ropt) const {
        const auto& M = *pimpl_->M;
        Eigen::VectorXd B = Eigen::VectorXd::Constant(M.V.rows(), base_scalar);
        return interpolate_percent_with_base(samples_percent, std::vector<real>(B.data(), B.data() + B.size()),
                                             percent_scale, sopt, ropt);
    }

    std::vector<real> MeshInterpolator2d::interpolate_percent_with_base(const std::vector<Sample> &samples_percent,
                                                                        const std::vector<double> &base_per_vertex,
                                                                        real percent_scale, const SolveOptions &sopt,
                                                                        const RobustOptions &ropt) const {
        const auto& M = *pimpl_->M;
        if (static_cast<index_t>(base_per_vertex.size()) != M.V.rows())
            throw std::runtime_error("base_per_vertex size mismatch");
        SpMat L = cotangent_laplacian(M);
        auto S = pimpl_->build_sampling(samples_percent);
        Eigen::VectorXd B(M.V.rows());
        for (index_t i = 0; i < M.V.rows(); ++i)
            B(i) = base_per_vertex[static_cast<size_t>(i)];
        Eigen::VectorXd base_at_samples = S.P * B;
        Eigen::VectorXd s_desired = base_at_samples.array() * (1.0 + percent_scale * S.s.array());
        {
            // Debug — check target amplitudes at the samples
            double bmax = base_at_samples.maxCoeff();
            double pmin = S.s.minCoeff(), pmax = S.s.maxCoeff();
            double smin = s_desired.minCoeff(), smax = s_desired.maxCoeff();
            std::cerr << "[percent debug] base max=" << bmax
                      << "  sample p in [" << pmin << ", " << pmax << "]"
                      << "  percent_scale=" << percent_scale
                      << "  desired sample range=[" << smin << ", " << smax << "]\n";

        }
        auto Sd = S;
        Sd.s = s_desired - base_at_samples;
        Eigen::VectorXd d = Impl::solve_field(Sd, L, sopt);
        // Debug print before robust loop
        {
            Eigen::VectorXd pred_abs = base_at_samples + S.P * d;
            std::cerr << "desired max=" << s_desired.maxCoeff()
                      << "  predicted@samples max=" << pred_abs.maxCoeff()
                      << "  min=" << pred_abs.minCoeff() << "\n";
        }
        for (index_t it = 0; it < ropt.iters; ++it) {
            Eigen::VectorXd pred_abs = base_at_samples + S.P * d;
            Eigen::VectorXd r = s_desired - pred_abs;
            real sigma = Impl::sigma_MAD(r);
            if (!(sigma>0)) sigma=1e-12;
            for (index_t i = 0; i < Sd.w.size(); ++i) {
                if (Sd.w(i) <= 0.0) continue;
                real t = r(i) / (sigma*ropt.huber_k + 1e-12);
                real hi = (std::abs(t) <= 1.0) ? 1.0 : (1.0 / std::abs(t));
                Sd.w(i) = std::max(1e-6, Sd.w(i)*hi);
            }
            d = Impl::solve_field(Sd, L, sopt);
        }
        Eigen::VectorXd v = B + d;
        std::vector<real> out(static_cast<size_t>(M.V.rows()));
        for (index_t i = 0; i < M.V.rows(); ++i)
            out[static_cast<size_t>(i)] = v(i);

        return out;
    }

    real MeshInterpolator2d::evaluate(const std::vector<real> &vertex_values, const std::array<real, 2> &p, const index_t seed_face) const {
        const auto& M = *pimpl_->M;
        if (static_cast<index_t>(vertex_values.size())!=M.V.rows())
            throw std::runtime_error("vertex_values size mismatch");
        const Vec2 px(p[0], p[1]);
        const auto hit = pimpl_->locator.locate(px, seed_face);
        if (hit.triangle_id < 0)
            return std::numeric_limits<real>::quiet_NaN();
        const index_t v0 = M.F(hit.triangle_id,0);
        const index_t v1 = M.F(hit.triangle_id,1);
        const index_t v2 = M.F(hit.triangle_id,2);
        return hit.bary[0] * vertex_values[static_cast<size_t>(v0)] + hit.bary[1] * vertex_values[static_cast<size_t>(
                   v1)] + hit.bary[2] * vertex_values[static_cast<size_t>(v2)];
    }


}

#else

#endif

//
// Created by amir on 1/21/26.
//
#include <tonb/cad2d/topo/face.hxx>

#include <tonb/cad2d/topo/wire.hxx>

namespace tonb::cad2d::topo {
    std::vector<std::shared_ptr<Wire>> Face::holes_locked() const {
        std::vector<std::shared_ptr<Wire>> out;
        out.reserve(holes_.size());
        for (const auto& w: holes_) out.push_back(w.lock());
        return out;
    }

    Result<void> Face::check_basic(const Tolerance &tol, bool requireClosed) const {
        const auto o = outer_.lock();
        if (!o) {
            return Result<void>(ResultError{
                "Face basic check failed: outer wire reference is missing or expired.",
                ErrorCode::topology_error
            });
        }

        // Outer must not be empty for a meaningful face boundary.
        if (o->empty()) {
            return Result<void>(ResultError{
                "Face basic check failed: outer wire is empty",
                ErrorCode::validation_failed
            });
        }

        if (requireClosed) {
            const auto r= o->check_closed(tol);
            if (!r) {
                return Result<void>(ResultError{
                    "Face basic check failed: outer wire is not closed (" + r.error().message + ")",
                    r.error().code
                });
            }
        }

        for (const auto & hole : holes_) {
            const auto h = hole.lock();
            if (!h) {
                return Result<void>(ResultError{
                "Face basic check failed: a hole wire reference is missing or expired.",
                    ErrorCode::topology_error
                });
            }

            if (h.get() == o.get()) {
                return Result<void>(ResultError{
                    "Face basic check failed: a hole wire references the same object as the outer wire",
                    ErrorCode::validation_failed
                });
            }

            if (h->empty()) {
                return Result<void>(ResultError{
                    "Face basic check failed: a hole wire is emtpy",
                    ErrorCode::validation_failed
                });
            }

            if (requireClosed) {
                const auto r = h->check_closed(tol);
                if (!r) {
                    return Result<void>(ResultError{
                        "Face basic check failed: a hole wire is not closed (" + r.error().message + ")",
                        r.error().code
                    });
                }
            }
        }
        return Result<void>{};
    }
}

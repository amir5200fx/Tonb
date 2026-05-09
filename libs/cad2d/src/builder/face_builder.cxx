//
// Created by amir on 1/22/26.
//
#include <tonb/cad2d/builder/face_builder.hxx>

#include <tonb/cad2d/topo/face.hxx>

#include "tonb/cad2d/topo/halfedge.hxx"
#include "tonb/cad2d/topo/wire.hxx"

namespace tonb::cad2d::build {
    topo::Result<std::shared_ptr<topo::Face>> FaceBuilder::create(const std::shared_ptr<topo::Wire> &outer,
        const std::vector<std::shared_ptr<topo::Wire>> &holes, const bool requireClosed, const bool setLeftFace) const {
        if (!outer) {
            return topo::Result<std::shared_ptr<topo::Face>>(topo::ResultError{
                "FaceBuilder: outer wire is null", topo::ErrorCode::invalid_input
            });
        }
        for (const auto& h : holes) {
            if (!h) {
                return topo::Result<std::shared_ptr<topo::Face>>(topo::ResultError{
                    "FaceBuilder: a hole wire is null", topo::ErrorCode::invalid_input
                });
            }
        }

        auto f = shape_.make_face();
        if (!f) return topo::Result<std::shared_ptr<topo::Face>>(topo::ResultError{
            "FaceBuilder: failed to allocate face", topo::ErrorCode::internal
        });

        f->set_outer(outer);

        std::vector<std::weak_ptr<topo::Wire>> wholes;
        wholes.reserve(holes.size());
        for (const auto& h : holes) wholes.emplace_back(h);
        f->set_holes(std::move(wholes));

        if (const auto chk = f->check_basic(tol_, requireClosed); !chk) {
            return topo::Result<std::shared_ptr<topo::Face>>(topo::ResultError{
                "FaceBuilder: basic check failed (" + chk.error().message + ")", chk.error().code
            });
        }

        if (setLeftFace) {
            auto assign_wire = [&](const std::shared_ptr<topo::Wire>& w) {
                for (const auto edges = w->edges_locked(); const auto& e : edges) {
                    if (e) e->set_left_face(f);
                }
            };
            assign_wire(outer);
            for (const auto& h : holes) assign_wire(h);
        }
        return topo::ok(std::move(f));
    }
}

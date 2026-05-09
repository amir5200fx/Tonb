//
// Created by amir on 1/22/26.
//
#include <tonb/cad2d/builder/vertex_builder.hxx>

#include <tonb/cad2d/topo/result.hxx>

namespace tonb::cad2d::build {
    topo::Result<std::shared_ptr<topo::Vertex>> VertexBuilder::create(const topo::Pnt2d &p, double vtol) {
        auto v = shape_.make_vertex(p, vtol);
        if (!v) {
            return topo::Result<std::shared_ptr<topo::Vertex>>(topo::ResultError{
                "VertexBuilder: failed to create vertex", topo::ErrorCode::internal
            });
        }
        return topo::ok(std::move(v));
    }

    topo::Result<std::shared_ptr<topo::Vertex>> VertexBuilder::create_or_reuse(const topo::Pnt2d &p, double vtol) {
        for (const auto& v : shape_.vertices()) {
            if (!v) continue;
            const auto& q = v->position();
            if (tol_.equal(p.x(), p.y(), q.x(), q.y())) {
                auto vv = v;
                return topo::ok(std::move(vv));
            }
        }
        return create(p, vtol);
    }
}

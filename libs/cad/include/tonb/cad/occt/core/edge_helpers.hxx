//
// Created by amir on 8/24/25.
//
#pragma once

#include <tonb/cad/occt/edge.hxx>
#include <opencascade/TopoDS_Edge.hxx>
namespace tonb::cad::occt {
    struct Edge::Impl {
        TopoDS_Edge edge;
    };
}
namespace tonb::cad::occt::core {

    // ---- interop friend

    struct occt_edge_access {
        static Edge make(const TopoDS_Edge& edge) {
            if (edge.IsNull()) return {};
            return Edge{std::make_shared<Edge::Impl>(Edge::Impl{std::move(edge)})};
        }
        static TopoDS_Edge get(const Edge& edge) {
            return (edge.pimple_ ? edge.pimple_->edge : TopoDS_Edge{});
        }
    };
}
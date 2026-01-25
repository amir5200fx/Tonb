//
// Created by amir on 1/24/26.
//
#pragma once
#ifndef TONB_CAD2d_VALIDATE_HALFEDGE_CHECKS_HXX
#define TONB_CAD2d_VALIDATE_HALFEDGE_CHECKS_HXX

#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/topo/result.hxx>

#include <memory>

namespace tonb::cad2d::topo {
    class HalfEdge;
}

namespace tonb::cad2d::validate {
    topo::Result<void> check_endpoints(const std::shared_ptr<topo::HalfEdge>& e);

    topo::Result<void> check_twin(const std::shared_ptr<topo::HalfEdge>& e);

    topo::Result<void> check_next_prev(const std::shared_ptr<topo::HalfEdge>& e);

    topo::Result<void> check_halfedge(const std::shared_ptr<topo::HalfEdge>& e);
}
#endif //TONB_CAD2d_VALIDATE_HALFEDGE_CHECKS_HXX
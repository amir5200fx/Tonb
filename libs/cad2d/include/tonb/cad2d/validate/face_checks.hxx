//
// Created by amir on 1/24/26.
//
#pragma once
#ifndef TONB_CAD2d_VALIDATE_FACE_CHECKS_HXX
#define TONB_CAD2d_VALIDATE_FACE_CHECKS_HXX

#include <tonb/cad2d/topo/result.hxx>
#include <tonb/cad2d/topo/tolerance.hxx>

#include <memory>

namespace tonb::cad2d::topo {
    class Face;
}

namespace tonb::cad2d::validate {

    topo::Result<void> check_face_wires(const std::shared_ptr<topo::Face>& f, const topo::Tolerance& tol, bool requireClosed = true);

    topo::Result<void> check_face_edge_disjointness(const std::shared_ptr<topo::Face>& f);

    topo::Result<void> check_face(const std::shared_ptr<topo::Face>& f, const topo::Tolerance& tol, bool requireClosed = true);
}
#endif //TONB_CAD2d_VALIDATE_FACE_CHECKS_HXX
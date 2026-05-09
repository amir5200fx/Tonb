//
// Created by amir on 8/26/25.
//
#pragma once
#include <tonb/cad/occt/face.hxx>
// OCCT
#include <opencascade/TopoDS_Face.hxx>
namespace tonb::cad::occt {
    struct Face::Impl {
        TopoDS_Face f;
        explicit Impl(TopoDS_Face face) noexcept : f(std::move(face)) {}
    };
}
namespace tonb::cad::occt::core {
    struct occt_face_access {
        static Face make(const TopoDS_Face& face) {
            if (face.IsNull()) return {};
            return Face{std::make_shared<Face::Impl>(Face::Impl{face})};
        }
        static TopoDS_Face get(const Face& face) {
            return (face.pimpl_ ? face.pimpl_->f : TopoDS_Face());
        }
    };
}
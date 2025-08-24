//
// Created by amir on 8/24/25.
//
#include <tonb/cad/occt/body.hxx>
#include <tonb/cad/occt/core/body_helpers.hxx>
#include <tonb/geometry/occt/bbox.hxx>
#include <tonb/geometry/occt/core/bbox_helpers.hxx>

// OCCT headers only here
#include <opencascade/BRepBndLib.hxx>
#include <opencascade/Bnd_Box.hxx>
#include <opencascade/TopoDS_Shape.hxx>

namespace tonb::cad::occt {

    // OCCT-backed implementation
    struct Body::Impl {
        TopoDS_Shape shape;
    };

    // Backend access used by the occt adapter
    struct occt_access {
        static Body make(const TopoDS_Shape& shape) {
            auto impl = std::make_shared<Body::Impl>();
            impl->shape = shape;
            return Body{std::move(impl)};
        }

        static const TopoDS_Shape& get(const Body& b) {
            static TopoDS_Shape null_shape;
            return (b.p_ ? b.p_->shape : null_shape);
        }
    };

    Body core::from_topo(const TopoDS_Shape &shape) {
        return occt_access::make(shape);
    }

    TopoDS_Shape core::to_topo(const Body &body) {
        // Return a copy of the handle (remains cheap)
        return occt_access::get(body);
    }

}

bool tonb::cad::occt::Body::is_valid() const noexcept {
    return p_ && !p_->shape.IsNull();
}

tonb::cad::occt::Body::BBox tonb::cad::occt::Body::bbox() const {
    BBox out;
    if (!is_valid()) return out;

    Bnd_Box box;
    BRepBndLib::Add(p_->shape, box, false);
    box.SetGap(0.0);

    return geometry::occt::core::to_bbox(box);
}



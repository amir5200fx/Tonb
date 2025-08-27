//
// Created by amir on 8/24/25.
//
#include <tonb/config.hxx>
#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/cad/occt/body.hxx>
#include <tonb/cad/occt/face.hxx>
#include <tonb/cad/occt/core/face_helpers.hxx>
#include <tonb/cad/occt/core/body_helpers.hxx>
#include <tonb/cad/occt/core/location_helpers.hxx>
#include <tonb/geometry/occt/bbox.hxx>
#include <tonb/geometry/occt/core/bbox_helpers.hxx>

// OCCT headers only here
#include <opencascade/BRepBndLib.hxx>
#include <opencascade/Bnd_Box.hxx>
#include <opencascade/TopoDS_Shape.hxx>
#include <opencascade/TopoDS_Face.hxx>
#include <opencascade/TopExp_Explorer.hxx>
#include <opencascade/TopoDS.hxx>
#include <opencascade/TopExp.hxx>
#include <opencascade/TopTools_IndexedMapOfShape.hxx>

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

namespace tonb::cad::occt {
    std::vector<Face> Body::oriented_face() const {
        if (!is_valid()) return {};
        std::vector<Face> out;
        for (TopExp_Explorer ex(p_->shape, TopAbs_FACE); ex.More(); ex.Next()) {
            const TopoDS_Face& f = TopoDS::Face(ex.Current()); // orientation preserved
            out.emplace_back(core::occt_face_access::make(f));
        }
        return out;
    }
    std::vector<Face> Body::unique_forward_faces() const {
        if (!is_valid()) return {};
        TopTools_IndexedMapOfShape map;
        TopExp::MapShapes(p_->shape, TopAbs_FACE, map);

        std::vector<Face> out;
        out.reserve(static_cast<std::size_t>(map.Extent()));
        for (int i = 1; i <= map.Extent(); ++i) {
            TopoDS_Face f = TopoDS::Face(map(i)); // typically FORWARD orientation
            out.emplace_back(core::occt_face_access::make(f));
        }
        return out;
    }
    /// Return all face occurrences in the body, each with its own location.
    std::vector<Body::FaceOccurrence> Body::occurrence_faces() const {
        if (!is_valid()) return {};
        std::vector<FaceOccurrence> out;
        for (TopExp_Explorer ex(p_->shape, TopAbs_FACE); ex.More(); ex.Next()) {
            TopoDS_Face f = TopoDS::Face(ex.Current());
            const TopLoc_Location& loc = f.Location();
            TopoDS_Face f_unlocated = TopoDS::Face(f.Located(TopLoc_Location())); // strip loc
            out.emplace_back(FaceOccurrence{core::occt_face_access::make(f_unlocated), core::occt_location_access::make(loc)});
        }
        return out;
    }

}
#else

#endif



//
// Created by amir on 8/26/25.
//
#include <tonb/config.hxx>
#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/cad/occt/face.hxx>
#include <tonb/cad/occt/core/face_helpers.hxx>
#include <tonb/cad/occt/location.hxx>
#include <tonb/geometry/occt/surface.hxx>
#include <tonb/geometry/occt/core/surface_helpers.hxx>

//OCCT
#include <opencascade/BRepBuilderAPI_MakeFace.hxx>
#include <opencascade/TopoDS_Face.hxx>
#include <opencascade/TopAbs_Orientation.hxx>
#include <opencascade/TopLoc_Location.hxx>

#include <opencascade/BRep_Tool.hxx>
#include <opencascade/BRepTools.hxx>

#include <opencascade/Geom_Surface.hxx>
#include <opencascade/GeomLProp_SLProps.hxx>

#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Dir.hxx>
#include <opencascade/gp_Vec.hxx>
#include <opencascade/gp_Trsf.hxx>

#include <opencascade/IGESControl_Controller.hxx>
#include <opencascade/IGESControl_Writer.hxx>
#include <opencascade/Interface_Static.hxx>
#include <opencascade/STEPControl_Writer.hxx>
#include <opencascade/STEPControl_StepModelType.hxx>
#include <opencascade/IFSelect_ReturnStatus.hxx>

#include <stdexcept>
#include <utility>
#include <CGAL/IO/io.h>

#include "tonb/cad/occt/core/location_helpers.hxx"

namespace tonb::cad::occt {
    Face::Face(const Surface & surface, real tol) {
        // get opaque ptr
        const void* opaque = surface.native_backend_handle();
        auto& h = *reinterpret_cast<const opencascade::handle<Geom_Surface>*>(opaque);
        if (!h.IsNull()) {
            TopoDS_Face face = BRepBuilderAPI_MakeFace(h, tol);
            pimpl_ = std::make_shared<Impl>(std::move(face));
        }
    }

    bool Face::is_valid() const noexcept {
        return pimpl_ && !pimpl_->f.IsNull();
    }
    std::optional<std::tuple<real, real, real, real>> Face::uv_bounds() const {
        if (!is_valid()) return std::nullopt;
        Standard_Real u1, u2, v1, v2;
        BRepTools::UVBounds(pimpl_->f, u1, u2, v1, v2);
        // OCCT faces typically have finite param bounds even if the surface is periodic.
        return std::make_tuple(static_cast<real>(u1), static_cast<real>(u2), static_cast<real>(v1),
                               static_cast<real>(v2));
    }
    std::array<real, 3> Face::value(const real u, const real v) const {
        if (!is_valid()) throw std::logic_error("Face::value() called on a non-valid Face");
        TopLoc_Location loc;
        Handle(Geom_Surface) s = BRep_Tool::Surface(pimpl_->f, loc);
        if (s.IsNull()) throw std::logic_error("Face::value() called on a non-valid Face");

        gp_Pnt p;
        s->D0(u, v, p);
        return {static_cast<real>(p.X()), static_cast<real>(p.Y()), static_cast<real>(p.Z())};
    }
    std::array<real, 3> Face::world_value(const real u, const real v) const {
        if (!is_valid()) throw std::logic_error("Face::value() called on a non-valid Face");
        TopLoc_Location loc;
        Handle(Geom_Surface) s = BRep_Tool::Surface(pimpl_->f, loc);
        if (s.IsNull()) throw std::logic_error("Face::value() called on a non-valid Face");

        gp_Pnt p;
        s->D0(u, v, p);
        if (!loc.IsIdentity()) {
            const gp_Trsf tr = loc.Transformation();
            p.Transform(tr);
        }
        return {static_cast<real>(p.X()), static_cast<real>(p.Y()), static_cast<real>(p.Z())};
    }
    std::array<real, 3> Face::normal(const real u, const real v) const {
        if (!is_valid()) throw std::logic_error("Face::normal called on a non-valid Face");
        TopLoc_Location loc;
        const Handle(Geom_Surface) s = BRep_Tool::Surface(pimpl_->f, loc);
        if (s.IsNull()) throw std::logic_error("Face::normal null underlying surface");

        GeomLProp_SLProps props(s, u, v, 1, 1.e-12);
        if (!props.IsNormalDefined()) {
            throw std::logic_error("Face::normal normal undefined at parameter");
        }
        gp_Dir n = props.Normal();

        // Apply placement transform (vector part only).
        if (!loc.IsIdentity()) {
            const gp_Trsf tr = loc.Transformation();
            gp_Vec nv(n.X(), n.Y(), n.Z());
            nv.Transform(tr);
            if (nv.Magnitude() > 0) {
                n = gp_Dir(nv);
            }
        }

        // Respect face orientation: reversed faces flip the geometric normal.
        if (pimpl_->f.Orientation() == TopAbs_REVERSED) {
            n.Reverse();
        }
        return {static_cast<real>(n.X()), static_cast<real>(n.Y()), static_cast<real>(n.Z())};
    }

    bool Face::is_forward() const noexcept {
        return is_valid() && (pimpl_->f.Orientation() == TopAbs_FORWARD);
    }
    bool Face::is_reversed() const noexcept {
        return is_valid() && (pimpl_->f.Orientation() == TopAbs_REVERSED);
    }

    Face::Surface Face::world_surface() const {
        const auto [s, loc] = surface();
        if (!s.is_valid()) return {};
        // Returning the original handle avoids an unnecessary copy.
        // If you plan to *modify* the surface, make a copy first (e.g., via .Copy()).
        if (loc.is_identity()) return {}; // already world-aligned

        // Transform creates a *new* geometry with transform baked in.
        // UV domain is unchanged; use UV bounds from the face if you need trimming.
        Handle(Geom_Geometry) g = geometry::occt::core::occt_surface_access::get(s)->Transformed(
            core::occt_location_access::get(loc).Transformation());
        return geometry::occt::core::occt_surface_access::make(Handle(Geom_Surface)::DownCast(g));
    }
    std::pair<Face::Surface, Location> Face::surface() const {
        TopLoc_Location loc; // out: accumulated location
        Handle(Geom_Surface) s = BRep_Tool::Surface(pimpl_->f, loc); // may be null
        // s can be null (e.g., degenerate face, invalid topology)
        if (s.IsNull()) return {};
        return {geometry::occt::core::occt_surface_access::make(s), core::occt_location_access::make(loc)};
    }

    bool Face::export_iges(const std::string &file_name, const std::string& unit) const {
        if (!is_valid()) return false;
        try {
            IGESControl_Controller::Init();

            // Set parameters first (global state)
            Interface_Static::SetCVal("write.iges.unit", unit.c_str());
            Interface_Static::SetIVal("write.iges.brep.mode", 1); // BREP

            IGESControl_Writer writer(unit.c_str(), 0);
            writer.AddShape(core::occt_face_access::get(*this));

            return writer.Write(file_name.c_str()); // returns Standard_Boolean
        }
        catch (const Standard_Failure& e) {
            // log e.GetMessageString() if you have logging
            return false;
        }
        catch (const std::exception&) {
            return false;
        }
        catch (...) {
            return false;
        }
    }

    bool Face::export_step_AP242(const std::string &file_name, std::string& msg) const {
        if (!is_valid()) {
            msg = "Invalid Face";
            return false;
        }
        try {
            Interface_Static::SetCVal("write.step.schema", "AP242");
            STEPControl_Writer writer;
            // Transfer geometry "as is" (no tessellation)
            IFSelect_ReturnStatus tr = writer.Transfer(core::occt_face_access::get(*this), STEPControl_AsIs);
            if (tr != IFSelect_RetDone) {
                std::ostringstream oss;
                oss << "STEP transfer failed (status "<< static_cast<int>(tr) <<")";
                msg = oss.str();
                return false;
            }
            // Write the .step/.stp file
            const IFSelect_ReturnStatus wr = writer.Write(file_name.c_str());
            if (wr != IFSelect_RetDone) {
                std::ostringstream oss;
                oss << "STEP write failed (status "<< static_cast<int>(wr) << ")\n";
                msg = oss.str();
                return false;
            }
            return true;
        } catch (const Standard_Failure& e) {
            std::ostringstream oss;
            oss << "OCCT error: " << e.GetMessageString() << "\n";
            msg = oss.str();
            return false;
        }
        catch (const std::exception& e) {
            std::ostringstream oss;
            oss << "OCCT error: " << e.what() << "\n";
            msg = oss.str();
            return false;
        }
        catch (...) {
            msg = "OCCT error: unknown error.\n";
            return false;
        }
    }
}

#else
static_assert(true, "src/occt/face.cxx compiled without TONB_WITH_OCCT");
#endif
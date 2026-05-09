#pragma once
#ifndef _Cad_PreviewTools_Header
#define _Cad_PreviewTools_Header

#include <Cad_Module.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity3d_PolygonFwd.hxx>
#include <Entity3d_ChainFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

class Geom_Curve;
class Geom_Surface;
class TopoDS_Face;
class TopoDS_Shape;

namespace tnbLib
{

	class Cad_PreviewTools
	{

	public:

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Chain> 
			RetrieveChain
			(
				const std::vector<std::vector<Pnt3d>>& thePoints
			);

		//- an exception will be thrown if the surface is not bspline
		static TnbCad_EXPORT std::shared_ptr<Entity3d_Triangulation>
			PreviewPatchCurves
			(
				const Handle(Geom_Surface)& theSurface,
				const Standard_Integer theNbSegments_U,
				const Standard_Integer theNbSegments_V
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Chain>
			PreviewUnMergedPatchCurves
			(
				const Handle(Geom_Surface)& theSurface,
				const Standard_Integer theNbSegments_U,
				const Standard_Integer theNbSegments_V
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Triangulation>
			PreviewPatchCurves
			(
				const TopoDS_Face& theFace,
				const Standard_Integer theNbSegments_U,
				const Standard_Integer theNbSegments_V
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Chain>
			PreviewUnMergedPatchCurves
			(
				const TopoDS_Face& theFace,
				const Standard_Integer theNbSegments_U,
				const Standard_Integer theNbSegments_V
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Chain>
			PreviewUnMergedPatchCurves
			(
				const TopoDS_Shape& theShape,
				const Standard_Integer theNbSegments_U,
				const Standard_Integer theNbSegments_V
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Polygon>
			PreviewCurveOnSurface_U
			(
				const Handle(Geom_Surface)& theSurface,
				const Standard_Real u,
				const Standard_Integer theNbSegments
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Polygon>
			PreviewCurveOnSurface_V
			(
				const Handle(Geom_Surface)& theSurface,
				const Standard_Real v,
				const Standard_Integer theNbSegments
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Polygon>
			PreviewCurve
			(
				const Handle(Geom_Curve)& theCurve,
				const Standard_Integer theNbSegments
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Triangulation>
			Box(const Entity3d_Box& b);
	};
}

#endif // !_Cad_PreviewTools_Header

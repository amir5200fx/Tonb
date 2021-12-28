#pragma once
#ifndef _Cad_Tools_Header
#define _Cad_Tools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Entity_Segment.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Cad_Module.hxx>

class Bnd_Box;
class TopoDS_Shape;
class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Wire;
class Geom_Curve;
class Geom_Line;
class Geom_Surface;
class Geom_Plane;
class Geom2d_Curve;
class Poly_Triangulation;
class Geom_BSplineCurve;
class Geom_BSplineSurface;

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Cad_TModel;
	class TModel_Surface;
	class TModel_Edge;
	class TModel_Curve;
	class TModel_Shell;
	class TModel_ParaWire;
	class TModel_Vertex;
	class TModel_Wire;
	class Entity2d_Metric1;

	template<class EntityType>
	class Cad_BlockEntity;

	class Cad_Tools
	{

	public:

		static TnbCad_EXPORT Standard_Boolean 
			HasTriangulation
			(
				const TopoDS_Shape& theShape
			);

		static TnbCad_EXPORT Standard_Real 
			CalcPrecision
			(
				const TModel_Vertex&
			);

		static TnbCad_EXPORT Standard_Boolean
			IsBounded
			(
				const Handle(Geom_Curve)& theCurve
			);

		static TnbCad_EXPORT Entity3d_Box
			BoundingBox
			(
				const Bnd_Box& theBox
			);

		static TnbCad_EXPORT Entity3d_Box
			BoundingBox
			(
				const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
			);

		static TnbCad_EXPORT Bnd_Box
			BoundingBox
			(
				const TopoDS_Shape& theShape, 
				const Standard_Boolean useTri = Standard_False
			);

		static TnbCad_EXPORT Pnt2d Project(const Pnt3d& thePoint, const Handle(Geom_Plane)& thePlane);
		static TnbCad_EXPORT Standard_Real Project(const Pnt3d& thePoint, const Handle(Geom_Line)& theLine);

		static TnbCad_EXPORT Entity_Segment<Pnt2d> 
			Project
			(
				const Entity3d_SegmentRef& theSeg,
				const Handle(Geom_Plane)& thePlane
			);

		static TnbCad_EXPORT Handle(Geom_BSplineCurve) BoundaryCurveU0(const Handle(Geom_BSplineSurface)&);
		static TnbCad_EXPORT Handle(Geom_BSplineCurve) BoundaryCurveUn(const Handle(Geom_BSplineSurface)&);
		static TnbCad_EXPORT Handle(Geom_BSplineCurve) BoundaryCurveV0(const Handle(Geom_BSplineSurface)&);
		static TnbCad_EXPORT Handle(Geom_BSplineCurve) BoundaryCurveVn(const Handle(Geom_BSplineSurface)&);

		static TnbCad_EXPORT std::shared_ptr<Entity2d_Triangulation>
			ParametricTriangulation
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Standard_Integer theNx,
				const Standard_Integer theNy
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Triangulation>
			Triangulation
			(
				const Geom_Surface& theSurface,
				const Entity2d_Triangulation& theParametric
			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Triangulation>
			Triangulation
			(
				const Handle(Geom_Surface)& theSurface,
				const Standard_Integer theNx,
				const Standard_Integer theNy

			);

		static TnbCad_EXPORT std::shared_ptr<Entity3d_Triangulation>
			Triangulation
			(
				const Poly_Triangulation& theTriangulation
			);

		static TnbCad_EXPORT Handle(Geom_Curve)
			ConvertToTrimmed
			(
				const Handle(Geom_Curve)& theCurve,
				const Standard_Real u0,
				const Standard_Real u1
			);

		static TnbCad_EXPORT std::shared_ptr<TModel_Edge>
			GetEdge
			(
				const TopoDS_Edge& theEdge,
				const TopoDS_Face& theFace
			);

		static TnbCad_EXPORT std::shared_ptr<TModel_Edge>
			GetEdge
			(
				const Standard_Integer theIndex,
				const TopoDS_Edge& theEdge,
				const TopoDS_Face& theFace
			);

		static TnbCad_EXPORT std::shared_ptr<TModel_Surface>
			GetSurface
			(
				const TopoDS_Face& theFace
			);

		static TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Surface>>
			GetSurfaces
			(
				const TopoDS_Shape& theShape
			);

		static TnbCad_EXPORT std::shared_ptr<Cad_TModel>
			MakeSolid
			(
				const TopoDS_Shape& theShape,
				const Standard_Real theTolerance
			);

		static TnbCad_EXPORT std::shared_ptr<Cad_TModel>
			MakeSolid
			(
				const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces,
				const Standard_Real theTolerance
			);

		static TnbCad_EXPORT std::shared_ptr<std::vector<std::shared_ptr<TModel_Shell>>>
			TrackShells
			(
				const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
			);

		//- Warning: This function is on the early stage!
		static TnbCad_EXPORT Standard_Boolean
			InnerHoles
			(
				const std::vector<std::shared_ptr<TModel_Shell>>& theShells,
				std::vector<std::shared_ptr<TModel_Shell>>& theInners,
				std::shared_ptr<TModel_Shell>& theOuters
			);

		static TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Edge>>
			RetrieveNonSingularEdges
			(
				const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
			);

		static TnbCad_EXPORT Handle(Poly_Triangulation)
			RetrieveTriangulation
			(
				const TopoDS_Face& theFace
			);

		static TnbCad_EXPORT std::vector<Handle(Poly_Triangulation)>
			RetrieveTriangulation
			(
				const TopoDS_Shape& theShape
			);

		static TnbCad_EXPORT std::vector<TopoDS_Face> 
			RetrieveFaces
			(
				const TopoDS_Shape& theShape
			);

		static TnbCad_EXPORT std::vector<TopoDS_Edge>
			RetrieveEdges
			(
				const TopoDS_Shape& theShape
			);

		static TnbCad_EXPORT std::vector<Handle(Geom2d_Curve)>
			RetrieveParaCurves
			(
				const std::vector<TopoDS_Edge>& theEdges, 
				const gp_Ax2& theSystem
			);

		static TnbCad_EXPORT std::vector<Handle(Geom2d_Curve)>
			RetrieveParaCurves
			(
				const std::vector<TopoDS_Edge>& theEdges,
				const Handle(Geom_Surface) theSurface
			);

		static TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Edge>> 
			RetrieveEdges
			(
				const std::vector<std::shared_ptr<TModel_Surface>>&
			);

		static TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Edge>> 
			RetrieveFreeEdges
			(
				const std::shared_ptr<Cad_TModel>&
			);

		static TnbCad_EXPORT Standard_Boolean
			IsClosed
			(
				const Cad_BlockEntity<TModel_Surface>& theBlock
			);

		static TnbCad_EXPORT Entity2d_Metric1 
			CalcMetric
			(
				const Pnt2d& thePnt, 
				const Handle(Geom_Surface)&
			);

		static TnbCad_EXPORT Entity2d_Metric1 
			CalcMetric
			(
				const Standard_Real theX,
				const Standard_Real theY,
				const Handle(Geom_Surface)&
			);

		static TnbCad_EXPORT void SetPrecision(const std::shared_ptr<Cad_TModel>& theSolid);

		static TnbCad_EXPORT void ExportToIGES
		(
			const word& theUnit,
			const TopoDS_Shape& theShape,
			const fileName& theName
		);

		static TnbCad_EXPORT void ExportToSTEP
		(
			const TopoDS_Shape& theShape,
			const fileName& name
		);
	};
}

#endif // !_Cad_Tools_Header

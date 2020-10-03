#pragma once
#ifndef _Pln_Tools_Header
#define _Pln_Tools_Header

#include <Standard_Handle.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Pln_Orientation.hxx>

#include <list>
#include <vector>
#include <memory>

class gp_Ax2d;
class gp_Ax22d;
class Bnd_Box2d;
class Geom2d_Curve;
class Geom2dAPI_InterCurveCurve;
class TopoDS_Edge;
class TopoDS_Shape;

namespace tnbLib
{

	// Forward Declarations
	class Pln_Entity;
	class Pln_Edge;
	class Pln_Ring;
	class Pln_CmpEdge;
	class Pln_Wire;
	class Pln_Curve;
	class Pln_Vertex;
	class Cad2d_Plane;
	class NumAlg_AdaptiveInteg_Info;

	template<class T>
	class Geo_AdTree;

	namespace cad2dLib
	{
		class Modeler_Corner;
	}

	class Pln_Tools
	{

	public:

		static Standard_Boolean
			IsBounded
			(
				const Handle(Geom2d_Curve)& theCurve
			);

		static Standard_Boolean 
			IsManifold
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static Standard_Boolean 
			IsValidToRetrieveWires
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		//- WARNING! check the convergence by info parameter
		static Standard_Real 
			Length
			(
				const Geom2d_Curve& theCurve,
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			);

		static Standard_Real
			Distance
			(
				const Pnt2d& theCoord,
				const Handle(Geom2d_Curve)& theCurve
			);

		static Standard_Real
			Distance
			(
				const Pnt2d& theCoord,
				const Handle(Geom2d_Curve)& theCurve,
				Standard_Real& theParameter
			);

		static std::shared_ptr<Pln_CmpEdge>
			MakeCompoundEdge
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static std::vector<std::shared_ptr<Pln_Edge>> Merged(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges);

		static std::shared_ptr<Pln_Wire>
			MakeWire
			(
				const std::shared_ptr<Pln_Ring>& theRing
			);

		static std::shared_ptr<Pln_Wire>
			MakeWire
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Pln_Wire>
			MakeWire
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const std::vector<Standard_Boolean>& theSense,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Cad2d_Plane>
			MakePlane
			(
				const std::shared_ptr<Pln_Wire>& theWire, 
				const gp_Ax2& theAx
			);

		static Pln_Orientation
			RetrieveOrientation
			(
				const Pln_Wire& theWire
			);

		static Entity2d_Box
			RetrieveBoundingBox
			(
				const Pln_Wire& theWire
			);

		static Entity2d_Box
			RetrieveBoundingBox
			(
				const Pln_CmpEdge& theEdge
			);

		static Entity2d_Box
			RetrieveBoundingBox
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static std::vector<std::shared_ptr<Pln_Wire>>
			RetrieveWires
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static std::vector<std::shared_ptr<Pln_Wire>>
			RetrieveWiresNonManifold
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
				const Standard_Boolean checkManifold = Standard_True
			);

		static std::vector<std::shared_ptr<Pln_Vertex>>
			RetrieveVertices
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveEdges
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		//- an exception will be thrown if the curve is not bounded
		static std::shared_ptr<Geom2dAPI_InterCurveCurve>
			Intersection
			(
				const Handle(Geom2d_Curve)& theCurve0,
				const Handle(Geom2d_Curve)& theCurve1,
				const Standard_Real theTol = 1.0E-6
			);

		static std::shared_ptr<Pln_Vertex> 
			Intersection
			(
				const std::shared_ptr<Pln_Edge>& theEdge0,
				const std::shared_ptr<Pln_Edge>& theEdge1
			);

		static Handle(Geom2d_Curve)
			ConvertToTrimmedCurve
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theU0,
				const Standard_Real theU1);

		//- an exception will be thrown if the curve is not bounded
		static Handle(Geom2d_Curve)
			ConvertToBSpline
			(
				const Handle(Geom2d_Curve)& theCurve
			);

		static std::shared_ptr<Entity2d_Triangulation>
			ParametricTriangulation
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Standard_Integer theNx,
				const Standard_Integer theNy
			);

		static Entity2d_Box 
			BoundingBox
			(
				const Bnd_Box2d& theBox
			);

		//- an exception will be thrown if the curve is not bounded
		static Bnd_Box2d
			BoundingBox
			(
				const Handle(Geom2d_Curve)& theCurve
			);

		static Bnd_Box2d
			BoundingBox
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theU0,
				const Standard_Real theU1
			);

		//- an exception will be thrown if the curve is not bounded and the x exceeds the boundary
		static void
			SplitCurve
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theX,
				Handle(Geom2d_Curve)& theC0,
				Handle(Geom2d_Curve)& theC1
			);

		static std::vector<std::shared_ptr<Pln_Curve>>
			RetrieveCurves
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves
			);

		static std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveEdges
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves
			);

		static std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveMergedEdges
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		//- WARNING! make sure the object is manifold then call this method
		static std::vector<std::shared_ptr<Pln_Wire>>
			RetrieveWires
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves, 
				const Standard_Real theMinTol, 
				const Standard_Real theMaxTol
			);

		//- WARNING! make sure the object is manifold then call this method
		static std::vector<std::shared_ptr<Pln_Wire>>
			RetrieveWires
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Pln_Wire>
			RetrieveWire
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

		static void 
			SameSense
			(
				const std::shared_ptr<Pln_CmpEdge>& theEdge
			);

		static std::shared_ptr<Pln_Wire>
			RetrieveOuterWire
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static std::vector<std::shared_ptr<Cad2d_Plane>>
			RetrievePlanes
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires,
				const gp_Ax2& theAx
			);

		static std::shared_ptr<Pln_Edge>
			ForwardEdge
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

		static std::shared_ptr<Pln_Edge>
			BackwardEdge
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

		static std::vector<std::shared_ptr<Pln_Edge>>
			MakeConsecutive
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
				const Standard_Real theTol
			);

		static std::shared_ptr<Pln_Vertex>
			MergeTwoVertex(const std::shared_ptr<Pln_Vertex>& theVtx0, const std::shared_ptr<Pln_Vertex>& theVtx1, const Standard_Real theTol);

		static void 
			SortWires
			(
				std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static std::shared_ptr<Pln_Vertex> 
			Vertex
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static std::shared_ptr<Pln_Edge> 
			Edge
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static std::shared_ptr<Pln_Curve> 
			Curve
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static std::shared_ptr<Pln_Ring> 
			Ring
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static std::shared_ptr<Cad2d_Plane> 
			Plane
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static std::vector<std::shared_ptr<Pln_Vertex>> RetrieveVertices(const std::shared_ptr<Pln_Entity>& theEnt);

		static std::vector<std::shared_ptr<Pln_Curve>> RetrieveCurves(const std::shared_ptr<Pln_Entity>& theEnt);

		static std::vector<std::shared_ptr<Pln_Edge>> RetrieveEdges(const std::shared_ptr<Pln_Entity>& theEnt);

		static std::vector<TopoDS_Edge> 
			RetrieveEdges
			(
				const TopoDS_Shape& theEdges
			);

		static std::vector<Handle(Geom2d_Curve)>
			RetrieveParaCurves
			(
				const std::vector<TopoDS_Edge>& theEdges,
				const gp_Ax2& theSystem
			);

		static void 
			ImportToCorner
			(
				const std::shared_ptr<Pln_Vertex>& theVtx,
				Geo_AdTree<std::shared_ptr<cad2dLib::Modeler_Corner>>& theCorners
			);

		static void RetrieveInnerOuterWires
		(
			std::list<std::shared_ptr<Pln_Wire>>& theWires,
			std::shared_ptr<Pln_Wire>& theOuter, 
			std::vector<std::shared_ptr<Pln_Wire>>& theInners
		);
	};
}

#endif // !_Pln_Tools_Header

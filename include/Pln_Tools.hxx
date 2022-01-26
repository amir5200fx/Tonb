#pragma once
#ifndef _Pln_Tools_Header
#define _Pln_Tools_Header

#include <Standard_Handle.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Cad2d_Module.hxx>
#include <Pln_Orientation.hxx>

#include <Precision.hxx>

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
	class Geo_ApprxCurve_Info;
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

		static TnbCad2d_EXPORT Standard_Real CalcPrecision(const Pln_Vertex&);

		static TnbCad2d_EXPORT Standard_Boolean
			IsBounded
			(
				const Handle(Geom2d_Curve)& theCurve
			);

		static TnbCad2d_EXPORT Standard_Boolean
			IsManifold
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static TnbCad2d_EXPORT Standard_Boolean
			IsValidToRetrieveWires
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		//- WARNING! check the convergence by info parameter
		static TnbCad2d_EXPORT Standard_Real
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
			)
		{
			NotImplemented;
			return 0;
		}

		static Standard_Real
			Distance
			(
				const Pnt2d& theCoord,
				const Handle(Geom2d_Curve)& theCurve,
				Standard_Real& theParameter
			)
		{
			NotImplemented;
			return 0;
		}

		static TnbCad2d_EXPORT std::shared_ptr<Entity2d_Polygon> 
			UniformDiscrete
			(
				const Handle(Geom2d_Curve)&,
				const Standard_Integer nbSeg
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_CmpEdge>
			MakeCompoundEdge
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>> Merged(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Wire>
			MakeWire
			(
				const std::shared_ptr<Pln_Ring>& theRing
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Wire>
			MakeWire
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const Standard_Real theMaxTol
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Wire>
			MakeWire
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const std::vector<Standard_Boolean>& theSense,
				const Standard_Real theMaxTol
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> MakeEdge(const Handle(Geom2d_Curve)& theCurve);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> MakeEdge(const std::shared_ptr<Pln_Curve>& theCurve);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> MakeEdge(std::shared_ptr<Pln_Curve>&& theCurve);

		static std::shared_ptr<Pln_Wire>
			MakeWire
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const std::vector<Standard_Boolean>& theSense,
				const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo,
				const Standard_Real theMaxTol
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			MakePlane
			(
				const std::shared_ptr<Pln_Wire>& theWire, 
				const gp_Ax2& theAx
			);

		static TnbCad2d_EXPORT Pln_Orientation
			RetrieveOrientation
			(
				const Pln_Wire& theWire
			);

		static TnbCad2d_EXPORT Entity2d_Box
			RetrieveBoundingBox
			(
				const Pln_Wire& theWire
			);

		static TnbCad2d_EXPORT Entity2d_Box
			RetrieveBoundingBox
			(
				const Pln_CmpEdge& theEdge
			);

		static TnbCad2d_EXPORT Entity2d_Box
			RetrieveBoundingBox
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Wire>>
			RetrieveWires
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Wire>>
			RetrieveWiresNonManifold
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
				const Standard_Boolean checkManifold = Standard_True,
				const Standard_Integer verbose = 0
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Vertex>> 
			RetrieveVertices
			(
				const Pln_Wire&
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Vertex>>
			RetrieveVertices
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveEdges
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		//- an exception will be thrown if the curve is not bounded
		static TnbCad2d_EXPORT std::shared_ptr<Geom2dAPI_InterCurveCurve>
			Intersection
			(
				const Handle(Geom2d_Curve)& theCurve0,
				const Handle(Geom2d_Curve)& theCurve1,
				const Standard_Real theTol = 1.0E-6
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Vertex>
			Intersection
			(
				const std::shared_ptr<Pln_Edge>& theEdge0,
				const std::shared_ptr<Pln_Edge>& theEdge1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			ConvertToTrimmedCurve
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theU0,
				const Standard_Real theU1);

		//- an exception will be thrown if the curve is not bounded
		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			ConvertToBSpline
			(
				const Handle(Geom2d_Curve)& theCurve
			);

		static TnbCad2d_EXPORT std::shared_ptr<Entity2d_Triangulation>
			ParametricTriangulation
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Standard_Integer theNx,
				const Standard_Integer theNy
			);

		static TnbCad2d_EXPORT Entity2d_Box
			BoundingBox
			(
				const Bnd_Box2d& theBox
			);

		//- an exception will be thrown if the curve is not bounded
		static TnbCad2d_EXPORT Bnd_Box2d
			BoundingBox
			(
				const Handle(Geom2d_Curve)& theCurve
			);

		static TnbCad2d_EXPORT Bnd_Box2d
			BoundingBox
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theU0,
				const Standard_Real theU1
			);

		static TnbCad2d_EXPORT Entity2d_Box 
			BoundingBox
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
			);

		//- an exception will be thrown if the curve is not bounded and the x exceeds the boundary
		static TnbCad2d_EXPORT void
			SplitCurve
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theX,
				Handle(Geom2d_Curve)& theC0,
				Handle(Geom2d_Curve)& theC1
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Curve>>
			RetrieveCurves
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveEdges
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveEdges
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveMergedEdges
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveMergedEdges
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		//- WARNING! make sure the object is manifold then call this method
		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Wire>>
			RetrieveWires
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves, 
				const Standard_Real theMinTol, 
				const Standard_Real theMaxTol
			);

		//- WARNING! make sure the object is manifold then call this method
		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Wire>>
			RetrieveWires
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Pln_Wire> FillGaps(const std::shared_ptr<Pln_Wire>& theWire, const Standard_Real tol);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Wire>
			RetrieveWire
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_CmpEdge> 
			RetrieveCompoundEdge
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

		static TnbCad2d_EXPORT void
			SameSense
			(
				const std::shared_ptr<Pln_CmpEdge>& theEdge
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Wire>
			RetrieveOuterWire
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Cad2d_Plane>>
			RetrievePlanes
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theWires,
				const gp_Ax2& theAx
			);

		// the node is on the edge [1/25/2022 Amir]
		// - the function returns the next node on the edge
		static TnbCad2d_EXPORT std::shared_ptr<Pln_Vertex> 
			NextNode
			(
				const std::shared_ptr<Pln_Vertex>& theNode,
				const std::shared_ptr<Pln_Edge>&
			);

		// the node is on the edge [1/25/2022 Amir]
		// - the function returns the next edge that has the common node, theNode, with theEdge.
		// - WARNING: the node must be manifold; an exception will be thrown, otherwise.
		static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> 
			NextEdge
			(
				const std::shared_ptr<Pln_Edge>& theEdge,
				const std::shared_ptr<Pln_Vertex>& theNode
			);

		// Marching on the edges while the vertices are manifold [1/25/2022 Amir]
		static std::tuple
			<
			std::vector<std::shared_ptr<Pln_Edge>>,
			std::shared_ptr<Pln_Vertex>,
			std::shared_ptr<Pln_Vertex>
			> 
			MarchOnEdges
			(
				const std::shared_ptr<Pln_Vertex>& theVertex, 
				const std::shared_ptr<Pln_Edge>& theDirection
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
			ForwardEdge
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
			BackwardEdge
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
			MakeConsecutive
			(
				const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
				const Standard_Real theTol
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Vertex>
			MergeTwoVertex(const std::shared_ptr<Pln_Vertex>& theVtx0, const std::shared_ptr<Pln_Vertex>& theVtx1, const Standard_Real theTol);

		static TnbCad2d_EXPORT void
			SortWires
			(
				std::vector<std::shared_ptr<Pln_Wire>>& theWires
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Vertex>
			Vertex
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
			Edge
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
			Curve
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
			Ring
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			Plane
			(
				const std::shared_ptr<Pln_Entity>& theEnt
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Vertex>> RetrieveVertices(const std::shared_ptr<Pln_Entity>& theEnt);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Curve>> RetrieveCurves(const std::shared_ptr<Pln_Entity>& theEnt);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>> RetrieveEdges(const std::shared_ptr<Pln_Entity>& theEnt);

		static TnbCad2d_EXPORT std::vector<TopoDS_Edge>
			RetrieveEdges
			(
				const TopoDS_Shape& theEdges
			);

		static TnbCad2d_EXPORT std::shared_ptr<Entity2d_Chain> RetrieveTriangulation(const Pln_Edge&);
		static TnbCad2d_EXPORT std::shared_ptr<Entity2d_Chain> RetrieveTriangulation(const Pln_Wire&);

		static TnbCad2d_EXPORT std::vector<Handle(Geom2d_Curve)>
			RetrieveParaCurves
			(
				const std::vector<TopoDS_Edge>& theEdges,
				const gp_Ax2& theSystem
			);

		static TnbCad2d_EXPORT void
			ImportToCorner
			(
				const std::shared_ptr<Pln_Vertex>& theVtx,
				Geo_AdTree<std::shared_ptr<cad2dLib::Modeler_Corner>>& theCorners
			);

		static TnbCad2d_EXPORT void RetrieveInnerOuterWires
		(
			std::list<std::shared_ptr<Pln_Wire>>& theWires,
			std::shared_ptr<Pln_Wire>& theOuter, 
			std::vector<std::shared_ptr<Pln_Wire>>& theInners
		);

		static TnbCad2d_EXPORT void SetPrecision
		(
			const std::shared_ptr<Pln_Wire>&, 
			const Standard_Real theOffsetTol = Precision::Confusion()
		);

		static TnbCad2d_EXPORT void PlaceVertices(const std::shared_ptr<Pln_Wire>&);

		static TnbCad2d_EXPORT void PlaceVertex(const std::shared_ptr<Pln_Vertex>&);

		static TnbCad2d_EXPORT void CheckManifold
		(
			const std::shared_ptr<Pln_Wire>&
		);
		
	};
}

#endif // !_Pln_Tools_Header

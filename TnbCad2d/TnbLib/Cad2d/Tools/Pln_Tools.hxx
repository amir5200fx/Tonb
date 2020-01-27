#pragma once
#ifndef _Pln_Tools_Header
#define _Pln_Tools_Header

#include <Standard_Handle.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>

#include <vector>
#include <memory>

class gp_Ax2d;
class gp_Ax22d;
class Bnd_Box2d;
class Geom2d_Curve;
class Geom2dAPI_InterCurveCurve;

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_CmpEdge;

	class Pln_Tools
	{

	public:

		static Standard_Real Distance(const Pnt2d& theCoord, const Handle(Geom2d_Curve)& theCurve);

		static Standard_Real Distance(const Pnt2d& theCoord, const Handle(Geom2d_Curve)& theCurve, Standard_Real& theParameter);

		static std::shared_ptr<Pln_CmpEdge> MakeCompoundEdge
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
		);

		//- an exception will be thrown if the curve is not bounded
		static std::shared_ptr<Geom2dAPI_InterCurveCurve>
			Intersection
			(
				const Handle(Geom2d_Curve)& theCurve0,
				const Handle(Geom2d_Curve)& theCurve1,
				const Standard_Real theTol = 1.0E-6
			);

		static Handle(Geom2d_Curve)
			ConvertToTrimmedCurve
			(
				const Handle(Geom2d_Curve)& theCurve,
				const Standard_Real theU0,
				const Standard_Real theU1);

		static std::shared_ptr<Entity2d_Triangulation>
			ParametricTriangulation
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Standard_Integer theNx,
				const Standard_Integer theNy
			);

		static Entity2d_Box BoundingBox(const Bnd_Box2d& theBox);

		//- an exception will be thrown if the curve is not bounded
		static Bnd_Box2d BoundingBox
		(
			const Handle(Geom2d_Curve)& theCurve
		);

		static Bnd_Box2d BoundingBox
		(
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theU0,
			const Standard_Real theU1
		);

		//- an exception will be thrown if the curve is not bounded and the x exceeds the boundary
		static void SplitCurve
		(
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theX,
			Handle(Geom2d_Curve)& theC0,
			Handle(Geom2d_Curve)& theC1
		);
	};
}

#endif // !_Pln_Tools_Header

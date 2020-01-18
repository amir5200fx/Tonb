#pragma once
#ifndef _Pln_CurveTools_Header
#define _Pln_CurveTools_Header

#include <Standard_Handle.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>

class gp_Ax2d;
class gp_Ax22d;
class Bnd_Box2d;
class Geom2d_Curve;
class Geom2dAPI_InterCurveCurve;

namespace tnbLib
{

	class Pln_CurveTools
	{

	public:

		static Handle(Geom2d_Curve)
			MakeSegment
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static Handle(Geom2d_Curve)
			MakeCircle
			(
				const gp_Ax22d& A,
				const Standard_Real Radius
			);

		static Handle(Geom2d_Curve)
			MakeCircle
			(
				const gp_Ax2d& A,
				const Standard_Real Radius,
				const Standard_Boolean Sense = Standard_True
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
	};
}

#endif // !_Pln_CurveTools_Header

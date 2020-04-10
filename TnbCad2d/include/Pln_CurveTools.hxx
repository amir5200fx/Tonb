#pragma once
#ifndef _Pln_CurveTools_Header
#define _Pln_CurveTools_Header

#include <Standard_Handle.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <OFstream.hxx>

class gp_Ax2d;
class gp_Ax22d;
class Bnd_Box2d;
class Geom2d_Curve;
class Geom2dAPI_InterCurveCurve;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Vec2d;

	class Pln_CurveTools
	{

	public:

		static Handle(Geom2d_Curve)
			Interpolation
			(
				const std::vector<Pnt2d>& theQ, 
				const Standard_Boolean thePeriodic = Standard_False,
				const Standard_Real theTol = 1.0E-6
			);

		static Handle(Geom2d_Curve) 
			Interpolation
			(
				const std::vector<Pnt2d>& theQ, 
				const Vec2d& theFirst, 
				const Vec2d& theLast,
				const Standard_Boolean thePeriodic = Standard_False,
				const Standard_Real theTol = 1.0E-6,
				const Standard_Boolean theScale = Standard_True
			);

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

		static void 
			ExportToPlt
			(
				const Handle(Geom2d_Curve)& theCurve,
				OFstream& File,
				const Standard_Integer n = 40
			);
	};
}

#endif // !_Pln_CurveTools_Header

#pragma once
#ifndef _Pln_CurveTools_Header
#define _Pln_CurveTools_Header

#include <Standard_Handle.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Cad2d_Module.hxx>
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

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			Trim
			(
				const Handle(Geom2d_Curve), 
				const Standard_Real theP0, 
				const Standard_Real theP1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			Interpolation
			(
				const std::vector<Pnt2d>& theQ, 
				const Standard_Boolean thePeriodic = Standard_False,
				const Standard_Real theTol = 1.0E-6
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			Interpolation
			(
				const std::vector<Pnt2d>& theQ, 
				const Vec2d& theFirst, 
				const Vec2d& theLast,
				const Standard_Boolean thePeriodic = Standard_False,
				const Standard_Real theTol = 1.0E-6,
				const Standard_Boolean theScale = Standard_True
			);

		/*static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeSegment
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircle
			(
				const gp_Ax22d& A,
				const Standard_Real Radius
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircle
			(
				const gp_Ax2d& A,
				const Standard_Real Radius,
				const Standard_Boolean Sense = Standard_True
			);*/

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeSegment
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircArc
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Pnt2d& theP2
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircArc
			(
				const Pnt2d& theP0,
				const Vec2d& theV0,
				const Pnt2d& theP1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircArc
			(
				const gp_Circ2d& theCirc,
				const Standard_Real theAlpha0,
				const Standard_Real theAlpha1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircArc
			(
				const gp_Circ2d& theCirc,
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeElipsArc
			(
				const gp_Elips2d& theElips,
				const Standard_Real theAlpha0,
				const Standard_Real theAlpha1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeElipsArc
			(
				const gp_Elips2d& theElips,
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeHyprArc
			(
				const gp_Hypr2d& theHypr,
				const Standard_Real theAlpha0,
				const Standard_Real theAlpha1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeHyprArc
			(
				const gp_Hypr2d& theHypr,
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeParbArc
			(
				const gp_Parab2d& theParab,
				const Standard_Real theAlpha0,
				const Standard_Real theAlpha1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeParabArc
			(
				const gp_Parab2d& theParab,
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircle
			(
				const gp_Circ2d& C
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircle
			(
				const gp_Circ2d& C,
				const Pnt2d& theP
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircle
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Pnt2d& theP2
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircle
			(
				const Pnt2d& theC,
				const Standard_Real theRadius
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeCircle
			(
				const Pnt2d& theC,
				const Pnt2d& theP
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeEllipse
			(
				const gp_Elips2d& E
			);

		static TnbCad2d_EXPORT Handle(Geom2d_Curve)
			MakeEllipse
			(
				const Pnt2d& theS0,
				const Pnt2d& theS1,
				const Pnt2d& theCenter
			);

		static TnbCad2d_EXPORT void
			ExportToPlt
			(
				const Handle(Geom2d_Curve)& theCurve,
				OFstream& File,
				const Standard_Integer n = 40
			);
	};
}

#endif // !_Pln_CurveTools_Header

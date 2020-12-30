#pragma once
#ifndef _Marine_Modeler_Tools_Header
#define _Marine_Modeler_Tools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Cad2d_Module.hxx>
#include <Marine_PlnCurveType.hxx>

#include <memory>
#include <vector>

class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;
class gp_Ax2d;
class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Vec2d;
	class Pln_Edge;
	class Pln_Ring;
	class Pln_Curve;

	namespace marineLib
	{

		class Modeler_Tools
		{

			/*Private Data*/


		public:

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Curve> 
				MakeCurve
				(
					const Handle(Geom2d_Curve)& geom, 
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Curve>
				MakeCurve
				(
					Handle(Geom2d_Curve)&& geom,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeEdge
				(
					const Handle(Geom2d_Curve)& geom,
					const Pnt2d& p0,
					const Pnt2d& p1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeRing
				(
					const Handle(Geom2d_Curve)& geom,
					const Pnt2d& theP,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeSegment
				(
					const Pnt2d& theP0,
					const Pnt2d& theP1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeSegment
				(
					const Pnt2d& theP0,
					const Standard_Real theAngle,
					const Standard_Real theLength,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const Pnt2d& theP0,
					const Pnt2d& theP1,
					const Pnt2d& theP2,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const Pnt2d& theP0,
					const Vec2d& theV0,
					const Pnt2d& theP1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const gp_Circ2d& theCirc,
					const Standard_Real theAlpha0,
					const Standard_Real theAlpha1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const gp_Circ2d& theCirc,
					const Pnt2d& theP0,
					const Pnt2d& theP1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeElipsArc
				(
					const gp_Elips2d& theElips,
					const Standard_Real theAlpha0,
					const Standard_Real theAlpha1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeElipsArc
				(
					const gp_Elips2d& theElips,
					const Pnt2d& theP0,
					const Pnt2d& theP1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeHyprArc
				(
					const gp_Hypr2d& theHypr,
					const Standard_Real theAlpha0,
					const Standard_Real theAlpha1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeHyprArc
				(
					const gp_Hypr2d& theHypr,
					const Pnt2d& theP0,
					const Pnt2d& theP1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeParbArc
				(
					const gp_Parab2d& theParab,
					const Standard_Real theAlpha0,
					const Standard_Real theAlpha1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeParabArc
				(
					const gp_Parab2d& theParab,
					const Pnt2d& theP0,
					const Pnt2d& theP1,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const gp_Circ2d& C,
					const curveType t
				);

			//! Make a Circle from Geom2d <TheCirc> parallel to another
			//! Circ <Circ> and passing through a Pnt <Point>.
			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const gp_Circ2d& C,
					const Pnt2d& theP,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const Pnt2d& theP0,
					const Pnt2d& theP1,
					const Pnt2d& theP2,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const Pnt2d& theC,
					const Standard_Real theRadius,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const Pnt2d& theC,
					const Pnt2d& theP,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeEllipse
				(
					const gp_Elips2d& E,
					const curveType t
				);

			//! Make an Ellipse centered on the point Center, where
			//! -   the major axis of the ellipse is defined by Center and S1,
			//! -   its major radius is the distance between Center and S1, and
			//! -   its minor radius is the distance between S2 and the major axis.
			//! The implicit orientation of the ellipse is:
			//! -   the sense defined by Axis or E,
			//! -   the sense defined by points Center, S1 and S2,
			//! -   the trigonometric sense if Sense is not given or is true, or
			//! -   the opposite sense if Sense is false.
			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeEllipse
				(
					const Pnt2d& theS0,
					const Pnt2d& theS1,
					const Pnt2d& theCenter,
					const curveType t
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				Interpolation
				(
					const std::vector<Pnt2d>& theQ,
					const curveType t,
					const Standard_Boolean thePeriodic = Standard_False,
					const Standard_Real theTol = 1.0E-6
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				Interpolation
				(
					const std::vector<Pnt2d>& theQ,
					const Vec2d& theFirst,
					const Vec2d& theLast,
					const curveType t,
					const Standard_Boolean thePeriodic = Standard_False,
					const Standard_Real theTol = 1.0E-6,
					const Standard_Boolean theScale = Standard_True
				);

			static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
				MakeRectangular
				(
					const Pnt2d& theP0,
					const Pnt2d& theP1,
					const curveType t
				);

			static TnbCad2d_EXPORT void 
				CheckCurveType
				(
					const std::shared_ptr<Pln_Curve>& theCurve,
					const curveType t
				);

		};
	}
}

#endif // !_Marine_Modeler_Tools_Header

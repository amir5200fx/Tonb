#pragma once
#ifndef _Cad2d_Modeler_Tools_Header
#define _Cad2d_Modeler_Tools_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;
class gp_Ax2d;

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Vec2d;
	class Pln_Vertex;
	class Pln_Edge;
	class Pln_Ring;
	class Cad2d_Plane;

	namespace cad2dLib
	{

		class Modeler_Tools
		{



		public:

			static std::shared_ptr<Pln_Edge>
				MakeSegment
				(
					const Pnt2d& theP0,
					const Pnt2d& theP1
				);

			static std::shared_ptr<Pln_Edge> 
				MakeSegment
				(
					const Pnt2d& theP0, 
					const Standard_Real theAngle, 
					const Standard_Real theLength
				);

			static std::shared_ptr<Pln_Edge> 
				MakeCircArc
				(
					const Pnt2d& theP0, 
					const Pnt2d& theP1,
					const Pnt2d& theP2
				);

			static std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const Pnt2d& theP0, 
					const Vec2d& theV0, 
					const Pnt2d& theP1
				);

			static std::shared_ptr<Pln_Edge> 
				MakeCircArc
				(
					const gp_Circ2d& theCirc,
					const Standard_Real theAlpha0, 
					const Standard_Real theAlpha1
				);

			static std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const gp_Circ2d& theCirc,
					const Pnt2d& theP0,
					const Pnt2d& theP1
				);

			static std::shared_ptr<Pln_Edge> 
				MakeElipsArc
				(
					const gp_Elips2d& theElips, 
					const Standard_Real theAlpha0, 
					const Standard_Real theAlpha1
				);

			static std::shared_ptr<Pln_Edge>
				MakeElipsArc
				(
					const gp_Elips2d& theElips,
					const Pnt2d& theP0,
					const Pnt2d& theP1
				);

			static std::shared_ptr<Pln_Edge> 
				MakeHyprArc
				(
					const gp_Hypr2d& theHypr,
					const Standard_Real theAlpha0, 
					const Standard_Real theAlpha1
				);

			static std::shared_ptr<Pln_Edge>
				MakeHyprArc
				(
					const gp_Hypr2d& theHypr,
					const Pnt2d& theP0,
					const Pnt2d& theP1
				);

			static std::shared_ptr<Pln_Edge> 
				MakeParbCurve
				(
					const gp_Parab2d& theParab,
					const Standard_Real theAlpha0, 
					const Standard_Real theAlpha1
				);

			static std::shared_ptr<Pln_Edge> 
				MakeParabCurve
				(
					const gp_Parab2d& theParab,
					const Pnt2d& theP0, 
					const Pnt2d& theP1
				);

			static std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const gp_Circ2d& C
				);

			//! Make a Circle from Geom2d <TheCirc> parallel to another
			//! Circ <Circ> and passing through a Pnt <Point>.
			static std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const gp_Circ2d& C,
					const Pnt2d& theP
				);

			static std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const Pnt2d& theP0, 
					const Pnt2d& theP1,
					const Pnt2d& theP2
				);

			static std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const Pnt2d& theC, 
					const Standard_Real theRadius
				);

			static std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const Pnt2d& theC, 
					const Pnt2d& theP
				);

			static std::shared_ptr<Pln_Ring>
				MakeEllipse
				(
					const gp_Elips2d& E
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
			static std::shared_ptr<Pln_Ring> 
				MakeEllipse
				(
					const Pnt2d& theS0,
					const Pnt2d& theS1, 
					const Pnt2d& theCenter
				);

			static std::vector<std::shared_ptr<Pln_Edge>>
				MakeRectangular(const Pnt2d& theP0, const Pnt2d& theP1);

			static std::vector<std::shared_ptr<Pln_Edge>>
				MakeRectangular(const gp_Ax2d& theAx, const Standard_Real dx, const Standard_Real dy);
		};
	}
}

#endif // !_Cad2d_Modeler_Tools_Header

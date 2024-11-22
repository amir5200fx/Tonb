#pragma once
#ifndef _Cad2d_Modeler_Tools_Header
#define _Cad2d_Modeler_Tools_Header

#include <Cad2d_Module.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

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
	class Pln_Vertex;
	class Pln_Edge;
	class Pln_Ring;
	class Pln_Wire;
	class Cad2d_Plane;

	namespace cad2dLib
	{

		// Forward Declarations
		class Modeler_Corner;
		class Modeler_Segment;
		class Modeler_SrchEng;

		class Modeler_Tools
		{

		public:

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> 
				MakeEdge
				(
					const Handle(Geom2d_Curve)& geom, 
					const Pnt2d& p0, 
					const Pnt2d& p1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring> 
				MakeRing
				(
					const Handle(Geom2d_Curve)& geom, 
					const Pnt2d& theP
				);

			static TnbCad2d_EXPORT std::shared_ptr<Modeler_Segment>
				HasRing
				(
					const std::shared_ptr<Modeler_Corner>& theCrn
				);

			static TnbCad2d_EXPORT std::shared_ptr<Modeler_Segment>
				IsSegment
				(
					const std::shared_ptr<Modeler_Corner>& theCrn0, 
					const std::shared_ptr<Modeler_Corner>& theCrn1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeSegment
				(
					const Pnt2d& theP0,
					const Pnt2d& theP1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeSegment
				(
					const Pnt2d& theP0, 
					const Standard_Real theAngle, 
					const Standard_Real theLength
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const Pnt2d& theP0, 
					const Pnt2d& theP1,
					const Pnt2d& theP2
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const Pnt2d& theP0, 
					const Vec2d& theV0, 
					const Pnt2d& theP1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const gp_Circ2d& theCirc,
					const Standard_Real theAlpha0, 
					const Standard_Real theAlpha1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeCircArc
				(
					const gp_Circ2d& theCirc,
					const Pnt2d& theP0,
					const Pnt2d& theP1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeElipsArc
				(
					const gp_Elips2d& theElips, 
					const Standard_Real theAlpha0, 
					const Standard_Real theAlpha1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeElipsArc
				(
					const gp_Elips2d& theElips,
					const Pnt2d& theP0,
					const Pnt2d& theP1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeHyprArc
				(
					const gp_Hypr2d& theHypr,
					const Standard_Real theAlpha0, 
					const Standard_Real theAlpha1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeHyprArc
				(
					const gp_Hypr2d& theHypr,
					const Pnt2d& theP0,
					const Pnt2d& theP1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeParbArc
				(
					const gp_Parab2d& theParab,
					const Standard_Real theAlpha0, 
					const Standard_Real theAlpha1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge>
				MakeParabArc
				(
					const gp_Parab2d& theParab,
					const Pnt2d& theP0, 
					const Pnt2d& theP1
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const gp_Circ2d& C
				);

			//! Make a Circle from Geom2d <TheCirc> parallel to another
			//! Circ <Circ> and passing through a Pnt <Point>.
			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const gp_Circ2d& C,
					const Pnt2d& theP
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const Pnt2d& theP0, 
					const Pnt2d& theP1,
					const Pnt2d& theP2
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const Pnt2d& theC, 
					const Standard_Real theRadius
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeCircle
				(
					const Pnt2d& theC, 
					const Pnt2d& theP
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
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
			static TnbCad2d_EXPORT std::shared_ptr<Pln_Ring>
				MakeEllipse
				(
					const Pnt2d& theS0,
					const Pnt2d& theS1, 
					const Pnt2d& theCenter
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> 
				Interpolation
				(
					const std::vector<Pnt2d>& theQ, 
					const Standard_Boolean thePeriodic = Standard_False, 
					const Standard_Real theTol = 1.0E-6
				);

			static TnbCad2d_EXPORT std::shared_ptr<Pln_Edge> 
				Interpolation
				(
					const std::vector<Pnt2d>& theQ,
					const Vec2d& theFirst, 
					const Vec2d& theLast, 
					const Standard_Boolean thePeriodic = Standard_False, 
					const Standard_Real theTol = 1.0E-6,
					const Standard_Boolean theScale = Standard_True
				);

			static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
				MakeRectangular
				(
					const Pnt2d& theP0,
					const Pnt2d& theP1
				);

			static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
				MakeRectangular(const gp_Ax2d& theAx, const Standard_Real dx, const Standard_Real dy);

			static TnbCad2d_EXPORT Standard_Real
				CalcMaxTolerance
				(
					const Pnt2d& theCentre,
					const std::shared_ptr<Modeler_Corner>& theCorner
				);

			static TnbCad2d_EXPORT std::vector<std::shared_ptr<Modeler_Segment>> TrackRing(const std::shared_ptr<Modeler_Corner>& theCrn);

			static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Wire>> RetrieveWires(const std::vector<std::shared_ptr<Modeler_Corner>>& theCorners);

			//- WARNING! the edges and the vertices will be removed from the corners
			static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
				MakeConsecutive
				(
					const std::vector<std::shared_ptr<Modeler_Corner>>& theCorners
				);

			static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
				MakeConsecutive
				(
					const std::vector<std::shared_ptr<Pln_Edge>>& theEdges, 
					const Standard_Real theTol
				);

			static TnbCad2d_EXPORT std::vector<std::shared_ptr<Modeler_Corner>>
				MakeCorners
				(
					const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
					const Standard_Real theTol
				);

			static TnbCad2d_EXPORT std::vector<std::shared_ptr<Pln_Edge>>
				ConstructMergedEdges
				(
					const std::vector<std::shared_ptr<Modeler_Corner>>& theCorners
				);

			static TnbCad2d_EXPORT void
				SmoothCorner
				(
					const std::shared_ptr<Modeler_Corner>& theCorner
				);

			static TnbCad2d_EXPORT void
				CalcCornerTolerances
				(
					const std::shared_ptr<Modeler_Corner>& theCorner
				);

			static TnbCad2d_EXPORT void
				CalcCornerTolerances
				(
					const std::vector<std::shared_ptr<Modeler_Corner>>& theCorners
				);

			static TnbCad2d_EXPORT void
				SetCoordToCorner
				(
					const Pnt2d& theCoord, 
					const std::shared_ptr<Modeler_Corner>& theCorner
				);

			static TnbCad2d_EXPORT void
				ImportVtxToCorner
				(
					const std::shared_ptr<Pln_Vertex>& theVtx,
					const std::shared_ptr<Modeler_Corner>& theCorner
				);

			//- WARNING! it should be no intersection of the vertex with the ones at the engine
			//- For more robust version, use "RegisterVtxToSearchEngine()" function
			static TnbCad2d_EXPORT void
				ImportVtxToSrchEngine
				(
					const std::shared_ptr<Pln_Vertex>& theVtx, 
					Modeler_SrchEng& theEngine
				);

			static TnbCad2d_EXPORT void
				RegisterVtxToSearchEngine
				(
					const std::shared_ptr<Pln_Vertex>& theVtx,
					Modeler_SrchEng& theEngine
				);
		};
	}
}

#endif // !_Cad2d_Modeler_Tools_Header

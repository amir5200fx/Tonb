#pragma once
#ifndef _Cad2d_Modeler_Tools_Header
#define _Cad2d_Modeler_Tools_Header

#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Vec2d;
	class Pln_Vertex;
	class Pln_Edge;

	namespace cad2dLib
	{

		class Modeler_Tools
		{

		public:

			std::shared_ptr<Pln_Edge> Segment(const Pnt2d& theP0, const Pnt2d& theP1);

			std::shared_ptr<Pln_Edge> Segment(const std::shared_ptr<Pln_Vertex>& theVtx, const Standard_Real theAngle, const Standard_Real theLength);

			std::shared_ptr<Pln_Edge> CircArc(const Pnt2d& theP0, const Pnt2d& theP1, const Pnt2d& theP2);

			std::shared_ptr<Pln_Edge> CircArc(const Pnt2d& theP0, const Vec2d& theV0, const Pnt2d& theP1);

			std::shared_ptr<Pln_Edge> CircArc(const Pnt2d& theCentre, const Standard_Real theRaius, const Standard_Real theAlpha0, const Standard_Real theAlpha1);


		};
	}
}

#endif // !_Cad2d_Modeler_Tools_Header

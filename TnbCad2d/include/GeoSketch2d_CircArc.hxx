#pragma once
#ifndef _GeoSketch2d_CircArc_Header
#define _GeoSketch2d_CircArc_Header

#include <Cad2d_GeoSketch.hxx>

class gp_Circ2d;

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;

	class GeoSketch2d_CircArc
		: public Cad2d_GeoSketch
	{

		/*Private Data*/

	public:

		GeoSketch2d_CircArc
		(
			const gp_Circ2d& theCirc,
			const Standard_Real theAlpha0,
			const Standard_Real theAlpha1, 
			const Standard_Boolean theSense = Standard_True
		);

		GeoSketch2d_CircArc
		(
			const gp_Circ2d& theCirc,
			const Pnt2d& theP,
			const Standard_Real theAlpha,
			const Standard_Boolean theSense = Standard_True
		);

		GeoSketch2d_CircArc
		(
			const gp_Circ2d& theCirc,
			const Pnt2d& theP0,
			const Pnt2d& theP1,
			const Standard_Boolean theSense = Standard_True
		);

		GeoSketch2d_CircArc
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1,
			const Pnt2d& theP2
		);
	};
}

#endif // !_GeoSketch2d_CircArc_Header

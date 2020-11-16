#pragma once
#ifndef _GeoSketch2d_ParbcArc_Header
#define _GeoSketch2d_ParbcArc_Header

#include <Cad2d_GeoSketch.hxx>

class gp_Parab2d;

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;

	class GeoSketch2d_ParbcArc
		: public Cad2d_GeoSketch
	{

		/*Private Data*/

	public:

		TnbCad2d_EXPORT GeoSketch2d_ParbcArc
		(
			const gp_Parab2d& theParab,
			const Standard_Real theAlpha0,
			const Standard_Real theAlpha1,
			const Standard_Boolean theSense = Standard_True
		);

		TnbCad2d_EXPORT GeoSketch2d_ParbcArc
		(
			const gp_Parab2d& theParab, 
			const Pnt2d& theP, 
			const Standard_Real theAlpha,
			const Standard_Boolean theSense = Standard_True
		);

		TnbCad2d_EXPORT GeoSketch2d_ParbcArc
		(
			const gp_Parab2d& theParab,
			const Pnt2d& theP0,
			const Pnt2d& theP1, 
			const Standard_Boolean theSense = Standard_True
		);
	};
}

#endif // !_GeoSketch2d_ParbcArc_Header

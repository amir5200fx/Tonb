#pragma once
#ifndef _GeoSketch2d_EllipcArc_Header
#define _GeoSketch2d_EllipcArc_Header

#include <Cad2d_GeoSketch.hxx>

class gp_Elips2d;

namespace tnbLib
{

	class GeoSketch2d_EllipcArc
		: public Cad2d_GeoSketch
	{

		/*Private Data*/

	public:

		GeoSketch2d_EllipcArc
		(
			const gp_Elips2d& theElips, 
			const Standard_Real theAlpha0,
			const Standard_Real theAlpha1, 
			const Standard_Real theSense = Standard_True
		);


	};
}

#endif // !_GeoSketch2d_EllipcArc_Header

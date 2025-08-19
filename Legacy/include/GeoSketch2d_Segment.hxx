#pragma once
#ifndef _GeoSketch2d_Segment_Header
#define _GeoSketch2d_Segment_Header

#include <Cad2d_GeoSketch.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Dir2d;

	class GeoSketch2d_Segment
		: public Cad2d_GeoSketch
	{

		/*Private Data*/

	public:

		TnbCad2d_EXPORT GeoSketch2d_Segment
		(
			const Pnt2d& theP0, 
			const Pnt2d& theP1
		);

		TnbCad2d_EXPORT GeoSketch2d_Segment
		(
			const Pnt2d& theP0,
			const Dir2d& theDir, 
			const Standard_Real theLength
		);

		TnbCad2d_EXPORT GeoSketch2d_Segment
		(
			const Pnt2d& theP0, 
			const Standard_Real theAngle, 
			const Standard_Real theLength
		);
	};
}

#endif // !_GeoSketch2d_Segment_Header

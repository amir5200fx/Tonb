#pragma once
#ifndef _GeoSketch2d_Ellipse_Header
#define _GeoSketch2d_Ellipse_Header

#include <Cad2d_GeoSketch.hxx>

class gp_Ax2d;
class gp_Ax22d;

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;

	class GeoSketch2d_Ellipse
		: public Cad2d_GeoSketch
	{

		/*Private Data*/

	public:

		TnbCad2d_EXPORT GeoSketch2d_Ellipse
		(
			const gp_Ax2d& theAxis,
			const Standard_Real theMajorRadius,
			const Standard_Real theMinorRadius, 
			const Standard_Boolean theSense = Standard_True
		);

		TnbCad2d_EXPORT GeoSketch2d_Ellipse
		(
			const gp_Ax22d& theAxis,
			const Standard_Real theMajorRadius,
			const Standard_Real theMinorRadius
		);
	};
}

#endif // !_GeoSketch2d_Ellipse_Header

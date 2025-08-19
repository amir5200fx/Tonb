#pragma once
#ifndef _GeoSketch2d_Circle_Header
#define _GeoSketch2d_Circle_Header

#include <Cad2d_GeoSketch.hxx>
#include <Cad2d_Module.hxx>

class gp_Ax2d;
class gp_Ax22d;

namespace tnbLib
{

	class GeoSketch2d_Circle
		: public Cad2d_GeoSketch
	{

		/*Private Data*/

	public:

		TnbCad2d_EXPORT GeoSketch2d_Circle
		(
			const gp_Ax2d& theAxis,
			const Standard_Real theRadius,
			const Standard_Boolean theSense = Standard_True
		);

		TnbCad2d_EXPORT GeoSketch2d_Circle
		(
			const gp_Ax22d& theAxis,
			const Standard_Real theRadius
		);

	};
}

#endif // !_GeoSketch2d_Circle_Header

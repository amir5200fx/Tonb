#pragma once
#ifndef _Cad2d_Sketch_Header
#define _Cad2d_Sketch_Header

#include <Geo_AdTree.hxx>

#include <gp_Ax2d.hxx>

namespace tnbLib
{

	class Cad2d_Sketch
	{

		/*Private Data*/

		gp_Ax2d theSystem_;

	public:

		Cad2d_Sketch(const gp_Ax2d& theSystem);

		const auto& System() const
		{
			return theSystem_;
		}
	};
}

#endif // !_Cad2d_Sketch_Header

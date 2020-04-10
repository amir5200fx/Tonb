#pragma once
#ifndef _HsModeler_Box_Header
#define _HsModeler_Box_Header

#include <HsModeler_Shape.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class HsModeler_Box
		: public HsModeler_Shape
	{

		/*Private Data*/

	public:

		HsModeler_Box(const Standard_Real dx, const Standard_Real dy, const Standard_Real dz, const gp_Ax2& theSystem);

		HsModeler_Box(const Pnt3d& theP0, const Pnt3d& theP1, const gp_Ax2& theSystem);


	};
}

#endif // !_HsModeler_Box_Header

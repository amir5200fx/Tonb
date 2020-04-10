#pragma once
#ifndef _HsModeler_Sphere_Header
#define _HsModeler_Sphere_Header

#include <HsModeler_Shape.hxx>

namespace tnbLib
{

	class HsModeler_Sphere
		: public HsModeler_Sphere
	{

		/*Private Data*/

	public:

		HsModeler_Sphere(const Standard_Real theRadius, const gp_Ax2& theSystem);
	};
}

#endif // !_HsModeler_Sphere_Header

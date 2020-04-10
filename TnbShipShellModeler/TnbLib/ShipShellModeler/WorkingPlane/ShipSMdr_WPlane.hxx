#pragma once
#ifndef _ShipSMdr_WPlane_Header
#define _ShipSMdr_WPlane_Header

#include <ShipSMdr_Entity.hxx>
#include <Global_AccessMethod.hxx>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	class ShipSMdr_WPlane
		: public ShipSMdr_Entity
	{

		/*Private Data*/

		gp_Ax2 theSystem_;

	public:

		ShipSMdr_WPlane();

		ShipSMdr_WPlane(const Standard_Integer theIndex);

		ShipSMdr_WPlane(const Standard_Integer theIndex, const word& theName);

		
		//- Macros
		GLOBAL_ACCESS_SINGLE(gp_Ax2, System)
	};
}

#endif // !_ShipSMdr_WPlane_Header

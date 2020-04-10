#pragma once
#ifndef _HsVessel_Tank_Header
#define _HsVessel_Tank_Header

#include <Marine_TankBody.hxx>

namespace tnbLib
{

	class HsVessel_Tank
		: public Marine_TankBody
	{

		/*Private Data*/

	public:

		HsVessel_Tank();

		HsVessel_Tank(const Standard_Integer theIndex);

		HsVessel_Tank(const Standard_Integer theIndex, const word& theName);
	};
}

#endif // !_HsVessel_Tank_Header

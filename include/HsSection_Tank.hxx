#pragma once
#ifndef _HsSection_Tank_Header
#define _HsSection_Tank_Header

#include <HsVessel_Section.hxx>

namespace tnbLib
{

	class HsSection_Tank
		: public HsVessel_Section
	{

		/*Private Data*/

	public:

		HsSection_Tank();


		Standard_Boolean IsTank() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_HsSection_Tank_Header

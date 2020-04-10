#pragma once
#ifndef _HsSection_Sail_Header
#define _HsSection_Sail_Header

#include <HsVessel_Section.hxx>

namespace tnbLib
{

	class HsSection_Sail
		: public HsVessel_Section
	{

		/*Private Data*/

	public:

		HsSection_Sail();


		Standard_Boolean IsSail() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_HsSection_Sail_Header

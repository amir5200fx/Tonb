#pragma once
#ifndef _HsSection_Deep_Header
#define _HsSection_Deep_Header

#include <HsSection_Wetted.hxx>

namespace tnbLib
{

	class HsSection_Deep
		: public HsSection_Wetted
	{

		/*Private Data*/

	public:

		HsSection_Deep();


		Standard_Boolean IsDeep() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_HsSection_Deep_Header

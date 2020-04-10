#pragma once
#ifndef _HsSection_Dry_Header
#define _HsSection_Dry_Header

#include <HsEntity_HullSection.hxx>

namespace tnbLib
{

	class HsSection_Dry
		: public HsEntity_HullSection
	{

		/*Private Data*/

	public:

		HsSection_Dry();


		Standard_Real Beam() const;

		Standard_Boolean IsDry() const override
		{
			return Standard_True;
		}
	};
}

#endif // !_HsSection_Dry_Header

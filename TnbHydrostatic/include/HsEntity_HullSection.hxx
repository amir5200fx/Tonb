#pragma once
#ifndef _HsEntity_HullSection_Header
#define _HsEntity_HullSection_Header

#include <HsVessel_Section.hxx>

namespace tnbLib
{

	class HsEntity_HullSection
		: public HsVessel_Section
	{

		/*Private Data*/

	protected:

		HsEntity_HullSection();


	public:

		Standard_Boolean IsHull() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsWetted() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsDry() const
		{
			return Standard_False;
		}
	};
}

#endif // !_HsEntity_HullSection_Header

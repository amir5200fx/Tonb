#pragma once
#ifndef _HsSection_Wetted_Header
#define _HsSection_Wetted_Header

#include <HsEntity_HullSection.hxx>

namespace tnbLib
{

	class HsSection_Wetted
		: public HsEntity_HullSection
	{

		/*Private Data*/

	protected:

		HsSection_Wetted();

	public:

		Standard_Boolean IsWetted() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsDeep() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsWaterLine() const
		{
			return Standard_False;
		}

		Standard_Real Beam() const;
	};
}

#endif // !_HsSection_Wetted_Header

#pragma once
#ifndef _HsVessel_MonoSection_Header
#define _HsVessel_MonoSection_Header

#include <HsVessel_CmpSection.hxx>

namespace tnbLib
{

	class HsVessel_MonoSection
		: public HsVessel_CmpSection
	{

		/*Private Data*/

	public:

		HsVessel_MonoSection();

		HsVessel_MonoSection(const Standard_Integer theIndex);

		HsVessel_MonoSection(const Standard_Integer theIndex, const word& theName);

		Standard_Real mY() const;

		Standard_Real Y() const;

		Standard_Boolean IsMono() const override
		{
			return Standard_True;
		}

		static std::vector<std::shared_ptr<HsVessel_MonoSection>>
			RetrieveMonos
			(
				const HsVessel_CmpSection& theSection
			);

		static Standard_Integer
			NbMonos
			(
				const HsVessel_CmpSection& theSection
			);
	};
}

#endif // !_HsVessel_MonoSection_Header

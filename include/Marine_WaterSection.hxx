#pragma once
#ifndef _Marine_WaterSection_Header
#define _Marine_WaterSection_Header

#include <Marine_Section.hxx>

namespace tnbLib
{

	class Marine_WaterSection
		: public Marine_Section
	{

		/*Private Data*/

	public:

		Marine_WaterSection
		(
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Marine_WaterSection
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Marine_WaterSection
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Standard_Boolean IsWaterSection() const override
		{
			return Standard_True;
		}

		std::shared_ptr<Marine_Section> Copy() const override;
	};
}

#endif // !_Marine_WaterSection_Header

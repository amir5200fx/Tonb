#pragma once
#ifndef _HydStatic_hArmFormula_Header
#define _HydStatic_hArmFormula_Header

#include <HydStatic_Entity.hxx>

namespace tnbLib
{

	class HydStatic_hArmFormula
		: public HydStatic_Entity
	{

		/*Private Data*/

	protected:

		HydStatic_hArmFormula()
		{}

		HydStatic_hArmFormula
		(
			const Standard_Integer theIndex
		)
			: HydStatic_Entity(theIndex)
		{}

		HydStatic_hArmFormula
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: HydStatic_Entity(theIndex, theName)
		{}

	public:

		virtual Standard_Real Value(const Standard_Real thePhi) const = 0;

	};
}

#endif // !_HydStatic_hArmFormula_Header

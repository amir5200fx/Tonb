#pragma once
#ifndef _HydStatic_hArmFormula_Const_Header
#define _HydStatic_hArmFormula_Const_Header

#include <HydStatic_hArmFormula.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class hArmFormula_Const
			: public HydStatic_hArmFormula
		{

			/*Private Data*/

			Standard_Real theValue_;

		public:

			hArmFormula_Const(const Standard_Real theValue)
				: theValue_(theValue)
			{}

			hArmFormula_Const
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const Standard_Real theValue
			)
				: HydStatic_hArmFormula(theIndex, theName)
				, theValue_(theValue)
			{}


			Standard_Real Value(const Standard_Real thePhi) const override
			{
				return theValue_;
			}

		};
	}
}

#endif // !_HydStatic_hArmFormula_Const_Header

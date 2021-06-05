#pragma once
#ifndef _PtdModel_IntrplPars_Header
#define _PtdModel_IntrplPars_Header

#include <Standard_TypeDef.hxx>
#include <word.hxx>

#include <vector>
#include <map>

namespace tnbLib
{

	class PtdModel_IntrplPars
	{

		/*Private Data*/

		std::vector<Standard_Real> theX_;

		std::map<word, std::vector<Standard_Real>> theParameters_;

	public:

		//- default constructor

		PtdModel_IntrplPars()
		{}


		//- constructor


		//- public functions and operators

		const auto& X() const
		{
			return theX_;
		}

		const auto& Parameters() const
		{
			return theParameters_;
		}
	};
}

#endif // !_PtdModel_IntrplPars_Header

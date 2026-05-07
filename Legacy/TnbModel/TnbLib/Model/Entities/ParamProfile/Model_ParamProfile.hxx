#pragma once
#ifndef _Model_ParamProfile_Header
#define _Model_ParamProfile_Header

#include <Model_Module.hxx>
#include <Global_Named.hxx>

#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Model_ParamProfile
		: public Global_Named
	{

		/*Private Data*/


	protected:

		// default constructor [12/20/2022 Payvand]

		Model_ParamProfile()
		{}


		// constructors [12/20/2022 Payvand]


	public:

		// Public functions and operators [12/20/2022 Payvand]

		virtual Standard_Boolean IsComposite() const
		{
			return Standard_False;
		}

		virtual Standard_Real Lower() const = 0;
		virtual Standard_Real Upper() const = 0;

		TnbModel_EXPORT Standard_Real LowerValue() const;
		TnbModel_EXPORT Standard_Real UpperValue() const;

		TnbModel_EXPORT Standard_Boolean InsideSpan(const Standard_Real x) const;

		virtual Standard_Real Value(const Standard_Real) const = 0;
		TnbModel_EXPORT virtual std::vector<Standard_Real> Breacks() const;

	};
}

#endif // !_Model_ParamProfile_Header

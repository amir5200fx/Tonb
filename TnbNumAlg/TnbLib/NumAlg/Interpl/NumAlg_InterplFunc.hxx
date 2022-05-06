#pragma once
#ifndef _NumAlg_InterplFunc_Header
#define _NumAlg_InterplFunc_Header

#include <NumAlg_Module.hxx>
#include <Global_Done.hxx>

#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	class NumAlg_InterplFunc
		: public Global_Done
	{

		/*Private Data*/


	protected:

		// default constructor [4/29/2022 Amir]

		NumAlg_InterplFunc()
		{}

		// constructors [4/29/2022 Amir]


	public:

		// destructor [4/30/2022 Amir]

		virtual ~NumAlg_InterplFunc()
		{}

		// public functions and operators [4/29/2022 Amir]

		virtual Standard_Integer NbSamples() const = 0;
		virtual Standard_Real Value(const Standard_Real x) const = 0;

		virtual std::pair<Standard_Real, Standard_Real> Sample(const Standard_Integer theIndex) const = 0;
		virtual std::vector<std::pair<Standard_Real, Standard_Real>> RetrieveSamples() const = 0;


		static TnbNumAlg_EXPORT std::pair<Standard_Real, Standard_Real> 
			Mirror
			(
				const std::pair<Standard_Real, Standard_Real>&,
				const std::pair<Standard_Real, Standard_Real>& theTarget
			);

		static TnbNumAlg_EXPORT std::vector<std::pair<Standard_Real, Standard_Real>> 
			ReproduceOffsets
			(
				const std::vector<std::pair<Standard_Real, Standard_Real>>&
			);
	};
}

#endif // !_NumAlg_InterplFunc_Header

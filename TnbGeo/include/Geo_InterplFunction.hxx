#pragma once
#ifndef _Geo_InterplFunction_Header
#define _Geo_InterplFunction_Header

#include <Geo_Module.hxx>
#include <Global_TypeDef.hxx>

#include <vector>

namespace tnbLib
{

	class Geo_InterplFunction
	{

		/*Private Data*/

	protected:

		// default constructor [1/12/2022 Amir]

		Geo_InterplFunction()
		{}

		// constructors [1/12/2022 Amir]

	public:

		virtual ~Geo_InterplFunction()
		{}

		// public functions and operators [1/12/2022 Amir]

		virtual Standard_Integer NbSamples() const = 0;
		virtual Standard_Real Value(const Standard_Real x) const = 0;

		virtual std::pair<Standard_Real, Standard_Real> Sample(const Standard_Integer theIndex) const = 0;
		virtual std::vector<std::pair<Standard_Real, Standard_Real>> RetrieveSamples() const = 0;
	};
}

#endif // !_Geo_InterplFunction_Header

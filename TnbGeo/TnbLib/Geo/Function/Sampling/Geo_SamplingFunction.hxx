#pragma once
#ifndef _Geo_SamplingFunction_Header
#define _Geo_SamplingFunction_Header

#include <Standard_TypeDef.hxx>
#include <Geo_Module.hxx>

#include <vector>

namespace tnbLib
{

	class Geo_SamplingFunction
	{

		/*private Data*/

	protected:

		// default constructor [1/13/2022 Amir]

		Geo_SamplingFunction()
		{}


		// constructors [1/13/2022 Amir]

	public:

		virtual ~Geo_SamplingFunction()
		{}


		// public functions and operators [1/13/2022 Amir]

		virtual std::vector<Standard_Integer> 
			Samples
			(
				const Standard_Real x,
				const std::vector<Standard_Real>&
			) const = 0;

		virtual Standard_Real Interpolate(const Standard_Real x, const std::vector<std::pair<Standard_Real, Standard_Real>>&) const = 0;
	};
}

#endif // !_Geo_SamplingFunction_Header

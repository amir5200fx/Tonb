#pragma once
#ifndef _Geo_LinSamplingFunction_Header
#define _Geo_LinSamplingFunction_Header

#include <Geo_SamplingFunction.hxx>

namespace tnbLib
{

	class Geo_LinSamplingFunction
		: public Geo_SamplingFunction
	{

		/*Private Data*/

	public:

		// default constructor [1/13/2022 Amir]

		Geo_LinSamplingFunction()
		{}

		// constructors [1/13/2022 Amir]


		// override functions and operators [1/13/2022 Amir]

		TnbGeo_EXPORT std::vector<Standard_Integer> 
			Samples
			(
				const Standard_Real x,
				const std::vector<Standard_Real>&
			) const override;

		TnbGeo_EXPORT Standard_Real 
			Interpolate
			(
				const Standard_Real x, 
				const std::vector<std::pair<Standard_Real, Standard_Real>>&
			) const override;

		// public functions and operators [1/13/2022 Amir]
	};
}

#endif // !_Geo_LinSamplingFunction_Header

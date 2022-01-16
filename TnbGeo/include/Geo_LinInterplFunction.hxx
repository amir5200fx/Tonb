#pragma once
#ifndef _Geo_LinInterplFunction_Header
#define _Geo_LinInterplFunction_Header

#include <Geo_InterplFunction.hxx>

namespace tnbLib
{

	class Geo_LinInterplFunction
		: public Geo_InterplFunction
	{

		/*Private Data*/

		std::pair<Standard_Real, Standard_Real> theX0_;
		std::pair<Standard_Real, Standard_Real> theX1_;

	public:

		static TnbGeo_EXPORT const Standard_Integer nbSamples;

		// default constructor [1/12/2022 Amir]

		Geo_LinInterplFunction()
		{}

		// constructors [1/12/2022 Amir]

		Geo_LinInterplFunction
		(
			const std::pair<Standard_Real, Standard_Real>& x0,
			const std::pair<Standard_Real, Standard_Real>& x1
		)
			: theX0_(x0)
			, theX1_(x1)
		{}

		Geo_LinInterplFunction
		(
			std::pair<Standard_Real, Standard_Real>&& x0,
			std::pair<Standard_Real, Standard_Real>&& x1
		)
			: theX0_(std::move(x0))
			, theX1_(std::move(x1))
		{}

		// override functions and operators [1/12/2022 Amir]

		TnbGeo_EXPORT Standard_Integer NbSamples() const override;
		TnbGeo_EXPORT Standard_Real Value(const Standard_Real x) const override;

		TnbGeo_EXPORT std::pair<Standard_Real, Standard_Real> 
			Sample
			(
				const Standard_Integer theIndex
			) const override;

		TnbGeo_EXPORT std::vector<std::pair<Standard_Real, Standard_Real>> 
			RetrieveSamples() const override;

		// public functions and operators [1/12/2022 Amir]

		const auto& X0() const
		{
			return theX0_;
		}

		const auto& X1() const
		{
			return theX1_;
		}

		void SetX0(const std::pair<Standard_Real, Standard_Real>& x)
		{
			theX0_ = x;
		}

		void SetX0(std::pair<Standard_Real, Standard_Real>&& x)
		{
			theX0_ = std::move(x);
		}

		void SetX1(const std::pair<Standard_Real, Standard_Real>& x)
		{
			theX1_ = x;
		}

		void SetX1(std::pair<Standard_Real, Standard_Real>&& x)
		{
			theX1_ = std::move(x);
		}
	};
}

#endif // !_Geo_LinInterplFunction_Header

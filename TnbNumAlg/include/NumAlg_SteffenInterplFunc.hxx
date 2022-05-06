#pragma once
#ifndef _NumAlg_SteffenInterplFunc_Header
#define _NumAlg_SteffenInterplFunc_Header

#include <NumAlg_InterplFunc.hxx>

#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>

namespace tnbLib
{

	class NumAlg_SteffenInterplFunc
		: public NumAlg_InterplFunc
	{

		/*Private Data*/

		std::vector<std::pair<Standard_Real, Standard_Real>> theQs_;

		gsl_spline* theSpline_;
		gsl_interp_accel* theAcc_;

		// private functions and operators [4/29/2022 Amir]

		auto& SplineInterplRef()
		{
			return theSpline_;
		}

		auto& AccelerationRef()
		{
			return theAcc_;
		}

	public:

		// default constructor [4/29/2022 Amir]

		NumAlg_SteffenInterplFunc()
		{}


		// constructors [4/29/2022 Amir]

		// set and perform [4/30/2022 Amir]
		TnbNumAlg_EXPORT explicit NumAlg_SteffenInterplFunc
		(
			const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs
		);

		// set and perform [4/30/2022 Amir]
		TnbNumAlg_EXPORT NumAlg_SteffenInterplFunc(std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs);


		// destructor [4/29/2022 Amir]

		~NumAlg_SteffenInterplFunc() override;


		// override functions and operators [4/30/2022 Amir]

		TnbNumAlg_EXPORT Standard_Integer NbSamples() const override;
		TnbNumAlg_EXPORT Standard_Real Value(const Standard_Real x) const override;

		TnbNumAlg_EXPORT std::pair<Standard_Real, Standard_Real> Sample(const Standard_Integer theIndex) const override;
		TnbNumAlg_EXPORT std::vector<std::pair<Standard_Real, Standard_Real>> RetrieveSamples() const override;

		// public functions and operators [4/29/2022 Amir]

		const auto& Qs() const
		{
			return theQs_;
		}

		const auto& SplineInterpl() const
		{
			return theSpline_;
		}

		const auto& Acceleration() const
		{
			return theAcc_;
		}

		TnbNumAlg_EXPORT void Perform();

		void SetQs(const std::vector<std::pair<Standard_Real, Standard_Real>>& theQs)
		{
			theQs_ = theQs;
		}

		void SetQs(std::vector<std::pair<Standard_Real, Standard_Real>>&& theQs)
		{
			theQs_ = std::move(theQs);
		}
	};
}

#endif // !_NumAlg_SteffenInterplFunc_Header

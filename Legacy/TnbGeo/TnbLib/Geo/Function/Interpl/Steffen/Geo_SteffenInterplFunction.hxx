#pragma once
#ifndef _Geo_SteffenInterplFunction_Header
#define _Geo_SteffenInterplFunction_Header

#include <Geo_InterplFunction.hxx>
#include <Global_Done.hxx>

#include <vector>

#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>

namespace tnbLib
{

	class Geo_SteffenInterplFunction
		: public Geo_InterplFunction
		, public Global_Done
	{

	public:

		typedef  std::vector<std::pair<Standard_Real, Standard_Real>>
			QsList;

	private:

		/* Private Data*/

		std::vector<std::pair<Standard_Real, Standard_Real>> theQs_;

		gsl_interp_accel* acc_;
		gsl_spline* spline_steffen_;

		double* x;
		double* y;

	public:

		// default constructor

		TnbGeo_EXPORT Geo_SteffenInterplFunction();

		// constructors

		Geo_SteffenInterplFunction(const QsList& theQs)
			: theQs_(theQs)
			, acc_(nullptr)
			, spline_steffen_(nullptr)
		{}

		Geo_SteffenInterplFunction(QsList&& theQs)
			: theQs_(std::move(theQs))
			, acc_(nullptr)
			, spline_steffen_(nullptr)
		{}

		// override virtual funcctions and operators

		TnbGeo_EXPORT ~Geo_SteffenInterplFunction() override;

		TnbGeo_EXPORT Standard_Integer NbSamples() const override;
		TnbGeo_EXPORT Standard_Real Value(const Standard_Real x) const override;

		TnbGeo_EXPORT std::pair<Standard_Real, Standard_Real> Sample(const Standard_Integer theIndex) const override;
		TnbGeo_EXPORT std::vector<std::pair<Standard_Real, Standard_Real>> RetrieveSamples() const override;

		// Public functions and operators

		const auto& Qs() const { return theQs_; }
		auto& QsRef() { return theQs_; }

		TnbGeo_EXPORT void Perform();

		void SetQs(const QsList& theQs) { theQs_ = theQs; }
		void SetQs(QsList&& theQs) { theQs_ = std::move(theQs); }

	};
}

#endif // !_Geo_SteffenInterplFunction_Header

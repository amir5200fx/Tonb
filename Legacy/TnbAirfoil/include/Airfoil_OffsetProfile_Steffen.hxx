#pragma once
#ifndef _Airfoil_OffsetProfile_Steffen_Header
#define _Airfoil_OffsetProfile_Steffen_Header

#include <Airfoil_OffsetProfile.hxx>

#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>

namespace tnbLib
{

	class Airfoil_OffsetProfile_Steffen
		: public Airfoil_OffsetProfile
	{

		/*Private Data*/

		gsl_interp_accel *acc_;
		gsl_spline *spline_steffen_;


		// Private functions and operators [10/30/2022 Amir]

		TNB_SERIALIZATION(TnbAirfoil_EXPORT);

	public:

		// default constructor [10/30/2022 Amir]

		Airfoil_OffsetProfile_Steffen()
		{}

		// constructors [10/30/2022 Amir]


		TnbAirfoil_EXPORT Standard_Real Value(const Standard_Real x) const override;

		TnbAirfoil_EXPORT void Perform() override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Airfoil_OffsetProfile_Steffen);

#endif // !_Airfoil_OffsetProfile_Steffen_Header

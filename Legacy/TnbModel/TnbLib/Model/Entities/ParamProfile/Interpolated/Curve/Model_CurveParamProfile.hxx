#pragma once
#ifndef _Model_CurveParamProfile_Header
#define _Model_CurveParamProfile_Header

#include <Model_ParamProfile_Interpolated.hxx>

#include <Standard_Handle.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	class Model_CurveParamProfile
		: public Model_ParamProfile_Interpolated
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theCurve_;

	public:

		// default constructor [12/21/2022 Payvand]

		Model_CurveParamProfile()
		{}

		// constructors [12/21/2022 Payvand]

		Model_CurveParamProfile(const Handle(Geom2d_Curve)& theCurve)
			: theCurve_(theCurve)
		{}


		// Public functions and operators [12/22/2022 Payvand]

		const auto& Curve() const
		{
			return theCurve_;
		}

		Standard_Real Lower() const override;
		Standard_Real Upper() const override;

		Standard_Real Value(const Standard_Real) const override;

	};
}

#endif // !_Model_CurveParamProfile_Header

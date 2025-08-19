#pragma once
#ifndef _AirfoilPx_Curve_Header
#define _AirfoilPx_Curve_Header

#include <Airfoil_Module.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [5/5/2023 Payvand]

	class Pln_Curve;

	class AirfoilPx_Curve
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Pln_Curve> theCurve_;

	protected:

		// default constructor [5/5/2023 Payvand]

		AirfoilPx_Curve()
		{}


		// constructors [5/5/2023 Payvand]


		// Protected functions and operators [5/5/2023 Payvand]

		auto& CurveRef()
		{
			return theCurve_;
		}

	public:

		// Public functions and operators [5/5/2023 Payvand]

		const auto& Surface() const { return theCurve_; }

	};
}

#endif // !_AirfoilPx_Curve_Header

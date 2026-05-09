#pragma once
#ifndef _Discret2d_PlnCurve_Function_Header
#define _Discret2d_PlnCurve_Function_Header

#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/13/2023 Payvand]

	class Pln_Curve;
	class Discret_Curve_Samples;

	class Discret2d_PlnCurve_Function
	{

		/*Private Data*/

		std::shared_ptr<Discret_Curve_Samples> theSamples_;

	protected:

		// default constructor [7/13/2023 Payvand]

		Discret2d_PlnCurve_Function() = default;

		// constructors [7/13/2023 Payvand]

	public:
		virtual ~Discret2d_PlnCurve_Function() = default;


		// public functions and operators [7/13/2023 Payvand]

		const auto& Samples() const
		{
			return theSamples_;
		}

		virtual Standard_Boolean
			Subdivide
			(
				const std::shared_ptr<Pln_Curve>& theCurve,
				const Standard_Real theU0,
				const Standard_Real theU1
			) const = 0;


		void SetSamples(const std::shared_ptr<Discret_Curve_Samples>& theSamples)
		{
			theSamples_ = theSamples;
		}
	};
}

#endif // !_Discret2d_PlnCurve_Function_Header

#pragma once
#ifndef _Discret2d_Curve_Function_Header
#define _Discret2d_Curve_Function_Header

#include <Discret_Module.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [11/7/2022 Amir]

	class Cad_ParaCurve;
	class Discret_Curve_Samples;

	class Discret2d_Curve_Function
	{

		/*Private Data*/

		std::shared_ptr<Discret_Curve_Samples> theSamples_;

	protected:

		// default constructor [11/7/2022 Amir]

		Discret2d_Curve_Function()
		{}


		// constructors [11/7/2022 Amir]


	public:


		// public functions and operators [11/7/2022 Amir]

		const auto& Samples() const
		{
			return theSamples_;
		}

		virtual Standard_Boolean 
			Subdivide
			(
				const std::shared_ptr<Cad_ParaCurve>& theCurve,
				const Standard_Real theU0,
				const Standard_Real theU1
			) const = 0;


		void SetSamples(const std::shared_ptr<Discret_Curve_Samples>& theSamples)
		{
			theSamples_ = theSamples;
		}
	};
}

#endif // !_Discret2d_Curve_Function_Header

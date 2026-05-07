#pragma once
#ifndef _Discret3d_Surface_SizeFunction_Header
#define _Discret3d_Surface_SizeFunction_Header

#include <Discret3d_Surface_Function.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [11/7/2022 Amir]

	class Discret_Curve_Samples;

	class Discret3d_Surface_SizeFunction
		: public Discret3d_Surface_Function
	{

		/*Private Data*/

		std::shared_ptr<Discret_Curve_Samples> theSamples_;


		// Private functions and operators [11/7/2022 Amir]

		TNB_SERIALIZATION(TnbDiscret_EXPORT);

	protected:

		// default constructor [11/7/2022 Amir]

		Discret3d_Surface_SizeFunction()
		{}


		// constructors [11/7/2022 Amir]

	public:

		// public functions and operators [11/7/2022 Amir]

		const auto& Samples() const
		{
			return theSamples_;
		}

		void SetSamples(const std::shared_ptr<Discret_Curve_Samples>& theSamples)
		{
			theSamples_ = theSamples;
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Discret3d_Surface_SizeFunction);

#endif // !_Discret3d_Surface_SizeFunction_Header

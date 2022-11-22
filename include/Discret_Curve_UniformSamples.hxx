#pragma once
#ifndef _Discret_Curve_UniformSamples_Header
#define _Discret_Curve_UniformSamples_Header

#include <Discret_Curve_Samples.hxx>

namespace tnbLib
{

	class Discret_Curve_UniformSamples
		: public Discret_Curve_Samples
	{

		/*Private Data*/


		// Private functions and operators [11/7/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Discret_Curve_Samples>(*this);
		}

	public:

		// default constructor [11/7/2022 Amir]

		Discret_Curve_UniformSamples()
		{}

		// constructors [11/7/2022 Amir]


		// public functions and operators [11/7/2022 Amir]


		TnbDiscret_EXPORT std::vector<Standard_Real> 
			CalcXs
			(
				const Standard_Real x0,
				const Standard_Real x1
			) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Discret_Curve_UniformSamples);

#endif // !_Discret_Curve_UniformSamples_Header

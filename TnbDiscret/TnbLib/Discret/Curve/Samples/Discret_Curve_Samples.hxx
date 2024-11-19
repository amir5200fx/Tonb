#pragma once
#ifndef _Discret_Curve_Samples_Header
#define _Discret_Curve_Samples_Header

#include <Discret_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <vector>

namespace tnbLib
{

	class Discret_Curve_Samples
	{

		/*Private Data*/

		Standard_Integer theNbSamples_;


		// Private functions and operators [11/7/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theNbSamples_;
		}

	protected:

		// default constructor [11/7/2022 Amir]

		Discret_Curve_Samples()
		{}


		// constructors [11/7/2022 Amir]


	public:

		// public functions and operators [11/7/2022 Amir]

		virtual std::vector<Standard_Real> CalcXs(const Standard_Real x0, const Standard_Real x1) const = 0;

		auto NbSamples() const
		{
			return theNbSamples_;
		}

		void SetNbSamples(const Standard_Integer n)
		{
			theNbSamples_ = n;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Discret_Curve_Samples);

#endif // !_Discret_Curve_Samples_Header

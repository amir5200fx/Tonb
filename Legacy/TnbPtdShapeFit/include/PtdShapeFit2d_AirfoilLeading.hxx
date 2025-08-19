#pragma once
#ifndef _PtdShapeFit2d_AirfoilLeading_Header
#define _PtdShapeFit2d_AirfoilLeading_Header

#include <PtdShapeFit2d_AirfoilCurve.hxx>

namespace tnbLib
{

	class PtdShapeFit2d_AirfoilLeading
		: public PtdShapeFit2d_AirfoilCurve
	{

		/*Private Data*/

		// Private functions and operators [5/6/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object <PtdShapeFit2d_AirfoilCurve>(*this);
		}

	protected:

		// default constructor [5/6/2023 Payvand]


		PtdShapeFit2d_AirfoilLeading()
		{}

		// constructors [5/6/2023 Payvand]

	public:

		// Public functions and operators [5/6/2023 Payvand]



	};

}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit2d_AirfoilLeading);

#endif // !_PtdShapeFit2d_AirfoilLeading_Header

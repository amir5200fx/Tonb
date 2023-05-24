#pragma once
#ifndef _PtdShapeFit2d_AirfoilNose_Header
#define _PtdShapeFit2d_AirfoilNose_Header

#include <PtdShapeFit2d_AirfoilCurve.hxx>

namespace tnbLib
{

	class PtdShapeFit2d_AirfoilNose
		: public PtdShapeFit2d_AirfoilCurve
	{

		/*Private Data*/


		// Private functions and operators [5/5/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object <PtdShapeFit2d_AirfoilCurve>(*this);
		}

	protected:

		// default constructor [5/5/2023 Payvand]

		PtdShapeFit2d_AirfoilNose()
		{}

		// constructors [5/5/2023 Payvand]

	public:

		// Public functions and operators [5/5/2023 Payvand]


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit2d_AirfoilNose);

#endif // !_PtdShapeFit2d_AirfoilNose_Header

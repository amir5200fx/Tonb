#pragma once
#ifndef _PtdShapeFit2d_AirfoilCurve_Header
#define _PtdShapeFit2d_AirfoilCurve_Header

#include <PtdShapeFit2d_Curve.hxx>

namespace tnbLib
{

	class PtdShapeFit2d_AirfoilCurve
		: public PtdShapeFit2d_Curve
	{

		/*Private Data*/

		// Private functions and operators [5/5/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object<PtdShapeFit2d_Curve>(*this);
		}

	protected:

		// default constructor [5/5/2023 Payvand]

		PtdShapeFit2d_AirfoilCurve()
		{}

		// constructors [5/5/2023 Payvand]

	public:

		// Public functions and operators [5/5/2023 Payvand]



	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit2d_AirfoilCurve);

#endif // !_PtdShapeFit2d_AirfoilCurve_Header

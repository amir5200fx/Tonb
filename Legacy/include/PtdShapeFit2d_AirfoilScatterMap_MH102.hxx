#pragma once
#ifndef _PtdShapeFit2d_AirfoilScatterMap_MH102_Header
#define _PtdShapeFit2d_AirfoilScatterMap_MH102_Header

#include <PtdShapeFit2d_AirfoilScatterMap.hxx>

namespace tnbLib
{

	class PtdShapeFit2d_AirfoilScatterMap_MH102
		: public PtdShapeFit2d_AirfoilScatterMap
	{

		/*Private Data*/


		// Private functions and operators [4/28/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_evrsion)
		{
			ar& boost::serialization::base_object<PtdShapeFit2d_AirfoilScatterMap>(*this);
		}

	protected:

		// default constructor [4/28/2023 Payvand]

		PtdShapeFit2d_AirfoilScatterMap_MH102()
		{}

		// constructors [4/28/2023 Payvand]

	public:

		// Public functions and operators [4/28/2023 Payvand]

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit2d_AirfoilScatterMap_MH102);

#endif // !_PtdShapeFit2d_AirfoilScatterMap_MH102_Header

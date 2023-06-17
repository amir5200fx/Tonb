#pragma once
#ifndef _PtdShapeFit2d_AirfoilScatterMap_Header
#define _PtdShapeFit2d_AirfoilScatterMap_Header

#include <PtdShapeFit2d_ScatterMap.hxx>

namespace tnbLib
{

	class PtdShapeFit2d_AirfoilScatterMap
		: public PtdShapeFit2d_ScatterMap
	{

		/*Private Data*/

		// Private functions and operators [4/29/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<PtdShapeFit2d_ScatterMap>(*this);
		}

	protected:

		// default constructor [4/25/2023 Payvand]

		PtdShapeFit2d_AirfoilScatterMap()
		{}


		// constructors [4/25/2023 Payvand]

	public:

		// Public functions and operators [4/25/2023 Payvand]


	};

}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit2d_AirfoilScatterMap);

#endif // !_PtdShapeFit2d_AirfoilScatterMap_Header

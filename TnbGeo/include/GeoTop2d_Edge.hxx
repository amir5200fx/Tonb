#pragma once
#ifndef _GeoTop2d_Edge_Header
#define _GeoTop2d_Edge_Header

#include <GeoTop2d_EdgeAdaptor.hxx>
#include <GeoTop2d_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations [2/17/2023 Payvand]

	class GeoTop2d_Vertex;

	class GeoTop2d_Edge
		: public GeoTop2d_Entity
		, public GeoTop2d_EdgeAdaptor
	{

		/*Private Data*/

		std::pair<std::shared_ptr<GeoTop2d_Vertex>, std::shared_ptr<GeoTop2d_Vertex>>
			thePair_;


		// Private functions and operators [2/17/2023 Payvand]

		TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		// default constructor [2/17/2023 Payvand]

		GeoTop2d_Edge()
		{}


		// constructors [2/17/2023 Payvand]

		GeoTop2d_Edge
		(
			const Standard_Integer theIndex, 
			const std::pair
			<
			std::shared_ptr<GeoTop2d_Vertex>,
			std::shared_ptr<GeoTop2d_Vertex>
			>& thePair
		)
			: GeoTop2d_Entity(theIndex)
			, thePair_(thePair)
		{}

		GeoTop2d_Edge
		(
			const Standard_Integer theIndex,
			std::pair
			<
			std::shared_ptr<GeoTop2d_Vertex>,
			std::shared_ptr<GeoTop2d_Vertex>
			>&& thePair
		)
			: GeoTop2d_Entity(theIndex)
			, thePair_(std::move(thePair))
		{}

		TnbGeo_EXPORT GeoTop2d_Edge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<GeoTop2d_Vertex>& theVtx0,
			const std::shared_ptr<GeoTop2d_Vertex>& theVtx1
		);

		// Public functions and operators [2/17/2023 Payvand]

		const auto& Pair() const
		{
			return thePair_;
		}

		auto& PairRef()
		{
			return thePair_;
		}

		const auto& First() const
		{
			return std::get<0>(Pair());
		}

		const auto& Second() const
		{
			return std::get<1>(Pair());
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoTop2d_Edge);

#endif // !_GeoTop2d_Edge_Header

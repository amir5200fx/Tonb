#pragma once
#ifndef _GeoTop2d_Vertex_Header
#define _GeoTop2d_Vertex_Header

#include <GeoTop2d_VertexAdaptor.hxx>
#include <GeoTop2d_Entity.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [2/17/2023 Payvand]

	class GeoTop2d_Point;

	class GeoTop2d_Vertex
		: public GeoTop2d_Entity
		, public GeoTop2d_VertexAdaptor
	{

		/*Private Data*/

		std::shared_ptr<GeoTop2d_Point> thePoint_;


		// Private functions and operators [2/17/2023 Payvand]

		TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		// default constructor [2/17/2023 Payvand]

		GeoTop2d_Vertex()
		{}

		// constructors [2/17/2023 Payvand]

		GeoTop2d_Vertex
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<GeoTop2d_Point>& thePoint
		)
			: GeoTop2d_Entity(theIndex)
			, thePoint_(thePoint)
		{}

		GeoTop2d_Vertex
		(
			const Standard_Integer theIndex,
			std::shared_ptr<GeoTop2d_Point>&& thePoint
		)
			: GeoTop2d_Entity(theIndex)
			, thePoint_(std::move(thePoint))
		{}


		// Public functions and operators [2/17/2023 Payvand]

		const auto& Point() const
		{
			return thePoint_;
		}

		auto& PointRef()
		{
			return thePoint_;
		}

		// return null if the node is interior [2/19/2023 Payvand]
		TnbGeo_EXPORT std::shared_ptr<GeoTop2d_Edge> ForwardBoundaryEdge() const;
		// return null if the node is interior [2/19/2023 Payvand]
		TnbGeo_EXPORT std::shared_ptr<GeoTop2d_Edge> BackwardBoundaryEdge() const;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoTop2d_Vertex);

#endif // !_GeoTop2d_Vertex_Header

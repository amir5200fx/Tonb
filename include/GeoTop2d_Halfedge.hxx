#pragma once
#ifndef _GeoTop2d_Halfedge_Header
#define _GeoTop2d_Halfedge_Header

#include <GeoTop2d_HalfedgeAdaptor.hxx>
#include <GeoTop2d_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations [2/17/2023 Payvand]

	class GeoTop2d_Vertex;

	class GeoTop2d_Halfedge
		: public GeoTop2d_Entity
		, public GeoTop2d_HalfedgeAdaptor
	{

		/*Private Data*/

		std::array<std::shared_ptr<GeoTop2d_Vertex>, 2> theVertices_;


		// Private functions and operators [2/17/2023 Payvand]

		TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		// default constructor [2/17/2023 Payvand]

		GeoTop2d_Halfedge()
		{}

		// constructors [2/17/2023 Payvand]

		GeoTop2d_Halfedge
		(
			const Standard_Integer theIndex, 
			const std::array<std::shared_ptr<GeoTop2d_Vertex>, 2>& theVertices
		)
			: theVertices_(theVertices)
		{}


		// Public functions and operators [2/17/2023 Payvand]

		const auto& Vertices() const
		{
			return theVertices_;
		}

		auto& VerticesRef()
		{
			return theVertices_;
		}

		const auto& Vtx0() const
		{
			return std::get<0>(Vertices());
		}

		const auto& Vtx1() const
		{
			return std::get<1>(Vertices());
		}

		TnbGeo_EXPORT void SetVtx0(const std::shared_ptr<GeoTop2d_Vertex>&);
		TnbGeo_EXPORT void SetVtx0(std::shared_ptr<GeoTop2d_Vertex>&&);
		TnbGeo_EXPORT void SetVtx1(const std::shared_ptr<GeoTop2d_Vertex>&);
		TnbGeo_EXPORT void SetVtx1(std::shared_ptr<GeoTop2d_Vertex>&&);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoTop2d_Halfedge);

#endif // !_GeoTop2d_Halfedge_Header

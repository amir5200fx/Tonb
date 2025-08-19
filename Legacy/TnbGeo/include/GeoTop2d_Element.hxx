#pragma once
#ifndef _GeoTop2d_Element_Header
#define _GeoTop2d_Element_Header

#include <GeoTop2d_ElementAdaptor.hxx>
#include <GeoTop2d_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations [2/17/2023 Payvand]

	class GeoTop2d_Vertex;
	class GeoTop2d_Edge;

	class GeoTop2d_Element
		: public GeoTop2d_Entity
		, public GeoTop2d_ElementAdaptor
	{

		/*Private Data*/

		std::array<std::shared_ptr<GeoTop2d_Vertex>, 3> theVertices_;
		std::array<std::shared_ptr<GeoTop2d_Edge>, 3> theEdges_;

		// Private functions and operators [2/17/2023 Payvand]

		TNB_SERIALIZATION(TnbGeo_EXPORT);


	public:

		// default constructor [2/17/2023 Payvand]

		GeoTop2d_Element()
		{}

		// constructors [2/17/2023 Payvand]

		GeoTop2d_Element
		(
			const Standard_Integer theIndex, 
			const std::array<std::shared_ptr<GeoTop2d_Vertex>, 3>& thevertices
		)
			: GeoTop2d_Entity(theIndex)
			, theVertices_(thevertices)
		{}

		GeoTop2d_Element
		(
			const Standard_Integer theIndex,
			std::array<std::shared_ptr<GeoTop2d_Vertex>, 3>&& thevertices
		)
			: GeoTop2d_Entity(theIndex)
			, theVertices_(std::move(thevertices))
		{}


		// Public functions and operators [2/17/2023 Payvand]

		const auto& Vertices() const
		{
			return theVertices_;
		}

		const auto& Edges() const
		{
			return theEdges_;
		}

		const auto& Vtx0() const
		{
			return std::get<0>(Vertices());
		}

		const auto& Vtx1() const
		{
			return std::get<1>(Vertices());
		}

		const auto& Vtx2() const
		{
			return std::get<2>(Vertices());
		}

		const auto& Edge0() const
		{
			return std::get<0>(Edges());
		}

		const auto& Edge1() const
		{
			return std::get<1>(Edges());
		}

		const auto& Edge2() const
		{
			return std::get<2>(Edges());
		}

		std::tuple<Standard_Integer, Standard_Integer, Standard_Integer>
			VertexIndices() const;
		std::tuple<Standard_Integer, Standard_Integer, Standard_Integer>
			EdgeIndices() const;

		TnbGeo_EXPORT const std::shared_ptr<GeoTop2d_Vertex>& 
			Vertex(const Standard_Integer theIndex) const;
		TnbGeo_EXPORT const std::shared_ptr<GeoTop2d_Edge>& 
			Edge(const Standard_Integer theIndex) const;

		auto& VerticesRef()
		{
			return theVertices_;
		}

		auto& EdgesRef()
		{
			return theEdges_;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoTop2d_Element);

#endif // !_GeoTop2d_Element_Header

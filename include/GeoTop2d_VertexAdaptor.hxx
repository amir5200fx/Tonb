#pragma once
#ifndef _GeoTop2d_VertexAdaptor_Header
#define _GeoTop2d_VertexAdaptor_Header

#include <Geo_Module.hxx>
#include <Geo_Serialization.hxx>

#include <map>
#include <vector>
#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [2/17/2023 Payvand]
	class GeoTop2d_Element;
	class GeoTop2d_Edge;

	class GeoTop2d_VertexAdaptor
	{

		/*Private Data*/

		std::map<Standard_Integer, std::weak_ptr<GeoTop2d_Edge>>
			theEdges_;
		std::map<Standard_Integer, std::weak_ptr<GeoTop2d_Element>>
			theElements_;

		// Private functions and operators [2/17/2023 Payvand]

		TNB_SERIALIZATION(TnbGeo_EXPORT);

	protected:

		// default constructor [2/17/2023 Payvand]

		GeoTop2d_VertexAdaptor()
		{}

		// constructors [2/17/2023 Payvand]


	public:

		// Public functions and operators [2/17/2023 Payvand]

		TnbGeo_EXPORT Standard_Integer NbEdges() const;
		TnbGeo_EXPORT Standard_Integer NbElements() const;

		TnbGeo_EXPORT Standard_Integer NbBoundaryEdges() const;

		const auto& Edges() const
		{
			return theEdges_;
		}

		const auto& Elements() const
		{
			return theElements_;
		}

		TnbGeo_EXPORT std::weak_ptr<GeoTop2d_Edge> 
			RemoveEdge(const Standard_Integer theIndex);
		TnbGeo_EXPORT std::weak_ptr<GeoTop2d_Element>
			RemoveElement(const Standard_Integer theIndex);

		TnbGeo_EXPORT void InsertToEdges
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<GeoTop2d_Edge>&
		);

		TnbGeo_EXPORT void InsertToElements
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<GeoTop2d_Element>&
		);

	};
}

#endif // !_GeoTop2d_VertexAdaptor_Header

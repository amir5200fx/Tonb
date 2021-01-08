#pragma once
#ifndef _Mesh_BndEdge_Header
#define _Mesh_BndEdge_Header

#include <Mesh_EdgeAdaptor.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	template<class BndEdgeTraits>
	class Mesh_BndEdge
		: public Mesh_EdgeAdaptor<void, typename BndEdgeTraits::facetType>
		, public BndEdgeTraits::edgeType
	{

	public:

		typedef typename BndEdgeTraits::edgeType edgeType;
		typedef typename edgeType::nodeType nodeType;
		typedef typename BndEdgeTraits::nodeType bndNodeType;

		typedef Mesh_EdgeAdaptor<void, typename BndEdgeTraits::facetType> edgeAdaptor;

	private:


		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<edgeAdaptor>(*this);
			ar & boost::serialization::base_object<edgeType>(*this);
		}

	public:

		
		//- default constructors

		Mesh_BndEdge()
		{}


		//- constructors

		Mesh_BndEdge
		(
			const Standard_Integer theIndex
		)
			: edgeType(theIndex)
		{}

		Mesh_BndEdge
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<nodeType>& theNode0,
			const std::shared_ptr<nodeType>& theNode1
		)
			: edgeType(theIndex, theNode0, theNode1)
		{}


		//- Static functions and operators

		static void
			ActiveBoundaryEdges
			(
				const std::vector<std::shared_ptr<edgeType>>& theEdges
			);

		static std::vector<std::shared_ptr<edgeType>>
			UpCast
			(
				const std::vector<std::shared_ptr<Mesh_BndEdge>>& theEdges
			);
	};
}

#include <Mesh_BndEdgeI.hxx>

#endif // !_Mesh_BndEdge_Header

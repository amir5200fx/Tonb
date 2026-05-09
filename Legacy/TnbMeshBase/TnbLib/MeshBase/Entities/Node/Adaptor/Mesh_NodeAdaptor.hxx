#pragma once
#ifndef _Mesh_NodeAdaptor_Header
#define _Mesh_NodeAdaptor_Header

#include <Mesh_EntityAdaptorM.hxx>
#include <MeshBase_Module.hxx>

#define MESH_MODULE TnbMeshBase_EXPORT

namespace tnbLib
{

	Mesh_EntityToEntityAdaptor(Node, BoundaryEdge, EdgeType);
	Mesh_EntityToEntityAdaptor(Node, BoundaryFacet, FacetType);

	Mesh_EntityToEntityAdaptor(Node, Edge, EdgeType);
	Mesh_EntityToEntityAdaptor(Node, Facet, FacetType);
	Mesh_EntityToEntityAdaptor(Node, Element, ElementType);

	template<class EdgeType, class ElementType, class FacetType = void>
	class Mesh_NodeAdaptor
		: public Mesh_NodeToEdgeAdaptor<EdgeType>
		, public Mesh_NodeToFacetAdaptor<FacetType>
		, public Mesh_NodeToElementAdaptor<ElementType>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_NodeToEdgeAdaptor<EdgeType>>(*this);
			ar & boost::serialization::base_object<Mesh_NodeToFacetAdaptor<FacetType>>(*this);
			ar & boost::serialization::base_object<Mesh_NodeToElementAdaptor<ElementType>>(*this);
		}

	public:

		typedef Mesh_NodeToEdgeAdaptor<EdgeType> edgeAdaptor;
		typedef Mesh_NodeToFacetAdaptor<FacetType> facetAdaptor;
		typedef Mesh_NodeToElementAdaptor<ElementType> elementAdaptor;

		Mesh_NodeAdaptor()
		{}
	};

	template<class EdgeType, class FacetType>
	class Mesh_NodeAdaptor<EdgeType, void, FacetType>
		: public Mesh_NodeToBoundaryEdgeAdaptor<EdgeType>
		, public Mesh_NodeToBoundaryFacetAdaptor<FacetType>
	{

		/*Private Data*/



		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_NodeToBoundaryEdgeAdaptor<EdgeType>>(*this);
			ar & boost::serialization::base_object<Mesh_NodeToBoundaryFacetAdaptor<FacetType>>(*this);
		}

	public:

		typedef Mesh_NodeToBoundaryEdgeAdaptor<EdgeType> edgeAdaptor;
		typedef Mesh_NodeToBoundaryFacetAdaptor<FacetType> facetAdaptor;

		Mesh_NodeAdaptor()
		{}
	};

	template<class EdgeType, class ElementType>
	class Mesh_NodeAdaptor<EdgeType, ElementType, void>
		: public Mesh_NodeToEdgeAdaptor<EdgeType>
		, public Mesh_NodeToElementAdaptor<ElementType>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_NodeToEdgeAdaptor<EdgeType>>(*this);
			ar & boost::serialization::base_object<Mesh_NodeToElementAdaptor<ElementType>>(*this);
		}

	public:

		typedef Mesh_NodeToEdgeAdaptor<EdgeType> edgeAdaptor;
		typedef Mesh_NodeToElementAdaptor<ElementType> elementAdaptor;

		Mesh_NodeAdaptor()
		{}
	};

	template<class EdgeType>
	class Mesh_NodeAdaptor<EdgeType, void, void>
		: public Mesh_NodeToBoundaryEdgeAdaptor<EdgeType>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_NodeToBoundaryEdgeAdaptor<EdgeType>>(*this);
		}

	public:

		typedef Mesh_NodeToBoundaryEdgeAdaptor<EdgeType> edgeAdaptor;

		Mesh_NodeAdaptor()
		{}
	};
}

#undef MESH_MODULE

#endif // !_Mesh_NodeAdaptor_Header

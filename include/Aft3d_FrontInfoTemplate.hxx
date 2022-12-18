#pragma once
#ifndef _Aft3d_FrontInfoTemplate_Header
#define _Aft3d_FrontInfoTemplate_Header

#define RESET_FRONT_INFO
#include <Aft_FrontInfo.hxx>
#include <Mesh_Counters.hxx>
#include <Aft_TypeTraits.hxx>
#include <Global_Serialization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//#include "Aft3d_Element.hxx"
//#include "Aft3d_Facet.hxx"
//#include "Aft3d_Edge.hxx"
//#include "Aft3d_Node.hxx"
//#include "Aft3d_FrontInfoAdaptor.hxx"
//#include "Aft_FrontTraits.hxx"

namespace tnbLib
{

	template<class FrontTraits, class FrontAdaptor>
	class Aft3d_FrontInfoTemplate
		: public Aft_FrontInfo<FrontAdaptor>
		, public Mesh3d_FrontCounter
	{

		// Private functions and operators [12/18/2022 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Aft_FrontInfo<FrontAdaptor>>(*this);
			ar& boost::serialization::base_object<Mesh3d_FrontCounter>(*this);
		}

	public:

		typedef typename FrontTraits::nodeType nodeType;
		typedef typename FrontTraits::edgeType edgeType;
		typedef typename FrontTraits::facetType frontType;
		typedef typename FrontTraits::facetType frontType;
		typedef typename FrontTraits::elementType elementType;

		typedef Aft_FrontInfo<FrontAdaptor> frontInfo;

	protected:

		// default constructor [12/17/2022 Payvand]

		Aft3d_FrontInfoTemplate()
		{}

		// constructors [12/17/2022 Payvand]


		// Protected functions and operators [12/17/2022 Payvand]

		static void AttachToMeshNodes(const std::shared_ptr<elementType>& theElement);
		static void AttachToMeshNodes(const std::shared_ptr<frontType>& theFacet);
		static void AttachToMeshNodes(const std::shared_ptr<edgeType>& theEdge);

		static void AttachToMeshEdges(const std::shared_ptr<frontType>&);
		static void AttachToMeshEdges(const std::shared_ptr<elementType>&);

		static void AttachToMesh(const std::shared_ptr<frontType>& theFacet);
		static void AttachToMesh(const std::shared_ptr<elementType>&);

		static void AttachToFrontNodes(const std::shared_ptr<frontType>& theFacet);
		static void AttachToFrontNodes(const std::shared_ptr<edgeType>& theEdge);
		static void AttachToFrontEdges(const std::shared_ptr<frontType>& theFacet);

		static void AttachToFronts(const std::shared_ptr<frontType>& theFront);

		static void deAttachFromMesh(const std::shared_ptr<frontType>&);
		static void deAttachFromMesh(const std::shared_ptr<edgeType>&);

		static void deAttachFromMeshNodes(const std::shared_ptr<frontType>&);
		static void deAttachFromMeshEdges(const std::shared_ptr<frontType>&);

		static void deAttachFromFronts(const std::shared_ptr<frontType>&);
		static void deAttachFromFronts(const std::shared_ptr<edgeType>&);

		static void deAttachFromFrontNodes(const std::shared_ptr<frontType>&);
		static void deAttachFromFrontEdges(const std::shared_ptr<frontType>&);

		void SetPairedFacets();
		void SetPairedEdges();

		template<class SizeMap>
		static void CalcGeometries(const std::shared_ptr<SizeMap>&, const std::shared_ptr<frontType>&);
		template<class SizeMap>
		static void CalcGeometries(const std::shared_ptr<SizeMap>&, const std::shared_ptr<edgeType>&);

		template<class SizeMap>
		void UpdateEdges(const std::shared_ptr<SizeMap>&);

		template<class SizeMap>
		void UpdateFacets(const std::shared_ptr<SizeMap>&);

	public:


		// Public functions and operators [12/17/2022 Payvand]

		void SetPairs();

		template<class SizeMap>
		void UpdatePairs(const std::shared_ptr<SizeMap>&);

		void CreateElement();

		void UpdateElement();


	};
}

#include <Aft3d_FrontInfoTemplateI.hxx>

#endif // !_Aft3d_FrontInfoTemplate_Header

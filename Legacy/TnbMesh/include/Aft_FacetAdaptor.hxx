#pragma once
#ifndef _Aft_FacetAdaptor_Header
#define _Aft_FacetAdaptor_Header

#include <Aft_EntityIdentifier.hxx>
#include <Aft3d_FacetFwd.hxx>
#include <Aft3d_FacetAnIsoFwd.hxx>
#include <Aft3d_Node.hxx>
#include <Mesh_ElementAdaptor.hxx>
#include <Mesh_FrontAdaptor.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	class Mesh_FrontAdaptor<Aft3d_FacetTraits>
		: public Aft_EntityIdentifier<Aft3d_Node, true>
	{

		/*Private Data*/


		// Private functions and operators [12/18/2022 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Aft_EntityIdentifier<Aft3d_Node, true>>(*this);
		}

	public:

		// Public functions and operators [12/18/2022 Payvand]

		static TnbMesh_EXPORT Standard_Real Length(const std::shared_ptr<Aft3d_Facet>& theFacet);
	};
}

#endif // !_Aft_FacetAdaptor_Header

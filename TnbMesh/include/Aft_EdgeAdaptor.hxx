#pragma once
#ifndef _Aft_EdgeAdaptor_Header
#define _Aft_EdgeAdaptor_Header

#include <Mesh_EdgeAdaptor.hxx>
#include <Aft3d_ElementFwd.hxx>
#include <Global_Serialization.hxx>

#define MESH_MODULE TnbMesh_EXPORT

namespace tnbLib
{

	Mesh_EntityToEntityAdaptor(Edge, FrontFacet, FacetType);

	template<class ElementType, class FacetType = void>
	class Aft_EdgeAdaptor
		: public Mesh_EdgeToFrontFacetAdaptor<FacetType>
	{

		/*Private Data*/


		// Private functions and operators [12/18/2022 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Mesh_EdgeToFrontFacetAdaptor<FacetType>>(*this);
		}

	public:

		typedef Mesh_EdgeAdaptor<ElementType, FacetType> meshAdaptor;
		typedef Mesh_EdgeToFrontFacetAdaptor<FacetType> frontFacetAdaptor;

	protected:

		// default constructor [12/16/2022 Payvand]

		Aft_EdgeAdaptor()
		{}

		// constructors [12/16/2022 Payvand]


		// public functions and operators [12/16/2022 Payvand]

	};

	template<>
	class Mesh_EdgeAdaptor<Aft3d_Element, void>
	{

		/*Private Data*/


		// Private functions and operators [12/16/2022 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{}

	protected:

		// default constructor [12/16/2022 Payvand]

		Mesh_EdgeAdaptor()
		{}

		// constructors [12/16/2022 Payvand]

	public:

		
		// Public functions and operators [12/16/2022 Payvand]
	};

	template<class ElementType>
	class Aft_EdgeAdaptor<ElementType, void>
	{

		/*Private Data*/


		// Private functions and operators [12/18/2022 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{}

	public:

		typedef Mesh_EdgeAdaptor<ElementType> meshAdaptor;

	protected:

		// default constructor [12/16/2022 Payvand]

		Aft_EdgeAdaptor()
		{}


		// constructors [12/16/2022 Payvand]


		// Public functions and operators [12/16/2022 Payvand]

	};
}

#endif // !_Aft_EdgeAdaptor_Header

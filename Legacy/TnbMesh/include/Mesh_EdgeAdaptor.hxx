#pragma once
#ifndef _Mesh_EdgeAdaptor_Header
#define _Mesh_EdgeAdaptor_Header

#include <Mesh_EntityAdaptorM.hxx>
#include <Mesh_Module.hxx>

#define MESH_MODULE TnbMesh_EXPORT

namespace tnbLib
{

	Mesh_EntityToEntityAdaptor(Edge, BoundaryFacet, FacetType);

	Mesh_EntityToEntityAdaptor(Edge, Facet, FacetType);
	Mesh_EntityToEntityAdaptor(Edge, Element, ElementType);

	template<class ElementType, class FacetType = void>
	class Mesh_EdgeAdaptor
		: public Mesh_EdgeToFacetAdaptor<FacetType>
		, public Mesh_EdgeToElementAdaptor<ElementType>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_EdgeToFacetAdaptor<FacetType>>(*this);
			ar & boost::serialization::base_object<Mesh_EdgeToElementAdaptor<ElementType>>(*this);
		}

	protected:

		//- default constructor

		Mesh_EdgeAdaptor()
		{}

	public:


		//- public functions and operators

		Standard_Boolean IsOrphan() const
		{
			return this->NbFacets() == 0 AND 
				this->NbElements() == 0;
		}

	};

	//template<class FacetType>
	//class Mesh_EdgeAdaptor<void, FacetType>
	//	: public Mesh_EdgeToFacetAdaptor<FacetType>
	//{

	//	/*Private Data*/

	//public:

	//	Mesh_EdgeAdaptor()
	//	{}
	//};

	template<>
	class Mesh_EdgeAdaptor<void, void>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{}

	protected:

		//- default constructor

		Mesh_EdgeAdaptor()
		{}

	public:

		//- public functions and operators

	};

	template<class ElementType>
	class Mesh_EdgeAdaptor<ElementType, void>
	{

		/*Private Data*/

		std::weak_ptr<ElementType> theRight_;
		std::weak_ptr<ElementType> theLeft_;


		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		//- default constructor

		Mesh_EdgeAdaptor()
		{}

	public:

		//- public functions and operators

		const std::weak_ptr<ElementType>& RightElement() const
		{
			return theRight_;
		}

		std::weak_ptr<ElementType>& RightElement()
		{
			return theRight_;
		}

		const std::weak_ptr<ElementType>& LeftElement() const
		{
			return theLeft_;
		}

		std::weak_ptr<ElementType>& LeftElement()
		{
			return theLeft_;
		}

		Standard_Boolean IsOrphan() const
		{
			return theRight_.lock() == nullptr && theLeft_.lock() == nullptr;
		}

		void SetRightElement(const std::weak_ptr<ElementType>& theElement)
		{
			theRight_ = theElement;
		}

		void SetLeftElement(const std::weak_ptr<ElementType>& theElement)
		{
			theLeft_ = theElement;
		}
	};
}

#undef MESH_MODULE

#endif // !_Mesh_EdgeAdaptor_Header
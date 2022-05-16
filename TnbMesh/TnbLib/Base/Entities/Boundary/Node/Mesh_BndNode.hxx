#pragma once
#ifndef _Mesh_BndNode_Header
#define _Mesh_BndNode_Header

#include <Mesh_NodeAdaptor.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	template<class BndNodeTraits>
	class Mesh_BndNode
		: public Mesh_NodeAdaptor
		<
		typename BndNodeTraits::edgeType,
		void,
		typename BndNodeTraits::facetType
		>
		, public BndNodeTraits::nodeType
	{

		typedef Mesh_NodeAdaptor
			<
			typename BndNodeTraits::edgeType,
			void,
			typename BndNodeTraits::facetType
			> nodeAdaptor;


		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<nodeAdaptor>(*this);
			ar & boost::serialization::base_object<typename BndNodeTraits::nodeType>(*this);
		}


	public:

		typedef typename BndNodeTraits::nodeType nodeType;
		typedef typename nodeType::ptType Point;

		typedef typename BndNodeTraits::nodeType base;

		using nodeType::Merge_Alg;

	protected:

		//- default constructors

		Mesh_BndNode()
		{}


		//- constructors

		explicit Mesh_BndNode
		(
			const Standard_Integer theIndex
		)
			: nodeType(theIndex)
		{}

		Mesh_BndNode
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: nodeType(theIndex, theCoord)
		{}

		// virtual functions and operators [5/13/2022 Amir]

		virtual Standard_Boolean IsGap() const
		{
			return Standard_False;
		}

		//- public functions and operators

		virtual Standard_Boolean IsSegment() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsCorner() const
		{
			return Standard_False;
		}
	};
}

#endif // !_Mesh_BndNode_Header

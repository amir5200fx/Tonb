#pragma once
#ifndef _Aft_Node_Header
#define _Aft_Node_Header

#include <Mesh_Node.hxx>
#include <Aft_NodeAdaptor.hxx>
#include <Aft_NodeIdentifier.hxx>

namespace tnbLib
{

	template<class NodeTraits>
	class Aft_Node
		: public Mesh_Node<NodeTraits>
		, public Aft_NodeIdentifier<NodeTraits::nType>
		, public Aft_NodeAdaptor
		<
		typename NodeTraits::edgeType,
		typename NodeTraits::elementType,
		typename NodeTraits::facetType
		>
	{

	public:

		typedef Mesh_Node<NodeTraits> baseType;

		typedef typename NodeTraits::edgeType edgeType;
		typedef typename NodeTraits::elementType elementType;
		typedef typename NodeTraits::facetType facetType;

		typedef typename baseType::ptType ptType;
		typedef Aft_NodeAdaptor<edgeType, elementType, facetType> nodeAdaptor;

	private:

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_Node<NodeTraits>>(*this);
			ar & boost::serialization::base_object<Aft_NodeIdentifier<NodeTraits::nType>>(*this);
			ar & boost::serialization::base_object<nodeAdaptor>(*this);
		}

	public:

		typedef ptType Point;

		enum class Merge_Alg
		{
			New = 0,
			FirstPreferred,
			SecondPreferred
		};


		//- default constructor

		Aft_Node()
		{}


		//- constructors

		Aft_Node
		(
			const Standard_Integer theIndex
		)
			: baseType(theIndex)
		{}

		Aft_Node
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: baseType(theIndex, theCoord)
		{}


		//- public functions and operators



		//- Static functions and operators

		static const Point& GetCoord(const std::shared_ptr<Aft_Node>& theNode)
		{
			Debug_Null_Pointer(theNode);
			return theNode->Coord();
		}

		static const Point& GetCoord(const std::weak_ptr<Aft_Node>& theNode)
		{
			const auto node = theNode.lock();
			Debug_Null_Pointer(node);

			return node->Coord();
		}

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Aft_Node>& theNode0,
			const std::shared_ptr<Aft_Node>& theNode1
		)
		{
			Debug_Null_Pointer(theNode0);
			Debug_Null_Pointer(theNode1);
			return theNode0->Index() < theNode1->Index();
		}

		static std::vector<Point>
			RetrieveGeometry
			(
				const std::vector<std::shared_ptr<Aft_Node>>& theNodes
			);
	};
}

#include <Aft_NodeI.hxx>


#endif // !_Aft_Node_Header
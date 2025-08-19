#pragma once
#ifndef _Mesh_Node_Header
#define _Mesh_Node_Header

#include <Mesh_Entity.hxx>
#include <Mesh_NodeAdaptor.hxx>

#include <memory>

namespace tnbLib
{

	template<class NodeTraits>
	class Mesh_Node
		: public Mesh_Entity
		, public Mesh_NodeAdaptor
		<
		typename NodeTraits::edgeType,
		typename NodeTraits::elementType,
		typename NodeTraits::facetType
		>
	{

		typedef typename NodeTraits::ptType Point;
		typedef Mesh_NodeAdaptor
			<
			typename NodeTraits::edgeType,
			typename NodeTraits::elementType,
			typename NodeTraits::facetType
			> nodeAdaptor;

		/*Private Data*/

		Point theCoord_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_Entity>(*this);
			ar & boost::serialization::base_object<nodeAdaptor>(*this);
			ar & theCoord_;
		}

	public:

		typedef Point ptType;

		enum
		{
			rank = 0
		};

		static const std::shared_ptr<Mesh_Node> null_ptr;

		Mesh_Node()
		{}

		Mesh_Node
		(
			const Standard_Integer theIndex
		)
			: Mesh_Entity(theIndex)
		{}

		Mesh_Node
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: Mesh_Entity(theIndex)
			, theCoord_(theCoord)
		{}


		// public functions and operators [9/19/2022 Amir]

		const Point& Coord() const
		{
			return theCoord_;
		}

		Point& Coord()
		{
			return theCoord_;
		}

		virtual Standard_Boolean IsBoundary() const;

		void SetCoord(const Point& theCoord)
		{
			theCoord_ = theCoord;
		}


		//- Static functions and operators

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Mesh_Node>& theNode0,
			const std::shared_ptr<Mesh_Node>& theNode1
		);
	};
}

#include <Mesh_NodeI.hxx>

#endif // !_Mesh_Node_Header
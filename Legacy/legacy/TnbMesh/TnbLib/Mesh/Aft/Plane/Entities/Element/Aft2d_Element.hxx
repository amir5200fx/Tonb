#pragma once
#ifndef _Aft2d_Element_Header
#define _Aft2d_Element_Header

#include <Aft2d_ElementAdaptor.hxx>
#include <Aft2d_Entity.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/1/2023 Payvand]

		class Aft2d_Node;
		class Aft2d_Edge;

		class Aft2d_Element
			: public Aft2d_Entity
			, public Aft2d_ElementAdaptor
		{

			/*Private Data*/

			std::array<std::shared_ptr<Aft2d_Node>, 3> theNodes_;
			std::array<std::shared_ptr<Aft2d_Edge>, 3> theEdges_;


			// Private functions and operators [2/1/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_Element()
			{}

			// constructors [2/1/2023 Payvand]

			Aft2d_Element
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Aft2d_Node>, 3>& theNodes
			)
				: Aft2d_Entity(theIndex)
				, theNodes_(theNodes)
			{}

			Aft2d_Element
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft2d_Node>, 3>&& theNodes
			)
				: Aft2d_Entity(theIndex)
				, theNodes_(std::move(theNodes))
			{}


			// Public functions and operators [2/1/2023 Payvand]

			const auto& Nodes() const
			{
				return theNodes_;
			}

			auto& NodesRef()
			{
				return theNodes_;
			}

			const auto& Edges() const
			{
				return theEdges_;
			}

			auto& EdgesRef()
			{
				return theEdges_;
			}

			const auto& Node0() const
			{
				return std::get<0>(Nodes());
			}

			auto& Node0Ref()
			{
				return std::get<0>(NodesRef());
			}

			const auto& Node1() const
			{
				return std::get<1>(Nodes());
			}

			auto& Node1Ref()
			{
				return std::get<1>(NodesRef());
			}

			const auto& Node2() const
			{
				return std::get<2>(Nodes());
			}

			auto& Node2Ref()
			{
				return std::get<2>(NodesRef());
			}

			const auto& Edge0() const
			{
				return std::get<0>(Edges());
			}

			auto& Edge0Ref()
			{
				return std::get<0>(EdgesRef());
			}

			const auto& Edge1() const
			{
				return std::get<1>(Edges());
			}

			auto& Edge1Ref()
			{
				return std::get<1>(EdgesRef());
			}

			const auto& Edge2() const
			{
				return std::get<2>(Edges());
			}

			auto& Edge2Ref()
			{
				return std::get<2>(EdgesRef());
			}
		};
	}
}

#include <Aft2d_ElementI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft2d_Element);

#endif // !_Aft2d_Element_Header

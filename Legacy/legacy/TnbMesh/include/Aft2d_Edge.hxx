#pragma once
#ifndef _Aft2d_Edge_Header
#define _Aft2d_Edge_Header

#include <Aft2d_EdgeAdaptor.hxx>
#include <Aft2d_EdgeGeometry.hxx>
#include <Aft2d_Entity.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/1/2023 Payvand]
		class Aft2d_Node;

		class Aft2d_Edge
			: public Aft2d_Entity
			, public Aft2d_EdgeAdaptor
			, public Aft2d_EdgeGeometry
		{

			/*Private Data*/

			std::array<std::shared_ptr<Aft2d_Node>, 2> theNodes_;


			// Private functions and operators [2/1/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_Edge()
			{}

			// constructors [2/1/2023 Payvand]

			Aft2d_Edge
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Aft2d_Node>, 2>& theNodes
			)
				: Aft2d_Entity(theIndex)
				, theNodes_(theNodes)
			{}

			Aft2d_Edge
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft2d_Node>, 2>&& theNodes
			)
				: Aft2d_Entity(theIndex)
				, theNodes_(std::move(theNodes))
			{}


		public:

			// Public functions and operators [2/1/2023 Payvand]

			const auto& Nodes() const
			{
				return theNodes_;
			}

			auto& NodesRef()
			{
				return theNodes_;
			}

			virtual Standard_Boolean IsInterior() const;
			virtual Standard_Boolean IsBoundary() const;

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
		};
	}
}

#include <Aft2d_EdgeI.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft2d_Edge);

#endif // !_Aft2d_Edge_Header

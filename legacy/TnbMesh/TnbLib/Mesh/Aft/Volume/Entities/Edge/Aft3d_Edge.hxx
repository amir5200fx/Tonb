#pragma once
#ifndef _Aft3d_Edge_Header
#define _Aft3d_Edge_Header

#include <Aft3d_EdgeAdaptor.hxx>
#include <Aft3d_EdgeGeoemtry.hxx>
#include <Aft3d_Entity.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/23/2023 Payvand]
		class Aft3d_Node;

		class Aft3d_Edge
			: public Aft3d_Entity
			, public Aft3d_EdgeGeoemtry
			, public Aft3d_EdgeAdaptor
		{

		public:

			enum { nbNodes = 2, id0 = 0, id1 = 1 };

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Aft3d_Node>, nbNodes> theNodes_;


			// Private functions and operators [2/23/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [2/23/2023 Payvand]

			Aft3d_Edge()
			{}

			// constructors [2/23/2023 Payvand]

			Aft3d_Edge
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Aft3d_Node>, nbNodes>& theNodes
			)
				: Aft3d_Entity(theIndex)
				, theNodes_(theNodes)
			{}

			Aft3d_Edge
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft3d_Node>, nbNodes>&& theNodes
			)
				: Aft3d_Entity(theIndex)
				, theNodes_(std::move(theNodes))
			{}


		public:

			// Public functions and operators [2/23/2023 Payvand]

			const auto& Nodes() const
			{
				return theNodes_;
			}

			auto& NodesRef()
			{
				return theNodes_;
			}

			TnbLegMesh_EXPORT virtual Standard_Boolean IsInterior() const;
			TnbLegMesh_EXPORT virtual Standard_Boolean IsBoundary() const;

			const auto& Node0() const { return std::get<id0>(Nodes()); }
			auto& Node0Ref() { return std::get<id0>(NodesRef()); }

			const auto& Node1() const { return std::get<id1>(Nodes()); }
			auto& Node1Ref() { return std::get<id1>(NodesRef()); }

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft3d_Edge);

#endif // !_Aft3d_Edge_Header

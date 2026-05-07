#pragma once
#ifndef _MeshBLayer2d_AdvLayer_EdgeSet_Header
#define _MeshBLayer2d_AdvLayer_EdgeSet_Header

#include <MeshBLayer2d_Edge.hxx>

#include <set>
#include <vector>
#include <memory>

namespace tnbLib
{

	namespace meshBLayerLib
	{

		static auto edge_cmp = [](const std::shared_ptr<MeshBLayer2d_Edge>& theEdge)
		{
			return theEdge->Index();
		};

		class AdvLayer_EdgeSet
		{

			/*Private Data*/

			std::set<std::shared_ptr<MeshBLayer2d_Edge>, decltype(edge_cmp)> theEdges_;

		public:

			// default constructor [2/1/2023 Payvand]

			AdvLayer_EdgeSet()
				: theEdges_(edge_cmp)
			{}


			// constructors [2/1/2023 Payvand]



			// Public functions and operators [2/1/2023 Payvand]

			auto Size() const
			{
				return (Standard_Integer)theEdges_.size();
			}

			const auto& Edges() const
			{
				return theEdges_;
			}

			void Insert(const std::shared_ptr<MeshBLayer2d_Edge>&);
			void Remove(const std::shared_ptr<MeshBLayer2d_Edge>&);
		};
	}
}

#endif // !_MeshBLayer2d_AdvLayer_EdgeSet_Header

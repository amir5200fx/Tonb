#pragma once
#ifndef _MeshBLayer2d_AdvLayer_NodeSet_Header
#define _MeshBLayer2d_AdvLayer_NodeSet_Header

#include <MeshBLayer2d_Node.hxx>

#include <set>
#include <vector>
#include <memory>

namespace tnbLib
{


	// Forward Declarations [1/31/2023 Payvand]

	class MeshBLayer2d_Node;

	namespace meshBLayerLib
	{

		static auto node_cmp = [](const std::shared_ptr<MeshBLayer2d_Node>& theNode)
		{
			return theNode->Index();
		};

		class AdvLayer_NodeSet
		{

			/*Private Data*/

			std::set<std::shared_ptr<MeshBLayer2d_Node>, decltype(node_cmp)> theNodes_;

		public:

			// default constructor [1/31/2023 Payvand]

			AdvLayer_NodeSet()
				: theNodes_(node_cmp)
			{}


			// constructors [1/31/2023 Payvand]


			// Public functions and operators [1/31/2023 Payvand]

			auto Size() const
			{
				return (Standard_Integer)theNodes_.size();
			}

			const auto& Nodes() const
			{
				return theNodes_;
			}

			void Insert(const std::shared_ptr<MeshBLayer2d_Node>&);
			void Remove(const std::shared_ptr<MeshBLayer2d_Node>&);

		};
	}
}

#endif // !_MeshBLayer2d_AdvLayer_NodeSet_Header

#pragma once
#ifndef _Knit_ChainRegistry_Header
#define _Knit_ChainRegistry_Header

#include <Standard_TypeDef.hxx>

#include <map>
#include <vector>
#include <memory>

namespace tnbLib
{

	template<class NodeType, class EdgeType>
	class Knit_ChainRegistry
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<NodeType>> theNodes_;
		std::map<Standard_Integer, std::shared_ptr<EdgeType>> theEdges_;

	protected:

		// default constructor [1/3/2022 Amir]

		Knit_ChainRegistry()
		{}

		// constructors [1/3/2022 Amir]

	public:

		// public functions and operators [1/3/2022 Amir]

		auto NbNodes() const
		{
			return (Standard_Integer)theNodes_.size();
		}

		auto NbEdges() const
		{
			return (Standard_Integer)theEdges_.size();
		}

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

		void RemoveItem(const std::shared_ptr<NodeType>&);
		void RemoveItem(const std::shared_ptr<EdgeType>&);

		void Insert(const std::shared_ptr<NodeType>&);
		void Insert(const std::shared_ptr<EdgeType>&);
		void Insert(std::shared_ptr<NodeType>&&);
		void Insert(std::shared_ptr<EdgeType>&&);

		void ClearNodes();
		void ClearEdges();
	};
}

#include <Knit_ChainRegistryI.hxx>

#endif // !_Knit_ChainRegistry_Header

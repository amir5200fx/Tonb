#pragma once
#ifndef _tools_Header
#define _tools_Header

#include <Aft2d_Edge.hxx>
#include <Global_Indexed.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SupEdge;

	class SupNode
		: public Global_Indexed
	{

		/*Private Data*/

		std::shared_ptr<Aft2d_Node> theNode_;

		std::weak_ptr<SupEdge> theBackward_;
		std::weak_ptr<SupEdge> theForward_;

	public:

		// default constructor

		SupNode()
		{}

		// constrcutors

		SupNode(const Standard_Integer theIndex, const std::shared_ptr<Aft2d_Node>& theNode)
			: Global_Indexed(theIndex)
			, theNode_(theNode)
		{}

		// Public functions and operators

		const auto& Node() const { return theNode_; }

		const auto& Backward() const { return theBackward_; }
		const auto& Forward() const { return theForward_; }

		std::shared_ptr<SupNode> Forward(const std::shared_ptr<SupNode>&) const;

		void SetNode(const std::shared_ptr<Aft2d_Node>& theNode) { theNode_ = theNode; }
		void SetBackward(const std::weak_ptr<SupEdge>& theEdge) { theBackward_ = theEdge; }
		void SetForward(const std::weak_ptr<SupEdge>& theEdge) { theForward_ = theEdge; }

	};

	class SupEdge
		: public Global_Indexed
	{

		/*Private Data*/

		std::shared_ptr<Aft2d_Edge> theEdge_;

		std::shared_ptr<SupNode> theNode0_;
		std::shared_ptr<SupNode> theNode1_;

	public:

		// default constructor

		SupEdge()
		{}

		// constructors

		SupEdge
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<SupNode>& theNode0,
			const std::shared_ptr<SupNode>& theNode1
		)
			: Global_Indexed(theIndex)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
		{}

		// Public functions and operators

		const auto& Node0() const { return theNode0_; }
		const auto& Node1() const { return theNode1_; }

		const auto& Edge() const { return theEdge_; }

		void SetEdge(const std::shared_ptr<Aft2d_Edge>& theEdge) { theEdge_ = theEdge; }

	};

	namespace tools
	{

		std::vector<std::shared_ptr<Aft2d_Node>> RetrieveNodes(const std::vector<std::shared_ptr<Aft2d_Edge>>&);
		std::vector<std::shared_ptr<SupEdge>> RetrieveSupEdges(const std::vector<std::shared_ptr<Aft2d_Edge>>&);

	}
}

#endif // !_tools_Header

#pragma once
#ifndef _tools_Header
#define _tools_Header

#include <Aft2d_SegmentEdgeFwd.hxx>
#include <Aft2d_NodeFwd.hxx>
#include <Mesh_BndLayer_Info.hxx>
#include <Entity2d_QuadMesh.hxx>
#include <Entity2d_PolygonFwd.hxx>
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
		std::shared_ptr<Aft2d_Node> theOffset_;

		std::weak_ptr<SupEdge> theBackward_;
		std::weak_ptr<SupEdge> theForward_;

	public:

		// default constructor

		SupNode()
		= default;

		// constrcutors

		SupNode(const Standard_Integer theIndex, const std::shared_ptr<Aft2d_Node>& theNode)
			: Global_Indexed(theIndex)
			, theNode_(theNode)
		{}

		// Public functions and operators

		Standard_Integer NbEdges() const;
		Standard_Boolean HasBackward() const;
		Standard_Boolean HasForward() const;
		Standard_Boolean IsManifold() const;

		Pnt2d Coord() const;

		const auto& Node() const { return theNode_; }
		const auto& Offset() const { return theOffset_; }

		const auto& Backward() const { return theBackward_; }
		const auto& Forward() const { return theForward_; }

		std::shared_ptr<SupNode> Next() const;

		void SetNode(const std::shared_ptr<Aft2d_Node>& theNode) { theNode_ = theNode; }
		void SetBackward(const std::weak_ptr<SupEdge>& theEdge) { theBackward_ = theEdge; }
		void SetForward(const std::weak_ptr<SupEdge>& theEdge) { theForward_ = theEdge; }
		void SetOffset(const std::shared_ptr<Aft2d_Node>& theNode) { theOffset_ = theNode; }
		void SetOffset(std::shared_ptr<Aft2d_Node>&& theNode) { theOffset_ = std::move(theNode); }

	};

	class SupEdge
		: public Global_Indexed
	{

		/*Private Data*/

		std::shared_ptr<Aft2d_SegmentEdge> theEdge_;
		std::shared_ptr<Aft2d_SegmentEdge> theOffset_;

		std::shared_ptr<SupNode> theNode0_;
		std::shared_ptr<SupNode> theNode1_;

	public:

		// default constructor

		SupEdge()
		= default;

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
		const auto& Offset() const { return theOffset_; }

		void SetEdge(const std::shared_ptr<Aft2d_SegmentEdge>& theEdge) { theEdge_ = theEdge; }
		void SetOffset(const std::shared_ptr<Aft2d_SegmentEdge>& theEdge) { theOffset_ = theEdge; }
		void SetOffset(std::shared_ptr<Aft2d_SegmentEdge>&& theEdge) { theOffset_ = std::move(theEdge); }

	};

	template<class EdgeType>
	struct EdgeSet
	{
		std::vector<std::shared_ptr<EdgeType>> edges;
	};

	template<class EdgeType>
	struct WireSet
	{
		std::vector<std::shared_ptr<EdgeType>> edges;
	};

	

	namespace tools
	{

		std::vector<std::shared_ptr<Aft2d_Node>>
			RetrieveNodes(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&);
		std::vector<std::shared_ptr<SupEdge>>
			RetrieveSupEdges(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&);
		std::shared_ptr<Entity2d_Polygon> RetrievePolygon(const std::vector<std::shared_ptr<SupEdge>>&);
		std::vector<std::shared_ptr<SupNode>> RetrieveNodes(const std::vector<std::shared_ptr<SupEdge>>&);
		std::vector<std::shared_ptr<SupNode>> TrackNodes(const std::shared_ptr<SupNode>&);

		std::map<Standard_Integer, std::shared_ptr<EdgeSet<Aft2d_SegmentEdge>>>
			RetrieveBoundaries(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&);

		std::vector<std::shared_ptr<WireSet<SupEdge>>> RetrieveWires(const std::map<Standard_Integer, std::shared_ptr<EdgeSet<Aft2d_SegmentEdge>>>&, const std::set<Standard_Integer>& theIds);
		std::vector<std::shared_ptr<WireSet<SupEdge>>> RetrieveWires(const std::vector<std::shared_ptr<SupEdge>>&);

		std::shared_ptr<Entity2d_Polygon> ClosePolygon(const Entity2d_Polygon&);
		std::shared_ptr<Entity2d_Polygon> RetrievePolygon(const WireSet<SupEdge>&);
		std::vector<std::shared_ptr<Entity2d_Polygon>> RetrieveInnerPolygons(const std::vector<std::shared_ptr<WireSet<SupEdge>>>&);

		std::vector<std::shared_ptr<Aft2d_SegmentEdge>> CreateEdges(const Entity2d_Polygon&);
		
		void CheckWire(const std::vector<std::shared_ptr<SupEdge>>&);

	}

	namespace bndLayer
	{

		std::pair<std::vector<std::shared_ptr<Aft2d_SegmentEdge>>, std::shared_ptr<Entity2d_QuadMesh>>
			CalcBndLayer(const std::vector<std::shared_ptr<SupEdge>>&, const Mesh_BndLayer_Info& theInfo);

		void SetOffsets(const std::vector<std::shared_ptr<SupNode>>&, const Entity2d_Polygon&);
		void CalcOffsetEdges(const std::vector<std::shared_ptr<SupEdge>>&);
	}
}

#endif // !_tools_Header

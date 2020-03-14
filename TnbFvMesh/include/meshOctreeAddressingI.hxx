#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	inline label meshOctreeAddressing::numberOfNodes() const
	{
		if (!nodeLabelsPtr_)
			createNodeLabels();

		return nNodes_;
	}

	inline const pointField& meshOctreeAddressing::octreePoints() const
	{
		if (!octreePointsPtr_)
			createOctreePoints();

		return *octreePointsPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::nodeLabels() const
	{
		if (!nodeLabelsPtr_)
			createNodeLabels();

		return *nodeLabelsPtr_;
	}

	inline const FRWGraph<label, 8>& meshOctreeAddressing::nodeLeaves() const
	{
		if (!nodeLeavesPtr_)
			createNodeLeaves();

		return *nodeLeavesPtr_;
	}

	inline const List<direction>& meshOctreeAddressing::boxType() const
	{
		if (!boxTypePtr_)
			findUsedBoxes();

		return *boxTypePtr_;
	}

	inline void meshOctreeAddressing::setBoxType
	(
		const label boxI,
		const direction type
	)
	{
		if (boxTypePtr_)
		{
			List<direction>& boxType = *boxTypePtr_;
			boxType[boxI] |= type;
		}
	}

	inline const meshOctree& meshOctreeAddressing::octree() const
	{
		return octree_;
	}

	inline const List<direction>& meshOctreeAddressing::nodeType() const
	{
		if (!nodeTypePtr_)
			calculateNodeType();

		return *nodeTypePtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::octreeFaces() const
	{
		if (!octreeFacesPtr_)
			createOctreeFaces();

		return *octreeFacesPtr_;
	}

	inline const labelLongList& meshOctreeAddressing::octreeFaceOwner() const
	{
		if (!octreeFacesOwnersPtr_)
			createOctreeFaces();

		return *octreeFacesOwnersPtr_;
	}

	inline const labelLongList& meshOctreeAddressing::octreeFaceNeighbour() const
	{
		if (!octreeFacesNeighboursPtr_)
			createOctreeFaces();

		return *octreeFacesNeighboursPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::leafFaces() const
	{
		if (!leafFacesPtr_)
			calculateLeafFaces();

		return *leafFacesPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::leafLeaves() const
	{
		if (!leafLeavesPtr_)
			calculateLeafLeaves();

		return *leafLeavesPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::nodeFaces() const
	{
		if (!nodeFacesPtr_)
			calculateNodeFaces();

		return *nodeFacesPtr_;
	}

	inline const LongList<edge>& meshOctreeAddressing::octreeEdges() const
	{
		if (!octreeEdgesPtr_)
			createOctreeEdges();

		return *octreeEdgesPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::edgeLeaves() const
	{
		if (!edgeLeavesPtr_)
			calculateEdgeLeaves();

		return *edgeLeavesPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::leafEdges() const
	{
		if (!leafEdgesPtr_)
			calculateLeafEdges();

		return *leafEdgesPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::nodeEdges() const
	{
		if (!nodeEdgesPtr_)
			createOctreeEdges();

		return *nodeEdgesPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::faceEdges() const
	{
		if (!faceEdgesPtr_)
			createOctreeEdges();

		return *faceEdgesPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::edgeFaces() const
	{
		if (!edgeFacesPtr_)
			calculateEdgeFaces();

		return *edgeFacesPtr_;
	}

	inline const labelLongList& meshOctreeAddressing::globalPointLabel() const
	{
		if (!globalPointLabelPtr_)
			calcGlobalPointLabels();

		return *globalPointLabelPtr_;
	}

	inline const Map<label>& meshOctreeAddressing::
		globalToLocalPointAddressing() const
	{
		if (!globalPointToLocalPtr_)
			calcGlobalPointLabels();

		return *globalPointToLocalPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::pointAtProcs() const
	{
		if (!pointProcsPtr_)
			calcGlobalPointLabels();

		return *pointProcsPtr_;
	}

	inline const labelLongList& meshOctreeAddressing::globalFaceLabel() const
	{
		if (!globalFaceLabelPtr_)
			calcGlobalFaceLabels();

		return *globalFaceLabelPtr_;
	}

	inline const Map<label>& meshOctreeAddressing::
		globalToLocalFaceAddressing() const
	{
		if (!globalFaceToLocalPtr_)
			calcGlobalFaceLabels();

		return *globalFaceToLocalPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::faceAtProcs() const
	{
		if (!faceProcsPtr_)
			calcGlobalFaceLabels();

		return *faceProcsPtr_;
	}

	inline const labelLongList& meshOctreeAddressing::globalLeafLabel() const
	{
		if (!globalLeafLabelPtr_)
			calcGlobalLeafLabels();

		return *globalLeafLabelPtr_;
	}

	inline const VRWGraph& meshOctreeAddressing::leafAtProcs() const
	{
		if (!leafAtProcsPtr_)
			calcGlobalLeafLabels();

		return *leafAtProcsPtr_;
	}

	inline const Map<label>& meshOctreeAddressing::
		globalToLocalLeafAddressing() const
	{
		if (!globalLeafToLocalPtr_)
			calcGlobalLeafLabels();

		return *globalLeafToLocalPtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
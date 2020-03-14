#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	inline const meshOctree& meshOctreeModifier::octree() const
	{
		return octree_;
	}

	inline labelList& meshOctreeModifier::neiProcsAccess()
	{
		return octree_.neiProcs_;
	}

	inline boundBox& meshOctreeModifier::rootBoxAccess()
	{
		return octree_.rootBox_;
	}

	inline bool& meshOctreeModifier::isRootInitialisedAccess()
	{
		return octree_.isRootInitialised_;
	}

	inline scalar& meshOctreeModifier::searchRangeAccess()
	{
		return octree_.searchRange_;
	}

	inline List<Pair<meshOctreeCubeCoordinates> >&
		meshOctreeModifier::neiRangeAccess()
	{
		return octree_.neiRange_;
	}

	inline meshOctreeCube& meshOctreeModifier::initialCubeAccess()
	{
		return *octree_.initialCubePtr_;
	}

	inline List<meshOctreeSlot>& meshOctreeModifier::dataSlotsAccess()
	{
		return octree_.dataSlots_;
	}

	inline meshOctreeCube* meshOctreeModifier::findCubeForPosition
	(
		const meshOctreeCubeCoordinates& cc
	) const
	{
		return octree_.findCubeForPosition(cc);
	}

	inline void meshOctreeModifier::findLeavesContainedInBox
	(
		const boundBox& bb,
		DynList<const meshOctreeCube*, 256>& containedLeaves
	) const
	{
		containedLeaves.clear();
		octree_.findLeavesContainedInBox(bb, containedLeaves);
	}

	inline LongList<meshOctreeCube*>& meshOctreeModifier::leavesAccess()
	{
		return octree_.leaves_;
	}

	inline void meshOctreeModifier::createListOfLeaves()
	{
		octree_.leaves_.clear();

		octree_.initialCubePtr_->findLeaves(octree_.leaves_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
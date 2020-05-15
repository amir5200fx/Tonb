#include <meshOctreeModifier.hxx>

#include <triSurf.hxx>
#include <demandDrivenData.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshOctreeModifier::reduceMemoryConsumption()
	{
		//createListOfLeaves();

		const LongList<meshOctreeCube*>& leaves = octree_.leaves_;

		forAll(octree_.dataSlots_, slotI)
		{
			//- deleting triangles
			VRWGraph& containedTriangles =
				octree_.dataSlots_[slotI].containedTriangles_;
			label nElmts = containedTriangles.size();
			boolList mayDeleteData(nElmts, true);
			forAll(leaves, leafI)
			{
				const meshOctreeCube& oc = *leaves[leafI];

				if (
					oc.hasContainedElements() &&
					oc.slotPtr() == &octree_.dataSlots_[slotI]
					)
					mayDeleteData[oc.containedElements()] = false;
			}

			for (label i = 0; i < nElmts; ++i)
				if (mayDeleteData[i])
					containedTriangles.setRowSize(i, 0);
			containedTriangles.optimizeMemoryUsage();

			//- deleting edges
			VRWGraph& containedEdges =
				octree_.dataSlots_[slotI].containedEdges_;
			nElmts = containedEdges.size();
			mayDeleteData.setSize(nElmts);
			mayDeleteData = true;
			forAll(leaves, leafI)
			{
				const meshOctreeCube& oc = *leaves[leafI];

				if (
					oc.hasContainedEdges() &&
					oc.slotPtr() == &octree_.dataSlots_[slotI]
					)
					mayDeleteData[oc.containedEdges()] = false;
			}

			for (label i = 0; i < nElmts; ++i)
				if (mayDeleteData[i])
					containedEdges.setRowSize(i, 0);

			containedEdges.optimizeMemoryUsage();
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
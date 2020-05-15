#include <meshOctree.hxx>

#include <triSurf.hxx>
#include <demandDrivenData.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshOctree::findBoundaryPatchesForLeaf
	(
		const label leafI,
		DynList<label>& patches
	) const
	{
		if (leaves_[leafI]->hasContainedElements())
		{
			patches.clear();
			const VRWGraph& ct = leaves_[leafI]->slotPtr()->containedTriangles_;
			const constRow ce =
				ct[leaves_[leafI]->containedElements()];
			forAll(ce, elI)
				patches.appendIfNotIn(surface_[ce[elI]].region());
		}
		else
		{
			patches.clear();
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
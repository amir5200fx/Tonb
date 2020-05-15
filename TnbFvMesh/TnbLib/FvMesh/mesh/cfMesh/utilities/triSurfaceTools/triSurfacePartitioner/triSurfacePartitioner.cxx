#include <triSurfacePartitioner.hxx>

#include <demandDrivenData.hxx>

# ifdef DEBUGPartitioner
#include <sstream>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	triSurfacePartitioner::triSurfacePartitioner
	(
		const triSurf& surface
	)
		:
		surface_(surface),
		corners_(),
		cornerPatches_(),
		patchPatches_(surface.patches().size()),
		edgeGroups_(),
		edgeGroupEdgeGroups_(),
		patchesEdgeGroups_(),
		edgeGroupsCorners_()
	{
		calculatePatchAddressing();
	}

	triSurfacePartitioner::~triSurfacePartitioner()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const labelList& triSurfacePartitioner::corners() const
	{
		return corners_;
	}

	const List<DynList<label> >& triSurfacePartitioner::cornerPatches() const
	{
		return cornerPatches_;
	}

	const List<labelHashSet>& triSurfacePartitioner::patchPatches() const
	{
		return patchPatches_;
	}

	const labelList& triSurfacePartitioner::edgeGroups() const
	{
		return edgeGroups_;
	}

	const List<labelHashSet>& triSurfacePartitioner::edgeGroupEdgeGroups() const
	{
		return edgeGroupEdgeGroups_;
	}

	void triSurfacePartitioner::edgeGroupsSharedByPatches
	(
		const label patch1,
		const label patch2,
		DynList<label>& edgeGroups
	) const
	{
		edgeGroups.clear();

		std::pair<label, label> pp
		(
			tnbLib::min(patch1, patch2),
			tnbLib::max(patch1, patch2)
		);

		std::map<std::pair<label, label>, labelHashSet>::const_iterator it =
			patchesEdgeGroups_.find(pp);

		if (it != patchesEdgeGroups_.end())
		{
			const labelHashSet& eGroups = it->second;

			forAllConstIter(labelHashSet, eGroups, it)
				edgeGroups.append(it.key());
		}
	}

	void triSurfacePartitioner::cornersSharedByEdgeGroups
	(
		const label edgeGroup1,
		const label edgeGroup2,
		DynList<label>& corners
	) const
	{
		corners.clear();

		std::pair<label, label> ep
		(
			tnbLib::min(edgeGroup1, edgeGroup2),
			tnbLib::max(edgeGroup1, edgeGroup2)
		);

		std::map<std::pair<label, label>, labelHashSet>::const_iterator it =
			edgeGroupsCorners_.find(ep);

		if (it != edgeGroupsCorners_.end())
		{
			const labelHashSet& corn = it->second;

			forAllConstIter(labelHashSet, corn, it)
				corners.append(it.key());
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
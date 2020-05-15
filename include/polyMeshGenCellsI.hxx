#pragma once
namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline const cellListPMG& polyMeshGenCells::cells() const
	{
		return cells_;
	}

	inline void polyMeshGenCells::addCellToSubset
	(
		const label selID,
		const label cellI
	)
	{
		std::map<label, meshSubset>::iterator it = cellSubsets_.find(selID);
		if (it == cellSubsets_.end())
			return;

		it->second.addElement(cellI);
	}

	inline void polyMeshGenCells::removeCellFromSubset
	(
		const label selID,
		const label cellI
	)
	{
		std::map<label, meshSubset>::iterator it = cellSubsets_.find(selID);
		if (it == cellSubsets_.end())
			return;

		it->second.removeElement(cellI);
	}

	inline void polyMeshGenCells::cellInSubsets
	(
		const label cellI,
		DynList<label>& cellSubsets
	) const
	{
		cellSubsets.clear();

		std::map<label, meshSubset>::const_iterator it;
		for
			(
				it = cellSubsets_.begin();
				it != cellSubsets_.end();
				++it
				)
		{
			if (it->second.contains(cellI))
				cellSubsets.append(it->first);
		}
	}

	inline void polyMeshGenCells::cellSubsetIndices(DynList<label>& indices) const
	{
		indices.clear();

		std::map<label, meshSubset>::const_iterator it;
		for
			(
				it = cellSubsets_.begin();
				it != cellSubsets_.end();
				++it
				)
			indices.append(it->first);
	}

	template<class ListType>
	inline void polyMeshGenCells::cellsInSubset
	(
		const label selID,
		ListType& cellLabels
	) const
	{
		cellLabels.clear();

		std::map<label, meshSubset>::const_iterator it =
			cellSubsets_.find(selID);
		if (it == cellSubsets_.end())
			return;

		it->second.containedElements(cellLabels);
	}

	template<class ListType>
	inline void polyMeshGenCells::updateCellSubsets
	(
		const ListType& newCellLabels
	)
	{
		for
			(
				std::map<label, meshSubset>::iterator it = cellSubsets_.begin();
				it != cellSubsets_.end();
				++it
				)
			it->second.updateSubset(newCellLabels);
	}

	inline void polyMeshGenCells::updateCellSubsets
	(
		const VRWGraph& newCellsForCell
	)
	{
		for
			(
				std::map<label, meshSubset>::iterator it = cellSubsets_.begin();
				it != cellSubsets_.end();
				++it
				)
			it->second.updateSubset(newCellsForCell);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
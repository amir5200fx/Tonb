#pragma once
namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline label triSurfPoints::nPoints() const
	{
		return points_.size();
	}

	inline const pointField& triSurfPoints::points() const
	{
		return points_;
	}

	inline void triSurfPoints::appendVertex(const point& p)
	{
		const label s = points_.size();
		points_.setSize(s + 1);
		points_[s] = p;
	}

	inline void triSurfPoints::addPointToSubset
	(
		const label setI,
		const label pointI
	)
	{
		Map<meshSubset>::iterator it = pointSubsets_.find(setI);
		if (it == pointSubsets_.end())
			return;

		it().addElement(pointI);
	}

	inline void triSurfPoints::removePointFromSubset
	(
		const label setI,
		const label pointI
	)
	{
		Map<meshSubset>::iterator it = pointSubsets_.find(setI);
		if (it == pointSubsets_.end())
			return;

		it().removeElement(pointI);
	}

	inline void triSurfPoints::pointInSubsets
	(
		const label pointI,
		DynList<label>& pointSubsets
	) const
	{
		pointSubsets.clear();

		forAllConstIter
		(
			Map<meshSubset>,
			pointSubsets_,
			it
		)
		{
			if (it().contains(pointI))
				pointSubsets.append(it.key());
		}
	}

	inline void triSurfPoints::pointSubsetIndices(DynList<label>& indices) const
	{
		indices.clear();

		forAllConstIter
		(
			Map<meshSubset>,
			pointSubsets_,
			it
		)
			indices.append(it.key());
	}

	template<class ListType>
	inline void triSurfPoints::pointsInSubset
	(
		const label setI,
		ListType& pointLabels
	) const
	{
		pointLabels.clear();

		Map<meshSubset>::const_iterator it =
			pointSubsets_.find(setI);
		if (it == pointSubsets_.end())
			return;

		it().containedElements(pointLabels);
	}

	template<class ListType>
	inline void triSurfPoints::updatePointSubsets(const ListType& newNodeLabels)
	{
		for
			(
				Map<meshSubset>::iterator it = pointSubsets_.begin();
				it != pointSubsets_.end();
				++it
				)
			it().updateSubset(newNodeLabels);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
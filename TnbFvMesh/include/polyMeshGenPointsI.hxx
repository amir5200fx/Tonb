#pragma once
namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline const Time& polyMeshGenPoints::returnTime() const
	{
		return runTime_;
	}

	inline const pointFieldPMG& polyMeshGenPoints::points() const
	{
		return points_;
	}

	inline pointFieldPMG& polyMeshGenPoints::points()
	{
		return points_;
	}

	inline void polyMeshGenPoints::appendVertex(const point& p)
	{
		points_.append(p);
	}

	inline void polyMeshGenPoints::addPointToSubset
	(
		const label setI,
		const label pointI
	)
	{
		std::map<label, meshSubset>::iterator it = pointSubsets_.find(setI);
		if (it == pointSubsets_.end())
			return;

		it->second.addElement(pointI);
	}

	inline void polyMeshGenPoints::removePointFromSubset
	(
		const label setI,
		const label pointI
	)
	{
		std::map<label, meshSubset>::iterator it = pointSubsets_.find(setI);
		if (it == pointSubsets_.end())
			return;

		it->second.removeElement(pointI);
	}

	inline void polyMeshGenPoints::pointInSubsets
	(
		const label pointI,
		DynList<label>& pointSubsets
	) const
	{
		pointSubsets.clear();

		std::map<label, meshSubset>::const_iterator it;
		for
			(
				it = pointSubsets_.begin();
				it != pointSubsets_.end();
				++it
				)
		{
			if (it->second.contains(pointI))
				pointSubsets.append(it->first);
		}
	}

	inline void polyMeshGenPoints::pointSubsetIndices(DynList<label>& indices) const
	{
		indices.clear();

		std::map<label, meshSubset>::const_iterator it;
		for
			(
				it = pointSubsets_.begin();
				it != pointSubsets_.end();
				++it
				)
			indices.append(it->first);
	}

	template<class ListType>
	inline void polyMeshGenPoints::pointsInSubset
	(
		const label setI,
		ListType& pointLabels
	) const
	{
		pointLabels.clear();

		std::map<label, meshSubset>::const_iterator it =
			pointSubsets_.find(setI);
		if (it == pointSubsets_.end())
			return;

		it->second.containedElements(pointLabels);
	}

	template<class ListType>
	inline void polyMeshGenPoints::updatePointSubsets(const ListType& newNodeLabels)
	{
		for
			(
				std::map<label, meshSubset>::iterator it = pointSubsets_.begin();
				it != pointSubsets_.end();
				++it
				)
			it->second.updateSubset(newNodeLabels);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
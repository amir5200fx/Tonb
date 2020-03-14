#pragma once
namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline label triSurfFeatureEdges::nFeatureEdges() const
	{
		return featureEdges_.size();
	}

	inline const edgeLongList& triSurfFeatureEdges::featureEdges() const
	{
		return featureEdges_;
	}

	inline void triSurfFeatureEdges::appendFeatureEdge(const edge& e)
	{
		featureEdges_.append(e);
	}

	inline void triSurfFeatureEdges::addEdgeToSubset
	(
		const label setI,
		const label eI
	)
	{
		Map<meshSubset>::iterator it = featureEdgeSubsets_.find(setI);
		if (it == featureEdgeSubsets_.end())
			return;

		it().addElement(eI);
	}

	inline void triSurfFeatureEdges::removeEdgeFromSubset
	(
		const label setI,
		const label eI
	)
	{
		Map<meshSubset>::iterator it = featureEdgeSubsets_.find(setI);
		if (it == featureEdgeSubsets_.end())
			return;

		it().removeElement(eI);
	}

	inline void triSurfFeatureEdges::edgeInSubsets
	(
		const label eI,
		DynList<label>& edgeSubsets
	) const
	{
		edgeSubsets.clear();

		forAllConstIter
		(
			Map<meshSubset>,
			featureEdgeSubsets_,
			it
		)
		{
			if (it().contains(eI))
				edgeSubsets.append(it.key());
		}
	}

	inline void triSurfFeatureEdges::edgeSubsetIndices
	(
		DynList<label>& indices
	) const
	{
		indices.clear();

		forAllConstIter
		(
			Map<meshSubset>,
			featureEdgeSubsets_,
			it
		)
			indices.append(it.key());
	}

	template<class ListType>
	inline void triSurfFeatureEdges::edgesInSubset
	(
		const label setI,
		ListType& edgeLabels
	) const
	{
		edgeLabels.clear();

		Map<meshSubset>::const_iterator it = featureEdgeSubsets_.find(setI);
		if (it == featureEdgeSubsets_.end())
			return;

		it().containedElements(edgeLabels);
	}

	template<class ListType>
	inline void triSurfFeatureEdges::updateEdgeSubsets
	(
		const ListType& newEdgeLabels
	)
	{
		for
			(
				Map<meshSubset>::iterator it = featureEdgeSubsets_.begin();
				it != featureEdgeSubsets_.end();
				++it
				)
			it().updateSubset(newEdgeLabels);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
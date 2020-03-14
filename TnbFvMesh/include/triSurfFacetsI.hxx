#pragma once
namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline label triSurfFacets::size() const
	{
		return triangles_.size();
	}

	inline const LongList<labelledTri>& triSurfFacets::facets() const
	{
		return triangles_;
	}

	inline const geometricSurfacePatchList& triSurfFacets::patches() const
	{
		return patches_;
	}

	inline void triSurfFacets::appendTriangle(const labelledTri& tri)
	{
		triangles_.append(tri);
	}

	inline void triSurfFacets::addFacetToSubset
	(
		const label setI,
		const label triI
	)
	{
		Map<meshSubset>::iterator it = facetSubsets_.find(setI);
		if (it == facetSubsets_.end())
			return;

		it().addElement(triI);
	}

	inline void triSurfFacets::removeFacetFromSubset
	(
		const label setI,
		const label triI
	)
	{
		Map<meshSubset>::iterator it = facetSubsets_.find(setI);
		if (it == facetSubsets_.end())
			return;

		it().removeElement(triI);
	}

	inline void triSurfFacets::facetInSubsets
	(
		const label triI,
		DynList<label>& facetSubsets
	) const
	{
		facetSubsets.clear();

		forAllConstIter
		(
			Map<meshSubset>,
			facetSubsets_,
			it
		)
		{
			if (it().contains(triI))
				facetSubsets.append(it.key());
		}
	}

	inline void triSurfFacets::facetSubsetIndices(DynList<label>& indices) const
	{
		indices.clear();

		forAllConstIter
		(
			Map<meshSubset>,
			facetSubsets_,
			it
		)
			indices.append(it.key());
	}

	template<class ListType>
	inline void triSurfFacets::facetsInSubset
	(
		const label setI,
		ListType& facetsLabels
	) const
	{
		facetsLabels.clear();

		Map<meshSubset>::const_iterator it = facetSubsets_.find(setI);
		if (it == facetSubsets_.end())
			return;

		it().containedElements(facetsLabels);
	}

	template<class ListType>
	inline void triSurfFacets::updateFacetsSubsets(const ListType& newFacetsLabels)
	{
		for
			(
				Map<meshSubset>::iterator it = facetSubsets_.begin();
				it != facetSubsets_.end();
				++it
				)
			it().updateSubset(newFacetsLabels);
	}

	inline const labelledTri& triSurfFacets::operator[](const label triI) const
	{
		return triangles_[triI];
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
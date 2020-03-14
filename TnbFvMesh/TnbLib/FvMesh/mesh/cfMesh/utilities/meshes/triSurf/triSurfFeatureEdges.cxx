#include <triSurfFeatureEdges.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	triSurfFeatureEdges::triSurfFeatureEdges()
		:
		featureEdges_(),
		featureEdgeSubsets_()
	{}

	triSurfFeatureEdges::triSurfFeatureEdges(const edgeLongList& featureEdges)
		:
		featureEdges_(featureEdges),
		featureEdgeSubsets_()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Destructor
	triSurfFeatureEdges::~triSurfFeatureEdges()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	label triSurfFeatureEdges::addEdgeSubset(const word& subsetName)
	{
		label id = edgeSubsetIndex(subsetName);
		if (id >= 0)
		{
			Warning << "Edge subset " << subsetName << " already exists!" << endl;
			return id;
		}

		id = 0;
		forAllConstIter(Map<meshSubset>, featureEdgeSubsets_, it)
			id = tnbLib::max(id, it.key() + 1);

		featureEdgeSubsets_.insert
		(
			id,
			meshSubset(subsetName, meshSubset::FEATUREEDGESUBSET)
		);

		return id;
	}

	void triSurfFeatureEdges::removeEdgeSubset(const label subsetID)
	{
		if (featureEdgeSubsets_.find(subsetID) == featureEdgeSubsets_.end())
			return;

		featureEdgeSubsets_.erase(subsetID);
	}

	word triSurfFeatureEdges::edgeSubsetName(const label subsetID) const
	{
		Map<meshSubset>::const_iterator it = featureEdgeSubsets_.find(subsetID);
		if (it == featureEdgeSubsets_.end())
		{
			Warning << "Subset " << subsetID << " is not an edge subset" << endl;
			return word();
		}

		return it().name();
	}

	label triSurfFeatureEdges::edgeSubsetIndex(const word& subsetName) const
	{
		forAllConstIter(Map<meshSubset>, featureEdgeSubsets_, it)
		{
			if (it().name() == subsetName)
				return it.key();
		}

		return -1;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
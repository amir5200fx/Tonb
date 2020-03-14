#include <triSurfPoints.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	triSurfPoints::triSurfPoints()
		:
		points_(),
		pointSubsets_()
	{}

	triSurfPoints::triSurfPoints(const pointField& points)
		:
		points_(points),
		pointSubsets_()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Destructor
	triSurfPoints::~triSurfPoints()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	label triSurfPoints::addPointSubset(const word& subsetName)
	{
		label id = pointSubsetIndex(subsetName);
		if (id >= 0)
		{
			Warning << "Point subset " << subsetName << " already exists!" << endl;
			return id;
		}

		id = 0;
		forAllConstIter(Map<meshSubset>, pointSubsets_, it)
			id = tnbLib::max(id, it.key() + 1);

		pointSubsets_.insert
		(
			id,
			meshSubset(subsetName, meshSubset::POINTSUBSET)
		);

		return id;
	}

	void triSurfPoints::removePointSubset(const label subsetID)
	{
		if (pointSubsets_.find(subsetID) == pointSubsets_.end())
			return;

		pointSubsets_.erase(subsetID);
	}

	word triSurfPoints::pointSubsetName(const label subsetID) const
	{
		Map<meshSubset>::const_iterator it = pointSubsets_.find(subsetID);
		if (it == pointSubsets_.end())
		{
			Warning << "Subset " << subsetID << " is not a point subset" << endl;
			return word();
		}

		return it().name();
	}

	label triSurfPoints::pointSubsetIndex(const word& subsetName) const
	{
		forAllConstIter(Map<meshSubset>, pointSubsets_, it)
		{
			if (it().name() == subsetName)
				return it.key();
		}

		return -1;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
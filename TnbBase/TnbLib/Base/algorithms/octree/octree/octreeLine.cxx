#include <octreeLine.hxx>

#include <octree.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Calculate sorted list of intersections
template <class Type>
void tnbLib::octreeLine<Type>::calcSortedIntersections()
{
	// Determine intersections and sort acc. to distance to start

	const labelList& indices = currentLeaf_->indices();

	sortedIntersections_.setSize(indices.size());

	const vector direction = endPoint_ - realStartPoint_;

	label nHits = 0;

	forAll(indices, elemI)
	{
		point pt;
		bool hit = tree_.shapes().intersects
		(
			indices[elemI],
			realStartPoint_,
			direction,
			pt
		);

		if (hit && (indices[elemI] != lastElem_))
		{
			sortedIntersections_[nHits++] = pointHitSort
			(
				pointHit
				(
					true,
					pt,
					tnbLib::magSqr(pt - leafExitPoint_),
					false
				),
				indices[elemI]
			);
		}
	}

	sortedIntersections_.setSize(nHits);

	tnbLib::sort(sortedIntersections_);

	//// After sorting
	//forAll(sortedIntersections_, i)
	//{
	//    Pout<< "calcSortedIntersections: After sorting:"
	//        << i << "  distance:"
	//        << sortedIntersections_[i].inter().distance()
	//        << "  index:" << sortedIntersections_[i].index()
	//        << endl;
	//}

	lastElem_ = -1;

	if (nHits > 0)
	{
		lastElem_ = sortedIntersections_[nHits - 1].index();

		//Pout<< "Storing lastElem_:" << lastElem_ << endl;
	}

	// Reset index into sortedIntersections_
	sortedI_ = -1;
}


// Searches for leaf with intersected elements. Return true if found; false
// otherwise. Sets currentLeaf_ and sortedIntersections_.
template <class Type>
bool tnbLib::octreeLine<Type>::getNextLeaf()
{
	do
	{
		// No current leaf. Find first one.
		// Note: search starts from top every time

		point start(leafExitPoint_);
		currentLeaf_ = tree_.findLeafLine(start, endPoint_, leafExitPoint_);

		if (!currentLeaf_)
		{
			// No leaf found. Give up.
			return false;
		}

		// Get intersections and sort.
		calcSortedIntersections();
	} while (sortedIntersections_.empty());

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template <class Type>
tnbLib::octreeLine<Type>::octreeLine
(
	const octree<Type>& tree,
	const point& startPoint,
	const point& endPoint
)
	:
	tree_(tree),
	startPoint_(startPoint),
	endPoint_(endPoint),
	realStartPoint_(startPoint),
	leafExitPoint_(startPoint_),
	currentLeaf_(NULL),
	sortedIntersections_(0),
	lastElem_(-1),
	sortedI_(-1)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template <class Type>
tnbLib::octreeLine<Type>::~octreeLine()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template <class Type>
bool tnbLib::octreeLine<Type>::getIntersection()
{
	// Go to next element in sortedIntersections

	sortedI_++;

	if (sortedI_ >= sortedIntersections_.size())
	{
		// Past all sortedIntersections in current leaf. Go to next one.
		if (!getNextLeaf())
		{
			// No valid leaf found
			return false;
		}
		sortedI_ = 0;
	}

	return true;
}

// ************************************************************************* //
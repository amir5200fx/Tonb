#include <octreeDataPointTreeLeaf.hxx>

#include <treeLeaf.hxx>
#include <octreeDataPoint.hxx>

// * * * * * * * * * * * * * Template Specialisations  * * * * * * * * * * * //

template<>
tnbLib::label tnbLib::treeLeaf<tnbLib::octreeDataPoint>::find
(
	const octreeDataPoint& shapes,
	const point& sample
) const
{
	notImplemented
	(
		"tnbLib::treeLeaf<tnbLib::octreeDataPoint>::find("
		"const octreeDataPoint& shapes,"
		"const point& sample"
	);

	return false;
}


template<>
bool tnbLib::treeLeaf<tnbLib::octreeDataPoint>::findNearest
(
	const octreeDataPoint& shapes,
	const point& sample,
	treeBoundBox& tightest,
	label& tightestI,
	scalar& tightestDist
) const
{
	// Some aliases
	const pointField& points = shapes.points();
	point& tMin = tightest.min();
	point& tMax = tightest.max();

	scalar minDist2 = sqr(tightestDist);

	label minIndex = -1;
	forAll(indices_, i)
	{
		label pointi = indices_[i];
		scalar dist = magSqr(points[pointi] - sample);

		if (dist < minDist2)
		{
			minDist2 = dist;
			minIndex = pointi;
		}
	}

	if (minIndex != -1)
	{
		tightestDist = sqrt(minDist2);

		// New nearer. Update 'tightest' bounding box
		tMin.x() = sample.x() - tightestDist;
		tMin.y() = sample.y() - tightestDist;
		tMin.z() = sample.z() - tightestDist;

		tMax.x() = sample.x() + tightestDist;
		tMax.y() = sample.y() + tightestDist;
		tMax.z() = sample.z() + tightestDist;

		tightestI = minIndex;

		return true;
	}
	else
	{
		// New no nearer so nothing changed
		return false;
	}
}


// ************************************************************************* //
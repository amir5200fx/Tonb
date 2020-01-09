#include <treeDataPoint.hxx>

#include <treeBoundBox.hxx>
#include <indexedOctree.hxx>
#include <polyMesh.hxx>
#include <triangleFuncs.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::treeDataPoint, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::treeDataPoint::treeDataPoint(const pointField& points)
	:
	points_(points)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::pointField tnbLib::treeDataPoint::points() const
{
	return points_;
}


//- Get type (inside,outside,mixed,unknown) of point w.r.t. surface.
//  Only makes sense for closed surfaces.
tnbLib::label tnbLib::treeDataPoint::getVolumeType
(
	const indexedOctree<treeDataPoint>& oc,
	const point& sample
) const
{
	return indexedOctree<treeDataPoint>::UNKNOWN;
}


// Check if any point on shape is inside cubeBb.
bool tnbLib::treeDataPoint::overlaps
(
	const label index,
	const treeBoundBox& cubeBb
) const
{
	return cubeBb.contains(points_[index]);
}


// Calculate nearest point to sample. Updates (if any) nearestDistSqr,
//  minIndex, nearestPoint.
void tnbLib::treeDataPoint::findNearest
(
	const labelList& indices,
	const point& sample,

	scalar& nearestDistSqr,
	label& minIndex,
	point& nearestPoint
) const
{
	forAll(indices, i)
	{
		label index = indices[i];

		const point& pt = points_[index];

		scalar distSqr = magSqr(pt - sample);

		if (distSqr < nearestDistSqr)
		{
			nearestDistSqr = distSqr;
			minIndex = index;
			nearestPoint = pt;
		}
	}
}


//- Calculates nearest (to line) point in shape.
//  Returns point and distance (squared)
void tnbLib::treeDataPoint::findNearest
(
	const labelList& indices,
	const linePointRef& ln,

	treeBoundBox& tightest,
	label& minIndex,
	point& linePoint,
	point& nearestPoint
) const
{
	// Best so far
	scalar nearestDistSqr = magSqr(linePoint - nearestPoint);

	forAll(indices, i)
	{
		label index = indices[i];

		const point& shapePt = points_[index];

		if (tightest.contains(shapePt))
		{
			// Nearest point on line
			pointHit pHit = ln.nearestDist(shapePt);
			scalar distSqr = sqr(pHit.distance());

			if (distSqr < nearestDistSqr)
			{
				nearestDistSqr = distSqr;
				minIndex = index;
				linePoint = pHit.rawPoint();
				nearestPoint = shapePt;

				{
					point& minPt = tightest.min();
					minPt = min(ln.start(), ln.end());
					minPt.x() -= pHit.distance();
					minPt.y() -= pHit.distance();
					minPt.z() -= pHit.distance();
				}
				{
					point& maxPt = tightest.max();
					maxPt = max(ln.start(), ln.end());
					maxPt.x() += pHit.distance();
					maxPt.y() += pHit.distance();
					maxPt.z() += pHit.distance();
				}
			}
		}
	}
}


// ************************************************************************* //
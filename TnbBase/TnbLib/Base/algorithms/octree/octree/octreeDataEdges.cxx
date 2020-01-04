#include <octreeDataEdges.hxx>

#include <line.hxx>
#include <labelList.hxx>
#include <octree.hxx>
#include <linePointRef.hxx>
#include <pointHit.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::octreeDataEdges, 0);

tnbLib::scalar tnbLib::octreeDataEdges::tol = 1e-6;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from selected edges. Bounding box calculated.
tnbLib::octreeDataEdges::octreeDataEdges
(
	const edgeList& edges,
	const pointField& points,
	const labelList& edgeLabels
)
	:
	edges_(edges),
	points_(points),
	edgeLabels_(edgeLabels),
	allBb_(edgeLabels_.size())
{
	// Generate tight fitting bounding box
	forAll(edgeLabels_, i)
	{
		label edgeI = edgeLabels_[i];

		const edge& e = edges_[edgeI];

		const point& a = points_[e.start()];
		const point& b = points_[e.end()];

		allBb_[i].min() = min(a, b);
		allBb_[i].max() = max(a, b);
	}
}


// Construct as copy
tnbLib::octreeDataEdges::octreeDataEdges(const octreeDataEdges& shapes)
	:
	edges_(shapes.edges()),
	points_(shapes.points()),
	edgeLabels_(shapes.edgeLabels()),
	allBb_(shapes.allBb())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::octreeDataEdges::~octreeDataEdges()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::octreeDataEdges::getSampleType
(
	const octree<octreeDataEdges>&,
	const point&
) const
{
	return octree<octreeDataEdges>::UNKNOWN;
}


bool tnbLib::octreeDataEdges::overlaps
(
	const label index,
	const treeBoundBox& sampleBb
) const
{
	return sampleBb.overlaps(allBb_[index]);
}


bool tnbLib::octreeDataEdges::contains
(
	const label,
	const point&
) const
{
	notImplemented
	(
		"octreeDataEdges::contains(const label, const point&)"
	);
	return false;
}


bool tnbLib::octreeDataEdges::intersects
(
	const label,
	const point&,
	const point&,
	point&
) const
{
	notImplemented
	(
		"octreeDataEdges::intersects(const label, const point&"
		", const point&, point&)"
	);
	return false;
}


bool tnbLib::octreeDataEdges::findTightest
(
	const label index,
	const point& sample,
	treeBoundBox& tightest
) const
{
	// Get nearest and furthest away vertex
	point myNear, myFar;
	allBb_[index].calcExtremities(sample, myNear, myFar);

	const point dist = myFar - sample;
	scalar myFarDist = mag(dist);

	point tightestNear, tightestFar;
	tightest.calcExtremities(sample, tightestNear, tightestFar);

	scalar tightestFarDist = mag(tightestFar - sample);

	if (tightestFarDist < myFarDist)
	{
		// Keep current tightest.
		return false;
	}
	else
	{
		// Construct bb around sample and myFar
		const point dist2(fabs(dist.x()), fabs(dist.y()), fabs(dist.z()));

		tightest.min() = sample - dist2;
		tightest.max() = sample + dist2;

		return true;
	}
}


// Determine numerical value of sign of sample compared to shape at index
tnbLib::scalar tnbLib::octreeDataEdges::calcSign
(
	const label,
	const point&,
	point& n
) const
{
	n = vector::zero;

	return 1;
}


// Calculate nearest point on/in shapei
tnbLib::scalar tnbLib::octreeDataEdges::calcNearest
(
	const label index,
	const point& sample,
	point& nearest
) const
{
	const edge& e = edges_[edgeLabels_[index]];

	pointHit nearHit = e.line(points_).nearestDist(sample);

	nearest = nearHit.rawPoint();

	return nearHit.distance();
}


// Calculate nearest point on/in shapei
tnbLib::scalar tnbLib::octreeDataEdges::calcNearest
(
	const label index,
	const linePointRef& sampleLine,
	point& sampleLinePt,
	point& shapePt
) const
{
	const edge& e = edges_[edgeLabels_[index]];

	linePointRef edgeLine(e.line(points_));

	return edgeLine.nearestDist(sampleLine, shapePt, sampleLinePt);
}


void tnbLib::octreeDataEdges::write
(
	Ostream& os,
	const label index
) const
{
	os << edgeLabels_[index] << " " << allBb_[index];
}


// ************************************************************************* //
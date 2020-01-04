#include <octreeDataBoundBox.hxx>

#include <labelList.hxx>
#include <polyMesh.hxx>
#include <octree.hxx>
#include <polyPatch.hxx>
#include <triangleFuncs.hxx>
#include <linePointRef.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::octreeDataBoundBox, 0);

const tnbLib::debug::tolerancesSwitch
tnbLib::octreeDataBoundBox::tol
(
	"octreeDataBoundBoxTol",
	1e-6
);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::octreeDataBoundBox::octreeDataBoundBox
(
	const treeBoundBoxList& bbL
)
	:
	allBb_(bbL)
{}


tnbLib::octreeDataBoundBox::octreeDataBoundBox(const octreeDataBoundBox& shapes)
	:
	allBb_(shapes.allBb())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::octreeDataBoundBox::~octreeDataBoundBox()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::octreeDataBoundBox::getSampleType
(
	const octree<octreeDataBoundBox>& oc,
	const point& sample
) const
{
	return octree<octreeDataBoundBox>::UNKNOWN;
}


bool tnbLib::octreeDataBoundBox::overlaps
(
	const label index,
	const treeBoundBox& sampleBb
) const
{
	return sampleBb.overlaps(allBb_[index]);
}


bool tnbLib::octreeDataBoundBox::contains(const label, const point&) const
{
	notImplemented
	(
		"octreeDataBoundBox::contains(const label, const point&)"
	);

	return false;
}


bool tnbLib::octreeDataBoundBox::intersects
(
	const label index,
	const point& start,
	const point& end,
	point& intersectionPoint
) const
{
	notImplemented
	(
		"octreeDataBoundBox::intersects(const label, const point&)"
	);
	return false;
}


bool tnbLib::octreeDataBoundBox::findTightest
(
	const label index,
	const point& sample,
	treeBoundBox& tightest
) const
{
	// Get furthest away vertex
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
tnbLib::scalar tnbLib::octreeDataBoundBox::calcSign
(
	const label index,
	const point& sample,
	point& n
) const
{
	n = vector::zero;

	return 1;
}


// Calculate nearest point on/in shapei
tnbLib::scalar tnbLib::octreeDataBoundBox::calcNearest
(
	const label index,
	const point& sample,
	point& nearest
) const
{
	notImplemented
	(
		"octreeDataBoundBox::calcNearest"
		"(const label index, const point& sample, point& nearest)"
	);

	return GREAT;
}


// Calculate nearest point on/in shapei
tnbLib::scalar tnbLib::octreeDataBoundBox::calcNearest
(
	const label index,
	const linePointRef& ln,
	point& linePt,
	point& shapePt
) const
{
	notImplemented
	(
		"octreeDataBoundBox::calcNearest"
		"(const label, const linePointRef&, point&, point&)"
	);
	return GREAT;
}


void tnbLib::octreeDataBoundBox::write(Ostream& os, const label index) const
{
	os << allBb_[index];
}


// ************************************************************************* //
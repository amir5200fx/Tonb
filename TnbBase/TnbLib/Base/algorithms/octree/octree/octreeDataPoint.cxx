#include <octreeDataPoint.hxx>

#include <labelList.hxx>
#include <treeBoundBox.hxx>
#include <octree.hxx>
#include <linePointRef.hxx>
#include <pointHit.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::octreeDataPoint::octreeDataPoint(const pointField& points)
	:
	points_(points)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

//- Get type of volume
tnbLib::label tnbLib::octreeDataPoint::getSampleType
(
	const octree<octreeDataPoint>&,
	const point&
) const
{
	return octree<octreeDataPoint>::UNKNOWN;
}


bool tnbLib::octreeDataPoint::overlaps
(
	const label index,
	const treeBoundBox& sampleBb
) const
{
	return sampleBb.contains(points_[index]);
}


bool tnbLib::octreeDataPoint::contains
(
	const label,
	const point&
) const
{
	notImplemented
	(
		"octreeDataPoint::contains(const label, const point&)"
	);

	return false;
}


bool tnbLib::octreeDataPoint::intersects
(
	const label,
	const point&,
	const point&,
	point&
) const
{
	notImplemented
	(
		"octreeDataPoint::intersects(const label, const point&,"
		"const point&, point&)"
	);

	return false;
}


bool tnbLib::octreeDataPoint::findTightest
(
	const label,
	const point&,
	treeBoundBox&
) const
{
	notImplemented
	(
		"octreeDataPoint::findTightest(const label, const point&,"
		"treeBoundBox&)"
	);

	return false;
}


tnbLib::scalar tnbLib::octreeDataPoint::calcSign
(
	const label,
	const point&,
	vector& n
) const
{
	n = vector::zero;

	return 1;
}


// Calculate nearest point on/in shapei
inline tnbLib::scalar tnbLib::octreeDataPoint::calcNearest
(
	const label index,
	const point& sample,
	point& nearest
) const
{
	nearest = points_[index];
	return magSqr(points_[index] - sample);
}


void tnbLib::octreeDataPoint::write
(
	Ostream& os,
	const label index
) const
{
	if ((index < 0) || (index > points().size()))
	{
		FatalErrorIn("octreeDataPoint::write(Ostream&, const label)")
			<< "Index " << index << " outside 0.." << points().size()
			<< abort(FatalError);
	}
	os << ' ' << points()[index];
}


// Calculate nearest point on/in shapei
tnbLib::scalar tnbLib::octreeDataPoint::calcNearest
(
	const label index,
	const linePointRef& ln,
	point& linePt,
	point& shapePt
) const
{
	// Nearest point on shape
	shapePt = points_[index];

	// Nearest point on line
	pointHit pHit = ln.nearestDist(shapePt);

	linePt = pHit.rawPoint();

	return pHit.distance();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::octreeDataPoint& ocPts
	)
{
	return os << ocPts.points();
}


// ************************************************************************* //
#include <octreeDataCell.hxx>

#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <treeNode.hxx>
#include <octree.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::octreeDataCell::octreeDataCell
(
	const polyMesh& mesh,
	const labelList& cellLabels,
	const treeBoundBoxList& bbs
)
	:
	mesh_(mesh),
	cellLabels_(cellLabels),
	bbs_(bbs)
{}


// Construct from mesh (assumes all cells)
tnbLib::octreeDataCell::octreeDataCell
(
	const polyMesh& mesh
)
	:
	mesh_(mesh),
	cellLabels_(mesh_.nCells()),
	bbs_
	(
		mesh_.nCells(),
		treeBoundBox::invertedBox
	)
{
	// Set one-one indexing
	for (label i = 0; i < mesh_.nCells(); i++)
	{
		cellLabels_[i] = i;
	}

	const pointField& points = mesh_.points();
	const faceList& faces = mesh_.faces();
	const cellList& cells = mesh_.cells();

	forAll(cells, celli)
	{
		const labelList& facesi = cells[celli];

		forAll(facesi, facei)
		{
			const labelList& pointsi = faces[facesi[facei]];

			forAll(pointsi, pointi)
			{
				const point& p = points[pointsi[pointi]];

				bbs_[celli].min() = min(bbs_[celli].min(), p);
				bbs_[celli].max() = max(bbs_[celli].max(), p);
			}
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::octreeDataCell::getSampleType
(
	octree<octreeDataCell>&,
	const point&
) const
{
	return octree<octreeDataCell>::UNKNOWN;
}


bool tnbLib::octreeDataCell::overlaps
(
	const label index,
	const treeBoundBox& cubeBb
) const
{
	return cubeBb.overlaps(bbs_[index]);
}


bool tnbLib::octreeDataCell::contains
(
	const label index,
	const point& sample
) const
{
	return mesh_.pointInCell(sample, cellLabels_[index]);
}


bool tnbLib::octreeDataCell::intersects
(
	const label,
	const point&,
	const point&,
	point&
) const
{
	//Hack: don't know what to do here.

	notImplemented
	(
		"octreeDataCell::intersects(const label, const point&,"
		"const point&, point&)"
	);

	return false;
}


bool tnbLib::octreeDataCell::findTightest
(
	const label index,
	const point& sample,
	treeBoundBox& tightest
) const
{

	// get nearest and furthest away vertex
	point myNear, myFar;
	bbs_[index].calcExtremities(sample, myNear, myFar);

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
tnbLib::scalar tnbLib::octreeDataCell::calcSign
(
	const label,
	const point&,
	vector& n
) const
{
	n = vector::zero;

	return GREAT;
}


// Calculate nearest point on/in shapei
tnbLib::scalar tnbLib::octreeDataCell::calcNearest
(
	const label index,
	const point& sample,
	point& nearest
) const
{
	nearest = mesh_.cellCentres()[cellLabels_[index]];

	return mag(nearest - sample);
}


// Calculate nearest point on/in shapei
tnbLib::scalar tnbLib::octreeDataCell::calcNearest
(
	const label index,
	const linePointRef& ln,
	point& linePt,
	point& shapePt
) const
{
	notImplemented
	(
		"octreeDataCell::calcNearest(const label, const linePointRef&"
		", point& linePt, point&)"
	);
	return GREAT;
}


void tnbLib::octreeDataCell::write
(
	Ostream& os,
	const label index
) const
{
	os << cellLabels_[index] << " " << bbs_[index];
}


// ************************************************************************* //
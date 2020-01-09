#include <treeDataCell.hxx>

#include <indexedOctree.hxx>
#include <primitiveMesh.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::treeDataCell, 0);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::treeBoundBox tnbLib::treeDataCell::calcCellBb(const label cellI) const
{
	const cellList& cells = mesh_.cells();
	const faceList& faces = mesh_.faces();
	const pointField& points = mesh_.points();

	treeBoundBox cellBb
	(
		vector(GREAT, GREAT, GREAT),
		vector(-GREAT, -GREAT, -GREAT)
	);

	const cell& cFaces = cells[cellI];

	forAll(cFaces, cFaceI)
	{
		const face& f = faces[cFaces[cFaceI]];

		forAll(f, fp)
		{
			const point& p = points[f[fp]];

			cellBb.min() = min(cellBb.min(), p);
			cellBb.max() = max(cellBb.max(), p);
		}
	}
	return cellBb;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::treeDataCell::treeDataCell
(
	const bool cacheBb,
	const primitiveMesh& mesh,
	const labelList& cellLabels
)
	:
	mesh_(mesh),
	cellLabels_(cellLabels),
	cacheBb_(cacheBb)
{
	if (cacheBb_)
	{
		bbs_.setSize(cellLabels_.size());

		forAll(cellLabels_, i)
		{
			bbs_[i] = calcCellBb(cellLabels_[i]);
		}
	}
}


tnbLib::treeDataCell::treeDataCell
(
	const bool cacheBb,
	const primitiveMesh& mesh
)
	:
	mesh_(mesh),
	cellLabels_(identity(mesh_.nCells())),
	cacheBb_(cacheBb)
{
	if (cacheBb_)
	{
		bbs_.setSize(cellLabels_.size());

		forAll(cellLabels_, i)
		{
			bbs_[i] = calcCellBb(cellLabels_[i]);
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::pointField tnbLib::treeDataCell::points() const
{
	pointField cc(cellLabels_.size());

	forAll(cellLabels_, i)
	{
		cc[i] = mesh_.cellCentres()[cellLabels_[i]];
	}

	return cc;
}


// Check if any point on shape is inside cubeBb.
bool tnbLib::treeDataCell::overlaps
(
	const label index,
	const treeBoundBox& cubeBb
) const
{
	if (cacheBb_)
	{
		return cubeBb.overlaps(bbs_[index]);
	}
	else
	{
		return cubeBb.overlaps(calcCellBb(cellLabels_[index]));
	}
}


// Calculate nearest point to sample. Updates (if any) nearestDistSqr, minIndex,
// nearestPoint.
void tnbLib::treeDataCell::findNearest
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
		label cellI = cellLabels_[index];
		scalar distSqr = magSqr(sample - mesh_.cellCentres()[cellI]);

		if (distSqr < nearestDistSqr)
		{
			nearestDistSqr = distSqr;
			minIndex = index;
			nearestPoint = mesh_.cellCentres()[cellI];
		}
	}
}


bool tnbLib::treeDataCell::intersects
(
	const label index,
	const point& start,
	const point& end,
	point& intersectionPoint
) const
{
	// Do quick rejection test
	if (cacheBb_)
	{
		const treeBoundBox& cellBb = bbs_[index];

		if ((cellBb.posBits(start) & cellBb.posBits(end)) != 0)
		{
			// start and end in same block outside of cellBb.
			return false;
		}
	}
	else
	{
		const treeBoundBox cellBb = calcCellBb(cellLabels_[index]);

		if ((cellBb.posBits(start) & cellBb.posBits(end)) != 0)
		{
			// start and end in same block outside of cellBb.
			return false;
		}
	}


	// Do intersection with all faces of cell
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Disable picking up intersections behind us.
	scalar oldTol = intersection::setPlanarTol(0.0);

	const cell& cFaces = mesh_.cells()[cellLabels_[index]];

	const vector dir(end - start);
	scalar minDistSqr = magSqr(dir);
	bool hasMin = false;

	forAll(cFaces, i)
	{
		const face& f = mesh_.faces()[cFaces[i]];

		pointHit inter = f.ray
		(
			start,
			dir,
			mesh_.points(),
			intersection::HALF_RAY
		);

		if (inter.hit() && sqr(inter.distance()) <= minDistSqr)
		{
			// Note: no extra test on whether intersection is in front of us
			// since using half_ray AND zero tolerance. (note that tolerance
			// is used to look behind us)
			minDistSqr = sqr(inter.distance());
			intersectionPoint = inter.hitPoint();
			hasMin = true;
		}
	}

	// Restore picking tolerance
	intersection::setPlanarTol(oldTol);

	return hasMin;
}


// ************************************************************************* //
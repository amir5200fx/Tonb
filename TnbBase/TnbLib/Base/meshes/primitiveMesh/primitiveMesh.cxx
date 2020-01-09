#include <primitiveMesh.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::primitiveMesh, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::primitiveMesh::primitiveMesh()
	:
	nPoints_(0),
	nEdges_(-1),
	nInternalFaces_(0),
	nFaces_(0),
	nCells_(0),

	cellShapesPtr_(NULL),
	edgesPtr_(NULL),
	ccPtr_(NULL),
	ecPtr_(NULL),
	pcPtr_(NULL),

	cfPtr_(NULL),
	efPtr_(NULL),
	pfPtr_(NULL),

	cePtr_(NULL),
	fePtr_(NULL),
	pePtr_(NULL),
	ppPtr_(NULL),
	cpPtr_(NULL),

	labels_(0),

	cellCentresPtr_(NULL),
	faceCentresPtr_(NULL),
	cellVolumesPtr_(NULL),
	faceAreasPtr_(NULL)
{}


// Construct from components
// WARNING: ASSUMES CORRECT ORDERING OF DATA.
tnbLib::primitiveMesh::primitiveMesh
(
	const label nPoints,
	const label nInternalFaces,
	const label nFaces,
	const label nCells
)
	:
	nPoints_(nPoints),
	nEdges_(-1),
	nInternalFaces_(nInternalFaces),
	nFaces_(nFaces),
	nCells_(nCells),

	cellShapesPtr_(NULL),
	edgesPtr_(NULL),
	ccPtr_(NULL),
	ecPtr_(NULL),
	pcPtr_(NULL),

	cfPtr_(NULL),
	efPtr_(NULL),
	pfPtr_(NULL),

	cePtr_(NULL),
	fePtr_(NULL),
	pePtr_(NULL),
	ppPtr_(NULL),
	cpPtr_(NULL),

	labels_(0),

	cellCentresPtr_(NULL),
	faceCentresPtr_(NULL),
	cellVolumesPtr_(NULL),
	faceAreasPtr_(NULL)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::primitiveMesh::~primitiveMesh()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::primitiveMesh::reset
(
	const label nPoints,
	const label nInternalFaces,
	const label nFaces,
	const label nCells
)
{
	clearOut();

	nPoints_ = nPoints;
	nEdges_ = -1;

	nInternalFaces_ = nInternalFaces;
	nFaces_ = nFaces;
	nCells_ = nCells;

	if (debug)
	{
		Pout << "primitiveMesh::reset : mesh reset to"
			<< " nPoints:" << nPoints_
			<< " nEdges:" << nEdges_
			<< " nInternalFaces:" << nInternalFaces_
			<< " nFaces:" << nFaces_
			<< " nCells:" << nCells_
			<< endl;
	}
}


void tnbLib::primitiveMesh::reset
(
	const label nPoints,
	const label nInternalFaces,
	const label nFaces,
	const label nCells,
	cellList& clst
)
{
	reset
	(
		nPoints,
		nInternalFaces,
		nFaces,
		nCells
	);

	cfPtr_ = new cellList(clst, true);
}


void tnbLib::primitiveMesh::reset
(
	const label nPoints,
	const label nInternalFaces,
	const label nFaces,
	const label nCells,
	const Xfer<cellList>& clst
)
{
	reset
	(
		nPoints,
		nInternalFaces,
		nFaces,
		nCells
	);

	cfPtr_ = new cellList(clst);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::primitiveMesh::movePoints
(
	const pointField& newPoints,
	const pointField& oldPoints
)
{
	if (newPoints.size() < nPoints() || oldPoints.size() < nPoints())
	{
		FatalErrorIn
		(
			"primitiveMesh::movePoints(const pointField& newPoints, "
			"const pointField& oldPoints)"
		) << "Cannot move points: size of given point list smaller "
			<< "than the number of active points" << nl
			<< "newPoints: " << newPoints.size()
			<< " oldPoints: " << oldPoints.size()
			<< " nPoints(): " << nPoints() << nl
			<< abort(FatalError);
	}

	// Create swept volumes
	const faceList& f = faces();

	tmp<scalarField> tsweptVols(new scalarField(f.size()));
	scalarField& sweptVols = tsweptVols();

	forAll(f, faceI)
	{
		sweptVols[faceI] = f[faceI].sweptVol(oldPoints, newPoints);
	}

	// Force recalculation of all geometric data with new points
	clearGeom();

	return tsweptVols;
}


const tnbLib::cellShapeList& tnbLib::primitiveMesh::cellShapes() const
{
	if (!cellShapesPtr_)
	{
		calcCellShapes();
	}

	return *cellShapesPtr_;
}


// ************************************************************************* //
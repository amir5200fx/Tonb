#include <pointVolInterpolation.hxx>

#include <fvMesh.hxx>
#include <pointFields.hxx>
#include <volFields.hxx>
#include <emptyFvPatch.hxx>
#include <SubField.hxx>
#include <demandDrivenData.hxx>
#include <globalMeshData.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pointVolInterpolation, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::pointVolInterpolation::makeWeights() const
{
	if (volWeightsPtr_)
	{
		FatalErrorIn("pointVolInterpolation::makeWeights() const")
			<< "weighting factors already calculated"
			<< abort(FatalError);
	}

	if (debug)
	{
		Info << "pointVolInterpolation::makeWeights() : "
			<< "constructing weighting factors"
			<< endl;
	}

	const pointField& points = vMesh().points();
	const labelListList& cellPoints = vMesh().cellPoints();
	const vectorField& cellCentres = vMesh().cellCentres();

	// Allocate storage for weighting factors
	volWeightsPtr_ = new FieldField<Field, scalar>(cellCentres.size());
	FieldField<Field, scalar>& weightingFactors = *volWeightsPtr_;

	forAll(weightingFactors, pointi)
	{
		weightingFactors.set
		(
			pointi,
			new scalarField(cellPoints[pointi].size())
		);
	}


	// Calculate inverse distances between points and cell centres
	// and store in weighting factor array
	forAll(cellCentres, cellI)
	{
		const labelList& curCellPoints = cellPoints[cellI];

		forAll(curCellPoints, cellPointI)
		{
			weightingFactors[cellI][cellPointI] = 1.0 /
				mag
				(
					cellCentres[cellI] - points[curCellPoints[cellPointI]]
				);
		}
	}

	scalarField pointVolSumWeights(cellCentres.size(), 0);

	// Calculate weighting factors using inverse distance weighting
	forAll(cellCentres, cellI)
	{
		const labelList& curCellPoints = cellPoints[cellI];

		forAll(curCellPoints, cellPointI)
		{
			pointVolSumWeights[cellI] += weightingFactors[cellI][cellPointI];
		}
	}

	forAll(cellCentres, cellI)
	{
		const labelList& curCellPoints = cellPoints[cellI];

		forAll(curCellPoints, cellPointI)
		{
			weightingFactors[cellI][cellPointI] /= pointVolSumWeights[cellI];
		}
	}

	if (debug)
	{
		Info << "pointVolInterpolation::makeWeights() : "
			<< "finished constructing weighting factors"
			<< endl;
	}
}


// Do what is neccessary if the mesh has changed topology
void tnbLib::pointVolInterpolation::clearAddressing() const
{
	deleteDemandDrivenData(patchInterpolatorsPtr_);
}


// Do what is neccessary if the mesh has moved
void tnbLib::pointVolInterpolation::clearGeom() const
{
	deleteDemandDrivenData(volWeightsPtr_);
}


const tnbLib::PtrList<tnbLib::primitivePatchInterpolation>&
tnbLib::pointVolInterpolation::patchInterpolators() const
{
	if (!patchInterpolatorsPtr_)
	{
		const fvBoundaryMesh& bdry = vMesh().boundary();

		patchInterpolatorsPtr_ =
			new PtrList<primitivePatchInterpolation>(bdry.size());

		forAll(bdry, patchI)
		{
			patchInterpolatorsPtr_->set
			(
				patchI,
				new primitivePatchInterpolation(bdry[patchI].patch())
			);
		}
	}

	return *patchInterpolatorsPtr_;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

tnbLib::pointVolInterpolation::pointVolInterpolation
(
	const pointMesh& pm,
	const fvMesh& vm
)
	:
	pointMesh_(pm),
	fvMesh_(vm),
	volWeightsPtr_(NULL),
	patchInterpolatorsPtr_(NULL)
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::pointVolInterpolation::~pointVolInterpolation()
{
	clearAddressing();
	clearGeom();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Return point weights
const tnbLib::FieldField<tnbLib::Field, tnbLib::scalar>&
tnbLib::pointVolInterpolation::volWeights() const
{
	// If weighting factor array not present then construct
	if (!volWeightsPtr_)
	{
		makeWeights();
	}

	return *volWeightsPtr_;
}


// Do what is neccessary if the mesh has moved
void tnbLib::pointVolInterpolation::updateTopology()
{
	clearAddressing();
	clearGeom();
}


// Do what is neccessary if the mesh has moved
bool tnbLib::pointVolInterpolation::movePoints()
{
	clearGeom();

	return true;
}


// ************************************************************************* //
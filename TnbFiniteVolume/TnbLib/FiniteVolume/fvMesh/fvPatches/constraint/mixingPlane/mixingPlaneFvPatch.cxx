#include <mixingPlaneFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mixingPlaneFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, mixingPlaneFvPatch, polyPatch);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::mixingPlaneFvPatch::~mixingPlaneFvPatch()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

// Make patch weighting factors
void tnbLib::mixingPlaneFvPatch::makeWeights(scalarField& w) const
{
	// Calculation of weighting factors is performed from the master
	// position, using reconstructed shadow cell centres
	if (mixingPlanePolyPatch_.master())
	{
		vectorField n = nf();

		// Note: mag in the dot-product.
		// For all valid meshes, the non-orthogonality will be less than
		// 90 deg and the dot-product will be positive.  For invalid
		// meshes (d & s <= 0), this will stabilise the calculation
		// but the result will be poor.  HJ, 24/Aug/2011
		scalarField nfc =
			mag(n & (mixingPlanePolyPatch_.reconFaceCellCentres() - Cf()));

		w = nfc / (mag(n & (Cf() - Cn())) + nfc);
	}
	else
	{
		// Pick up weights from the master side
		scalarField masterWeights(shadow().size());
		shadow().makeWeights(masterWeights);

		scalarField oneMinusW = 1 - masterWeights;

		w = interpolate(oneMinusW);
	}
}


void tnbLib::mixingPlaneFvPatch::makeDeltaCoeffs(scalarField& dc) const
{
	if (mixingPlanePolyPatch_.master())
	{
		// Stabilised form for bad meshes.  HJ, 24/Aug/2011
		vectorField d = delta();

		dc = 1.0 / max(nf() & d, 0.05*mag(d));
	}
	else
	{
		scalarField masterDeltas(shadow().size());
		shadow().makeDeltaCoeffs(masterDeltas);
		dc = interpolate(masterDeltas);
	}
}


void tnbLib::mixingPlaneFvPatch::makeCorrVecs(vectorField& cv) const
{
	cv = vector::zero;
#if 0
	// Full non-orthogonality treatment

	// Calculate correction vectors on coupled patches
	const scalarField& patchDeltaCoeffs = deltaCoeffs();

	vectorField patchDeltas = delta();
	vectorField n = nf();
	cv = n - patchDeltas * patchDeltaCoeffs;
#endif
}


const tnbLib::mixingPlaneFvPatch& tnbLib::mixingPlaneFvPatch::shadow() const
{
	const fvPatch& p =
		this->boundaryMesh()[mixingPlanePolyPatch_.shadowIndex()];

	return refCast<const mixingPlaneFvPatch>(p);
}


// Return delta (P to N) vectors across coupled patch
tnbLib::tmp<tnbLib::vectorField> tnbLib::mixingPlaneFvPatch::delta() const
{
	if (mixingPlanePolyPatch_.master())
	{
		return mixingPlanePolyPatch_.reconFaceCellCentres() - Cn();
	}
	else
	{
		tmp<vectorField> tDelta = interpolate
		(
			shadow().Cn()
			- mixingPlanePolyPatch_.shadow().reconFaceCellCentres()
		);

		return tDelta;
	}
}


bool tnbLib::mixingPlaneFvPatch::master() const
{
	return mixingPlanePolyPatch_.master();
}


tnbLib::label tnbLib::mixingPlaneFvPatch::shadowIndex() const
{
	return mixingPlanePolyPatch_.shadowIndex();
}


const tnbLib::mixingPlaneLduInterface&
tnbLib::mixingPlaneFvPatch::shadowInterface() const
{
	const fvPatch& p =
		this->boundaryMesh()[mixingPlanePolyPatch_.shadowIndex()];

	return refCast<const mixingPlaneLduInterface>(p);
}


const tnbLib::labelListList& tnbLib::mixingPlaneFvPatch::addressing() const
{
	if (mixingPlanePolyPatch_.master())
	{
		return mixingPlanePolyPatch_.patchToPatch().masterPatchToProfileAddr();
	}
	else
	{
		return mixingPlanePolyPatch_.patchToPatch().slavePatchToProfileAddr();
	}
}


const tnbLib::scalarListList& tnbLib::mixingPlaneFvPatch::weights() const
{
	if (mixingPlanePolyPatch_.master())
	{
		return mixingPlanePolyPatch_.patchToPatch().
			masterPatchToProfileWeights();
	}
	else
	{
		return mixingPlanePolyPatch_.patchToPatch().
			slavePatchToProfileWeights();
	}
}


tnbLib::tmp<tnbLib::labelField> tnbLib::mixingPlaneFvPatch::interfaceInternalField
(
	const unallocLabelList& internalData
) const
{
	return patchInternalField(internalData);
}


void tnbLib::mixingPlaneFvPatch::initTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& interfaceData
) const
{
	labelTransferBuffer_ = interfaceData;
}


tnbLib::tmp<tnbLib::labelField> tnbLib::mixingPlaneFvPatch::transfer
(
	const Pstream::commsTypes,
	const unallocLabelList& interfaceData
) const
{
	return this->shadow().labelTransferBuffer();
}


void tnbLib::mixingPlaneFvPatch::initInternalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& iF
) const
{
	labelTransferBuffer_ = patchInternalField(iF);
}


tnbLib::tmp<tnbLib::labelField> tnbLib::mixingPlaneFvPatch::internalFieldTransfer
(
	const Pstream::commsTypes,
	const unallocLabelList& iF
) const
{
	return shadow().labelTransferBuffer();
}


// ************************************************************************* //
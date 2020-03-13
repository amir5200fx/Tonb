#include <ggiFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ggiFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, ggiFvPatch, polyPatch);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ggiFvPatch::~ggiFvPatch()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

// Make patch weighting factors
void tnbLib::ggiFvPatch::makeWeights(scalarField& w) const
{
	// Calculation of weighting factors is performed from the master
	// position, using reconstructed shadow cell centres
	// HJ, 2/Aug/2007
	if (ggiPolyPatch_.master())
	{
		vectorField n = nf();

		// Note: mag in the dot-product.
		// For all valid meshes, the non-orthogonality will be less than
		// 90 deg and the dot-product will be positive.  For invalid
		// meshes (d & s <= 0), this will stabilise the calculation
		// but the result will be poor.  HJ, 24/Aug/2011
		scalarField nfc =
			mag(n & (ggiPolyPatch_.reconFaceCellCentres() - Cf()));

		w = nfc / (mag(n & (Cf() - Cn())) + nfc);

		if (bridgeOverlap())
		{
			// Set overlap weights to 0.5 and use mirrored neighbour field
			// for interpolation.  HJ, 21/Jan/2009
			bridge(scalarField(size(), 0.5), w);
		}
	}
	else
	{
		// Pick up weights from the master side
		scalarField masterWeights(shadow().size());
		shadow().makeWeights(masterWeights);

		scalarField oneMinusW = 1 - masterWeights;

		w = interpolate(oneMinusW);

		if (bridgeOverlap())
		{
			// Set overlap weights to 0.5 and use mirrored neighbour field
			// for interpolation.  HJ, 21/Jan/2009
			bridge(scalarField(size(), 0.5), w);
		}
	}
}


// Make patch face - neighbour cell distances
void tnbLib::ggiFvPatch::makeDeltaCoeffs(scalarField& dc) const
{
	if (ggiPolyPatch_.master())
	{
		// Stabilised form for bad meshes.  HJ, 24/Aug/2011
		vectorField d = delta();

		dc = 1.0 / max(nf() & d, 0.05*mag(d));

		if (bridgeOverlap())
		{
			scalarField bridgeDeltas = nf() & fvPatch::delta();

			bridge(bridgeDeltas, dc);
		}
	}
	else
	{
		scalarField masterDeltas(shadow().size());
		shadow().makeDeltaCoeffs(masterDeltas);
		dc = interpolate(masterDeltas);

		if (bridgeOverlap())
		{
			scalarField bridgeDeltas = nf() & fvPatch::delta();

			bridge(bridgeDeltas, dc);
		}
	}
}


// Make patch face non-orthogonality correction vectors
void tnbLib::ggiFvPatch::makeCorrVecs(vectorField& cv) const
{
	// Non-orthogonality correction on a ggi interface
	// MB, 7/April/2009

	// Calculate correction vectors on coupled patches
	const scalarField& patchDeltaCoeffs = deltaCoeffs();

	vectorField patchDeltas = delta();
	vectorField n = nf();

	// If non-orthogonality is over 90 deg, kill correction vector
	// HJ, 6/Jan/2011
	cv = pos(patchDeltas & n)*(n - patchDeltas * patchDeltaCoeffs);
}


// Return delta (P to N) vectors across coupled patch
tnbLib::tmp<tnbLib::vectorField> tnbLib::ggiFvPatch::delta() const
{
	if (ggiPolyPatch_.master())
	{
		tmp<vectorField> tDelta = ggiPolyPatch_.reconFaceCellCentres() - Cn();

		if (bridgeOverlap())
		{
			vectorField bridgeDeltas = Cf() - Cn();

			bridge(bridgeDeltas, tDelta());
		}

		return tDelta;
	}
	else
	{
		tmp<vectorField> tDelta = interpolate
		(
			shadow().Cn() - ggiPolyPatch_.shadow().reconFaceCellCentres()
		);

		if (bridgeOverlap())
		{
			vectorField bridgeDeltas = Cf() - Cn();

			bridge(bridgeDeltas, tDelta());
		}

		return tDelta;
	}
}


const tnbLib::ggiFvPatch& tnbLib::ggiFvPatch::shadow() const
{
	const fvPatch& p = this->boundaryMesh()[ggiPolyPatch_.shadowIndex()];

	return refCast<const ggiFvPatch>(p);
}


bool tnbLib::ggiFvPatch::master() const
{
	return ggiPolyPatch_.master();
}


bool tnbLib::ggiFvPatch::fineLevel() const
{
	return true;
}


tnbLib::label tnbLib::ggiFvPatch::shadowIndex() const
{
	return ggiPolyPatch_.shadowIndex();
}


const tnbLib::ggiLduInterface& tnbLib::ggiFvPatch::shadowInterface() const
{
	const fvPatch& p = this->boundaryMesh()[ggiPolyPatch_.shadowIndex()];

	return refCast<const ggiLduInterface>(p);
}


tnbLib::label tnbLib::ggiFvPatch::interfaceSize() const
{
	return ggiPolyPatch_.size();
}


tnbLib::label tnbLib::ggiFvPatch::zoneSize() const
{
	return ggiPolyPatch_.zone().size();
}


const tnbLib::labelList& tnbLib::ggiFvPatch::zoneAddressing() const
{
	return ggiPolyPatch_.zoneAddressing();
}


const tnbLib::labelListList& tnbLib::ggiFvPatch::addressing() const
{
	if (ggiPolyPatch_.master())
	{
		return ggiPolyPatch_.patchToPatch().masterAddr();
	}
	else
	{
		return ggiPolyPatch_.patchToPatch().slaveAddr();
	}
}


bool tnbLib::ggiFvPatch::localParallel() const
{
	return ggiPolyPatch_.localParallel();
}


const tnbLib::scalarListList& tnbLib::ggiFvPatch::weights() const
{
	if (ggiPolyPatch_.master())
	{
		return ggiPolyPatch_.patchToPatch().masterWeights();
	}
	else
	{
		return ggiPolyPatch_.patchToPatch().slaveWeights();
	}
}


tnbLib::tmp<tnbLib::labelField> tnbLib::ggiFvPatch::interfaceInternalField
(
	const unallocLabelList& internalData
) const
{
	return patchInternalField(internalData);
}


void tnbLib::ggiFvPatch::initTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& interfaceData
) const
{
	labelTransferBuffer_ = interfaceData;
}


tnbLib::tmp<tnbLib::labelField> tnbLib::ggiFvPatch::transfer
(
	const Pstream::commsTypes,
	const unallocLabelList& interfaceData
) const
{
	return this->shadow().labelTransferBuffer();
}


void tnbLib::ggiFvPatch::initInternalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& iF
) const
{
	labelTransferBuffer_ = patchInternalField(iF);
}


tnbLib::tmp<tnbLib::labelField> tnbLib::ggiFvPatch::internalFieldTransfer
(
	const Pstream::commsTypes,
	const unallocLabelList& iF
) const
{
	return shadow().labelTransferBuffer();
}



// ************************************************************************* //
#include <regionCoupleFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvMesh.hxx>
#include <fvBoundaryMesh.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupleFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, regionCoupleFvPatch, polyPatch);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionCoupleFvPatch::~regionCoupleFvPatch()
{}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Make patch weighting factors
void tnbLib::regionCoupleFvPatch::makeWeights(scalarField& w) const
{
	if (rcPolyPatch_.coupled())
	{
		if (rcPolyPatch_.master())
		{
			vectorField n = nf();

			// Note: mag in the dot-product.
			// For all valid meshes, the non-orthogonality will be less than
			// 90 deg and the dot-product will be positive.  For invalid
			// meshes (d & s <= 0), this will stabilise the calculation
			// but the result will be poor.  HJ, 24/Aug/2011
			scalarField nfc =
				mag(n & (rcPolyPatch_.reconFaceCellCentres() - Cf()));

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
	else
	{
		fvPatch::makeWeights(w);
	}
}


// Make patch face - neighbour cell distances
void tnbLib::regionCoupleFvPatch::makeDeltaCoeffs(scalarField& dc) const
{
	if (rcPolyPatch_.coupled())
	{
		if (rcPolyPatch_.master())
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
	else
	{
		fvPatch::makeDeltaCoeffs(dc);
	}
}


// Make patch face non-orthogonality correction vectors
void tnbLib::regionCoupleFvPatch::makeCorrVecs(vectorField& cv) const
{
	if (rcPolyPatch_.coupled())
	{
		// Non-orthogonality correction in attached state identical to ggi
		// interface

		// Calculate correction vectors on coupled patches
		const scalarField& patchDeltaCoeffs = deltaCoeffs();

		vectorField patchDeltas = delta();
		vectorField n = nf();

		// If non-orthogonality is over 90 deg, kill correction vector
		// HJ, 6/Jan/2011
		cv = pos(patchDeltas & n)*(n - patchDeltas * patchDeltaCoeffs);
	}
	else
	{
		// No correction in detached state.  HJ, 26/Jul/2011
		cv = vector::zero;
	}
}


// Return delta (P to N) vectors across coupled patch
tnbLib::tmp<tnbLib::vectorField> tnbLib::regionCoupleFvPatch::delta() const
{
	if (rcPolyPatch_.coupled())
	{
		if (rcPolyPatch_.master())
		{
			tmp<vectorField> tDelta =
				rcPolyPatch_.reconFaceCellCentres() - Cn();

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
				shadow().Cn() - rcPolyPatch_.shadow().reconFaceCellCentres()
			);

			if (bridgeOverlap())
			{
				vectorField bridgeDeltas = Cf() - Cn();

				bridge(bridgeDeltas, tDelta());
			}

			return tDelta;
		}
	}
	else
	{
		return fvPatch::delta();
	}
}


bool tnbLib::regionCoupleFvPatch::coupled() const
{
	return rcPolyPatch_.coupled();
}


const tnbLib::fvMesh& tnbLib::regionCoupleFvPatch::shadowRegion() const
{
	return
		boundaryMesh().mesh().objectRegistry::parent().lookupObject<fvMesh>
		(
			rcPolyPatch_.shadowRegionName()
			);
}


const tnbLib::regionCoupleFvPatch& tnbLib::regionCoupleFvPatch::shadow() const
{
	const fvPatch& p =
		shadowRegion().boundary()[rcPolyPatch_.shadowIndex()];

	return refCast<const regionCoupleFvPatch>(p);
}


bool tnbLib::regionCoupleFvPatch::master() const
{
	return rcPolyPatch_.master();
}


bool tnbLib::regionCoupleFvPatch::fineLevel() const
{
	return true;
}


tnbLib::label tnbLib::regionCoupleFvPatch::shadowIndex() const
{
	return rcPolyPatch_.shadowIndex();
}


const tnbLib::ggiLduInterface&
tnbLib::regionCoupleFvPatch::shadowInterface() const
{
	const fvPatch& p =
		shadowRegion().boundary()[rcPolyPatch_.shadowIndex()];

	return refCast<const ggiLduInterface>(p);
}


tnbLib::label tnbLib::regionCoupleFvPatch::interfaceSize() const
{
	return rcPolyPatch_.size();
}


tnbLib::label tnbLib::regionCoupleFvPatch::zoneSize() const
{
	return rcPolyPatch_.zone().size();
}


const tnbLib::labelList& tnbLib::regionCoupleFvPatch::zoneAddressing() const
{
	return rcPolyPatch_.zoneAddressing();
}


const tnbLib::labelListList& tnbLib::regionCoupleFvPatch::addressing() const
{
	if (rcPolyPatch_.master())
	{
		return rcPolyPatch_.patchToPatch().masterAddr();
	}
	else
	{
		return rcPolyPatch_.patchToPatch().slaveAddr();
	}
}


bool tnbLib::regionCoupleFvPatch::localParallel() const
{
	return rcPolyPatch_.localParallel();
}


const tnbLib::scalarListList& tnbLib::regionCoupleFvPatch::weights() const
{
	if (rcPolyPatch_.master())
	{
		return rcPolyPatch_.patchToPatch().masterWeights();
	}
	else
	{
		return rcPolyPatch_.patchToPatch().slaveWeights();
	}
}


tnbLib::tmp<tnbLib::labelField> tnbLib::regionCoupleFvPatch::interfaceInternalField
(
	const unallocLabelList& internalData
) const
{
	return patchInternalField(internalData);
}


void tnbLib::regionCoupleFvPatch::initTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& interfaceData
) const
{
	labelTransferBuffer_ = interfaceData;
}


tnbLib::tmp<tnbLib::labelField> tnbLib::regionCoupleFvPatch::transfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& interfaceData
) const
{

	return shadow().labelTransferBuffer();
}


void tnbLib::regionCoupleFvPatch::initInternalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& iF
) const
{
	labelTransferBuffer_ = patchInternalField(iF);
}


tnbLib::tmp<tnbLib::labelField> tnbLib::regionCoupleFvPatch::internalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const unallocLabelList& iF
) const
{
	return shadow().labelTransferBuffer();
}


// ************************************************************************* //
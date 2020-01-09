#include <AMGInterface.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(AMGInterface, 0);
	defineRunTimeSelectionTable(AMGInterface, lduInterface);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::AMGInterface::combine(const AMGInterface& coarseGi)
{
	const labelList& coarseFra = coarseGi.restrictAddressing_;

	forAll(restrictAddressing_, ffi)
	{
		restrictAddressing_[ffi] = coarseFra[restrictAddressing_[ffi]];
	}

	faceCells_ = coarseGi.faceCells_;
}


tnbLib::tmp<tnbLib::labelField> tnbLib::AMGInterface::interfaceInternalField
(
	const unallocLabelList& internalData
) const
{
	return interfaceInternalField<label>(internalData);
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::AMGInterface::agglomerateCoeffs
(
	const scalarField& fineCoeffs
) const
{
	tmp<scalarField> tcoarseCoeffs(new scalarField(size(), 0.0));
	scalarField& coarseCoeffs = tcoarseCoeffs();

	// Added weights to account for non-integral matching
	forAll(restrictAddressing_, ffi)
	{
		coarseCoeffs[restrictAddressing_[ffi]] +=
			restrictWeights_[ffi] * fineCoeffs[fineAddressing_[ffi]];
	}

	return tcoarseCoeffs;
}


// ************************************************************************* //

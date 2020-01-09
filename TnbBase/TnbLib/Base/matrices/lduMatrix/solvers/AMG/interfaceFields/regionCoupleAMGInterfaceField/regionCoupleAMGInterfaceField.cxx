#include <regionCoupleAMGInterfaceField.hxx>

#include <lduMatrix.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <OSspecific.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupleAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		AMGInterfaceField,
		regionCoupleAMGInterfaceField,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionCoupleAMGInterfaceField::regionCoupleAMGInterfaceField
(
	const AMGInterface& AMGCp,
	const lduInterfaceField& fineInterface
)
	:
	ggiAMGInterfaceField(AMGCp, fineInterface),
	regionCoupleInterface_(refCast<const regionCoupleAMGInterface>(AMGCp))
{}


// * * * * * * * * * * * * * * * * Desstructor * * * * * * * * * * * * * * * //

tnbLib::regionCoupleAMGInterfaceField::~regionCoupleAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::regionCoupleAMGInterfaceField::initInterfaceMatrixUpdate
(
	const scalarField& psiInternal,
	scalarField& result,
	const lduMatrix& m,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes commsType,
	const bool switchToLhs
) const
{
	// This must have a reduce in it.  HJ, 15/May/2009
	if (regionCoupleInterface_.coupled())
	{
		ggiAMGInterfaceField::initInterfaceMatrixUpdate
		(
			psiInternal,
			result,
			m,
			coeffs,
			cmpt,
			commsType,
			switchToLhs
		);
	}
}


void tnbLib::regionCoupleAMGInterfaceField::updateInterfaceMatrix
(
	const scalarField& psiInternal,
	scalarField& result,
	const lduMatrix& m,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes commsType,
	const bool switchToLhs
) const
{
	// Get expanded data to zone size.  No global reduce allowed
	// HJ, 15/May/2009
	if (regionCoupleInterface_.coupled())
	{
		ggiAMGInterfaceField::updateInterfaceMatrix
		(
			psiInternal,
			result,
			m,
			coeffs,
			cmpt,
			commsType,
			switchToLhs
		);
	}
}


// ************************************************************************* //
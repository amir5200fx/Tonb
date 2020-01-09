#include <mixingPlaneAMGInterfaceField.hxx>

#include <lduMatrix.hxx>
#include <mixingPlaneLduInterfaceField.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <OSspecific.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mixingPlaneAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		AMGInterfaceField,
		mixingPlaneAMGInterfaceField,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mixingPlaneAMGInterfaceField::mixingPlaneAMGInterfaceField
(
	const AMGInterface& AMGCp,
	const lduInterfaceField& fineInterface
)
	:
	AMGInterfaceField(AMGCp, fineInterface),
	mixingPlaneInterface_(refCast<const mixingPlaneAMGInterface>(AMGCp)),
	doTransform_(false),
	rank_(0),
	transferBuffer_()
{
	const mixingPlaneLduInterfaceField& p =
		refCast<const mixingPlaneLduInterfaceField>(fineInterface);

	doTransform_ = p.doTransform();
	rank_ = p.rank();
}


// * * * * * * * * * * * * * * * * Desstructor * * * * * * * * * * * * * * * //

tnbLib::mixingPlaneAMGInterfaceField::~mixingPlaneAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mixingPlaneAMGInterfaceField::initInterfaceMatrixUpdate
(
	const scalarField& psiInternal,
	scalarField&,
	const lduMatrix&,
	const scalarField&,
	const direction,
	const Pstream::commsTypes commsType,
	const bool switchToLhs
) const
{
	mixingPlaneInterface_.initInternalFieldTransfer(commsType, psiInternal);
}


void tnbLib::mixingPlaneAMGInterfaceField::updateInterfaceMatrix
(
	const scalarField& psiInternal,
	scalarField& result,
	const lduMatrix&,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes commsType,
	const bool switchToLhs
) const
{
	scalarField pnf =
		mixingPlaneInterface_.internalFieldTransfer(commsType, psiInternal);
	transformCoupleField(pnf, cmpt);

	const unallocLabelList& faceCells = mixingPlaneInterface_.faceCells();

	if (switchToLhs)
	{
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] += coeffs[elemI] * pnf[elemI];
		}
	}
	else
	{
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
		}
	}
}


// ************************************************************************* //
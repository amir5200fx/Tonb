#include <processorAMGInterfaceField.hxx>

#include <lduMatrix.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		AMGInterfaceField,
		processorAMGInterfaceField,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::processorAMGInterfaceField::processorAMGInterfaceField
(
	const AMGInterface& AMGCp,
	const lduInterfaceField& fineInterfaceField
)
	:
	AMGInterfaceField(AMGCp, fineInterfaceField),
	procInterface_(refCast<const processorAMGInterface>(AMGCp)),
	doTransform_(false),
	rank_(0)
{
	const processorLduInterfaceField& p =
		refCast<const processorLduInterfaceField>(fineInterfaceField);

	doTransform_ = p.doTransform();
	rank_ = p.rank();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::processorAMGInterfaceField::~processorAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::processorAMGInterfaceField::initInterfaceMatrixUpdate
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
	procInterface_.compressedSend
	(
		commsType,
		procInterface_.interfaceInternalField(psiInternal)()
	);
}


void tnbLib::processorAMGInterfaceField::updateInterfaceMatrix
(
	const scalarField&,
	scalarField& result,
	const lduMatrix&,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes commsType,
	const bool switchToLhs
) const
{
	scalarField pnf
	(
		procInterface_.compressedReceive<scalar>(commsType, coeffs.size())
	);
	transformCoupleField(pnf, cmpt);

	const unallocLabelList& faceCells = procInterface_.faceCells();

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
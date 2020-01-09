#include <cyclicAMGInterfaceField.hxx>

#include <lduMatrix.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		AMGInterfaceField,
		cyclicAMGInterfaceField,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicAMGInterfaceField::cyclicAMGInterfaceField
(
	const AMGInterface& AMGCp,
	const lduInterfaceField& fineInterface
)
	:
	AMGInterfaceField(AMGCp, fineInterface),
	cyclicInterface_(refCast<const cyclicAMGInterface>(AMGCp)),
	doTransform_(false),
	rank_(0)
{
	const cyclicLduInterfaceField& p =
		refCast<const cyclicLduInterfaceField>(fineInterface);

	doTransform_ = p.doTransform();
	rank_ = p.rank();
}


// * * * * * * * * * * * * * * * * Desstructor * * * * * * * * * * * * * * * //

tnbLib::cyclicAMGInterfaceField::~cyclicAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cyclicAMGInterfaceField::updateInterfaceMatrix
(
	const scalarField& psiInternal,
	scalarField& result,
	const lduMatrix&,
	const scalarField& coeffs,
	const direction cmpt,
	const Pstream::commsTypes,
	const bool switchToLhs
) const
{
	scalarField pnf(size());

	label sizeby2 = size() / 2;

	const unallocLabelList& faceCells = cyclicInterface_.faceCells();

	for (label facei = 0; facei < sizeby2; facei++)
	{
		pnf[facei] = psiInternal[faceCells[facei + sizeby2]];
		pnf[facei + sizeby2] = psiInternal[faceCells[facei]];
	}

	transformCoupleField(pnf, cmpt);

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
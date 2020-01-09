#include <ggiAMGInterfaceField.hxx>

#include <lduMatrix.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <OSspecific.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ggiAMGInterfaceField, 0);
	addToRunTimeSelectionTable
	(
		AMGInterfaceField,
		ggiAMGInterfaceField,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::ggiAMGInterfaceField::ggiAMGInterfaceField
(
	const AMGInterface& AMGCp,
	const lduInterfaceField& fineInterface
)
	:
	AMGInterfaceField(AMGCp, fineInterface),
	ggiInterface_(refCast<const ggiAMGInterface>(AMGCp)),
	doTransform_(false),
	rank_(0)
{
	const ggiLduInterfaceField& p =
		refCast<const ggiLduInterfaceField>(fineInterface);

	doTransform_ = p.doTransform();
	rank_ = p.rank();
}


// * * * * * * * * * * * * * * * * Desstructor * * * * * * * * * * * * * * * //

tnbLib::ggiAMGInterfaceField::~ggiAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::ggiAMGInterfaceField::initInterfaceMatrixUpdate
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
	// This must have a reduce in it.  HJ, 15/May/2009
	ggiInterface_.initInternalFieldTransfer(commsType, psiInternal);
}


void tnbLib::ggiAMGInterfaceField::updateInterfaceMatrix
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
	// Get expanded data to zone size.  No global reduce allowed
	// HJ, 15/May/2009
	scalarField pnf =
		ggiInterface_.internalFieldTransfer(commsType, psiInternal);
	transformCoupleField(pnf, cmpt);

	const unallocLabelList& faceCells = ggiInterface_.faceCells();

	// New treatment.  HJ, 26/Jun/2011
	if (pnf.size() != faceCells.size())
	{
		FatalErrorIn("ggiAMGInterfaceField::updateInterfaceMatrix")
			<< "Error in interface update: incorrect size of zone fields" << nl
			<< "Field size = " << pnf.size()
			<< " Zone size = " << faceCells.size()
			<< abort(FatalError);
	}

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
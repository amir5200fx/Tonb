#include <ProcessorBlockAMGInterfaceField.hxx>

#include <processorLduInterfaceField.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::ProcessorBlockAMGInterfaceField<Type>::ProcessorBlockAMGInterfaceField
(
	const AMGInterface& AMGCp,
	const BlockLduInterfaceField<Type>& fineInterfaceField
)
	:
	BlockAMGInterfaceField<Type>(AMGCp, fineInterfaceField),
	procInterface_(refCast<const processorAMGInterface>(AMGCp)),
	doTransform_(false)
{
	// If the interface based on a patch this must be taken care specially of
	if (isA<ProcessorBlockLduInterfaceField<Type> >(fineInterfaceField))
	{
		const ProcessorBlockLduInterfaceField<Type>& p =
			refCast<const ProcessorBlockLduInterfaceField<Type> >
			(
				fineInterfaceField
				);

		doTransform_ = p.doTransform();
	}
	else if (isA<processorLduInterfaceField>(fineInterfaceField))
	{
		const processorLduInterfaceField& p =
			refCast<const processorLduInterfaceField >(fineInterfaceField);

		doTransform_ = p.doTransform();
	}
	else
	{
		FatalErrorIn("ProcessorBlockAMGInterfaceField<Type> Constructor")
			<< "fineInterface must be of processor type and either" << endl
			<< "    ProcessorBlockLduInterfaceField<Type> or " << endl
			<< "    processorFvPatchField<Type> " << endl
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::ProcessorBlockAMGInterfaceField<Type>::
~ProcessorBlockAMGInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::ProcessorBlockAMGInterfaceField<Type>::initInterfaceMatrixUpdate
(
	const Field<Type>& psiInternal,
	Field<Type>&,
	const BlockLduMatrix<Type>&,
	const CoeffField<Type>&,
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


template<class Type>
void tnbLib::ProcessorBlockAMGInterfaceField<Type>::updateInterfaceMatrix
(
	const Field<Type>& psiInternal,
	Field<Type>& result,
	const BlockLduMatrix<Type>&,
	const CoeffField<Type>& coeffs,
	const Pstream::commsTypes commsType,
	const bool switchToLhs
) const
{
	Field<Type> pnf
	(
		procInterface_.compressedReceive<Type>(commsType, this->size())
	);

	// Multiply neighbour field with coeffs and re-use pnf for result
	// of multiplication
	multiply(pnf, coeffs, pnf);

	const unallocLabelList& faceCells = procInterface_.faceCells();

	if (switchToLhs)
	{
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] += pnf[elemI];
		}
	}
	else
	{
		forAll(faceCells, elemI)
		{
			result[faceCells[elemI]] -= pnf[elemI];
		}
	}
}


// ************************************************************************* //
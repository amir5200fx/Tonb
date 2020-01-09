#include <BlockAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::BlockAMGInterfaceField<Type> >
tnbLib::BlockAMGInterfaceField<Type>::New
(
	const AMGInterface& AMGCp,
	const BlockLduInterfaceField<Type>& fineInterface
)
{
	word coupleType(fineInterface.interfaceFieldType());

	typename lduInterfaceConstructorTable::iterator cstrIter =
		lduInterfaceConstructorTablePtr_->find(coupleType);

	if (cstrIter == lduInterfaceConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"BlockAMGInterfaceField::New"
			"(const AMGInterface& AMGCp, "
			"const BlockLduInterfaceField<Type>& fineInterface)"
		) << "Unknown BlockAMGInterfaceField type " << coupleType << ".\n"
			<< "Valid BlockAMGInterfaceField types are :"
			<< lduInterfaceConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<BlockAMGInterfaceField<Type> >
		(
			cstrIter()
			(
				AMGCp,
				fineInterface
				)
			);
}


// ************************************************************************* //
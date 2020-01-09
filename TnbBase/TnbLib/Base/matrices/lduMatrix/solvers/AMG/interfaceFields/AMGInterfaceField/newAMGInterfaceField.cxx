#include <AMGInterfaceField.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::AMGInterfaceField> tnbLib::AMGInterfaceField::New
(
	const AMGInterface& AMGCp,
	const lduInterfaceField& fineInterface
)
{
	word coupleType(fineInterface.interfaceFieldType());

	lduInterfaceConstructorTable::iterator cstrIter =
		lduInterfaceConstructorTablePtr_->find(coupleType);

	if (cstrIter == lduInterfaceConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"AMGInterfaceField::New"
			"(const AMGInterface& AMGCp, "
			"const lduInterfaceField& fineInterface)"
		) << "Unknown AMGInterfaceField type " << coupleType << ".\n"
			<< "Valid AMGInterfaceField types are :"
			<< lduInterfaceConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<AMGInterfaceField>(cstrIter()(AMGCp, fineInterface));
}


// ************************************************************************* //
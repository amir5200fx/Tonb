#include <AMGInterface.hxx>

#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::AMGInterface> tnbLib::AMGInterface::New
(
	const lduPrimitiveMesh& lduMesh,
	const lduInterface& fineInterface,
	const labelField& localRestrictAddressing,
	const labelField& neighbourRestrictAddressing
)
{
	word coupleType(fineInterface.type());

	lduInterfaceConstructorTable::iterator cstrIter =
		lduInterfaceConstructorTablePtr_->find(coupleType);

	if (cstrIter == lduInterfaceConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"AMGInterface::New"
			"(const lduPrimitiveMesh& lduMesh,"
			"const lduInterface& fineInterface,"
			"const labelField& localRestrictAddressing,"
			"const labelField& neighbourRestrictAddressing)"
		) << "Unknown AMGInterface type " << coupleType << ".\n"
			<< "Valid AMGInterface types are :"
			<< lduInterfaceConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<AMGInterface>
		(
			cstrIter()
			(
				lduMesh,
				fineInterface,
				localRestrictAddressing,
				neighbourRestrictAddressing
				)
			);
}


// ************************************************************************* //
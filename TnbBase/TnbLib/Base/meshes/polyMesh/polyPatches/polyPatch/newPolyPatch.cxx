#include <polyPatch.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::polyPatch> tnbLib::polyPatch::New
(
	const word& patchType,
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm
)
{
	if (debug)
	{
		Info << "polyPatch::New(const word&, const word&, const label, "
			"const label, const label, const polyBoundaryMesh&) : "
			"constructing polyPatch"
			<< endl;
	}

	wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(patchType);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"polyPatch::New(const word&, const word&, const label, "
			"const label, const label, const polyBoundaryMesh&) "
		) << "Unknown polyPatch type " << patchType << " for patch " << name
			<< endl << endl
			<< "Valid polyPatch types are :" << endl
			<< wordConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<polyPatch>(cstrIter()(name, size, start, index, bm));
}


tnbLib::autoPtr<tnbLib::polyPatch> tnbLib::polyPatch::New
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm
)
{
	if (debug)
	{
		Info << "polyPatch::New(const word&, const dictionary&, const label, "
			"const polyBoundaryMesh&) : constructing polyPatch"
			<< endl;
	}

	word patchType(dict.lookup("type"));

	dict.readIfPresent("geometricType", patchType);

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(patchType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		if (!disallowGenericPolyPatch)
		{
			cstrIter = dictionaryConstructorTablePtr_->find("genericPatch");
		}

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"polyPatch::New(const word&, const dictionary&, "
				"const label, const polyBoundaryMesh&)",
				dict
			) << "Unknown polyPatch type " << patchType
				<< " for patch " << name
				<< endl << endl
				<< "Valid polyPatch types are :" << endl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}
	}

	return autoPtr<polyPatch>(cstrIter()(name, dict, index, bm));
}


// ************************************************************************* //
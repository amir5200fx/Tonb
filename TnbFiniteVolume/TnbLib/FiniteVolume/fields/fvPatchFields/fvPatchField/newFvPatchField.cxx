#include <fvPatchField.hxx>

#include <IOobject.hxx>
#include <dictionary.hxx>
#include <fvMesh.hxx>
#include <fvPatchFieldMapper.hxx>
#include <GeometricField.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type> > tnbLib::fvPatchField<Type>::New
(
	const word& patchFieldType,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
{
	if (debug)
	{
		Info << "fvPatchField<Type>::New(const word&, const fvPatch&, "
			"const DimensionedField<Type, volMesh>&) : patchFieldType="
			<< patchFieldType
			<< endl;
	}

	typename patchConstructorTable::iterator cstrIter =
		patchConstructorTablePtr_->find(patchFieldType);

	if (cstrIter == patchConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"fvPatchField<Type>::New(const word&, const fvPatch&, "
			"const DimensionedField<Type, volMesh>&)"
		) << "Unknown patch field type " << patchFieldType
			<< " for field " << iF.name() << " on patch " << p.name()
			<< nl << nl
			<< "Valid patchField types are :" << endl
			<< patchConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	typename patchConstructorTable::iterator patchTypeCstrIter =
		patchConstructorTablePtr_->find(p.type());

	if (patchTypeCstrIter != patchConstructorTablePtr_->end())
	{
		return patchTypeCstrIter()(p, iF);
	}
	else
	{
		return cstrIter()(p, iF);
	}
}


template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type> > tnbLib::fvPatchField<Type>::New
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
{
	word patchFieldType(dict.lookup("type"));

	if (debug)
	{
		Info << "fvPatchField<Type>::New(const fvPatch&, "
			"const DimensionedField<Type, volMesh>&, "
			"const dictionary&) : patchFieldType = " << patchFieldType
			<< endl;
	}

	typename dictionaryConstructorTable::iterator cstrIter
		= dictionaryConstructorTablePtr_->find(patchFieldType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		if (!disallowGenericFvPatchField)
		{
			cstrIter = dictionaryConstructorTablePtr_->find("generic");
		}

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"fvPatchField<Type>::New(const fvPatch&, "
				"const DimensionedField<Type, volMesh>&, "
				"const dictionary&)",
				dict
			) << "Unknown patch field type " << patchFieldType
				<< " for field " << iF.name() << " on patch " << p.name()
				<< " for patch type " << p.type() << endl << endl
				<< "Valid patch field types are :" << endl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}
	}

	if
		(
			!dict.found("patchType")
			|| word(dict.lookup("patchType")) != p.type()
			)
	{
		typename dictionaryConstructorTable::iterator patchTypeCstrIter
			= dictionaryConstructorTablePtr_->find(p.type());

		if
			(
				patchTypeCstrIter != dictionaryConstructorTablePtr_->end()
				&& patchTypeCstrIter() != cstrIter()
				)
		{
			FatalIOErrorIn
			(
				"fvPatchField<Type>::New(const fvPatch&, "
				"const DimensionedField<Type, volMesh>&, "
				"const dictionary&)",
				dict
			) << "Inconsistent patch and patchField types for field "
				<< iF.name() << " on patch " << p.name() << "\n"
				<< "    patch type " << p.type()
				<< " and patchField type " << patchFieldType
				<< exit(FatalIOError);
		}
	}

	return cstrIter()(p, iF, dict);
}


template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type> > tnbLib::fvPatchField<Type>::New
(
	const fvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& pfMapper
)
{
	if (debug)
	{
		Info << "fvPatchField<Type>::New(const fvPatchField<Type>&, "
			"const fvPatch&, const DimensionedField<Type, volMesh>&, "
			"const fvPatchFieldMapper&) : "
			"constructing fvPatchField<Type>"
			<< endl;
	}

	typename patchMapperConstructorTable::iterator cstrIter =
		patchMapperConstructorTablePtr_->find(ptf.type());

	if (cstrIter == patchMapperConstructorTablePtr_->end())
	{
		FatalErrorIn
		(
			"fvPatchField<Type>::New(const fvPatchField<Type>&, "
			"const fvPatch&, const DimensionedField<Type, volMesh>&, "
			"const fvPatchFieldMapper&)"
		) << "unknown patch field type " << ptf.type()
			<< " for field " << iF.name() << " on patch " << p.name()
			<< nl << nl
			<< "Valid patchField types are :" << endl
			<< patchMapperConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return cstrIter()(ptf, p, iF, pfMapper);
}


// ************************************************************************* //
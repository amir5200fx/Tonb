#include <overlapGgiFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	overlapGgiFvsPatchField<Type>::overlapGgiFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(p, iF),
		overlapGgiPatch_(refCast<const overlapGgiFvPatch>(p))
	{}


	template<class Type>
	overlapGgiFvsPatchField<Type>::overlapGgiFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		coupledFvsPatchField<Type>(p, iF, dict, true),
		overlapGgiPatch_(refCast<const overlapGgiFvPatch>(p))
	{
		if (!isType<overlapGgiFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"overlapGgiFvsPatchField<Type>::overlapGgiFvsPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, surfaceMesh>& iF,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not overlapGgi type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	overlapGgiFvsPatchField<Type>::overlapGgiFvsPatchField
	(
		const overlapGgiFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		coupledFvsPatchField<Type>(ptf, p, iF, mapper),
		overlapGgiPatch_(refCast<const overlapGgiFvPatch>(p))
	{
		if (!isType<overlapGgiFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"overlapGgiFvsPatchField<Type>::overlapGgiFvsPatchField\n"
				"(\n"
				"    const overlapGgiFvsPatchField<Type>& ptf,\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, surfaceMesh>& iF,\n"
				"    const fvPatchFieldMapper& mapper\n"
				")\n"
			) << "Field type does not correspond to patch type for patch "
				<< this->patch().index() << "." << endl
				<< "Field type: " << typeName << endl
				<< "Patch type: " << this->patch().type()
				<< exit(FatalError);
		}
	}


	template<class Type>
	overlapGgiFvsPatchField<Type>::overlapGgiFvsPatchField
	(
		const overlapGgiFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(ptf, iF),
		overlapGgiPatch_(refCast<const overlapGgiFvPatch>(ptf.patch()))
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
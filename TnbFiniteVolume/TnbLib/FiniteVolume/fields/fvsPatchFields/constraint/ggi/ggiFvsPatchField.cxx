#include <ggiFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	ggiFvsPatchField<Type>::ggiFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(p, iF),
		ggiPatch_(refCast<const ggiFvPatch>(p))
	{}


	template<class Type>
	ggiFvsPatchField<Type>::ggiFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		coupledFvsPatchField<Type>(p, iF, dict, true),
		ggiPatch_(refCast<const ggiFvPatch>(p))
	{
		if (!isType<ggiFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"ggiFvsPatchField<Type>::ggiFvsPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, surfaceMesh>& iF,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not ggi type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	ggiFvsPatchField<Type>::ggiFvsPatchField
	(
		const ggiFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		coupledFvsPatchField<Type>(ptf, p, iF, mapper),
		ggiPatch_(refCast<const ggiFvPatch>(p))
	{
		if (!isType<ggiFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"ggiFvsPatchField<Type>::ggiFvsPatchField\n"
				"(\n"
				"    const ggiFvsPatchField<Type>& ptf,\n"
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
	ggiFvsPatchField<Type>::ggiFvsPatchField
	(
		const ggiFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(ptf, iF),
		ggiPatch_(refCast<const ggiFvPatch>(ptf.patch()))
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
#include <cyclicGgiFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	cyclicGgiFvsPatchField<Type>::cyclicGgiFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(p, iF),
		cyclicGgiPatch_(refCast<const cyclicGgiFvPatch>(p))
	{}


	template<class Type>
	cyclicGgiFvsPatchField<Type>::cyclicGgiFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		coupledFvsPatchField<Type>(p, iF, dict, true),
		cyclicGgiPatch_(refCast<const cyclicGgiFvPatch>(p))
	{
		if (!isType<cyclicGgiFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"cyclicGgiFvsPatchField<Type>::cyclicGgiFvsPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, surfaceMesh>& iF,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not cyclicGgi type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	cyclicGgiFvsPatchField<Type>::cyclicGgiFvsPatchField
	(
		const cyclicGgiFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		coupledFvsPatchField<Type>(ptf, p, iF, mapper),
		cyclicGgiPatch_(refCast<const cyclicGgiFvPatch>(p))
	{
		if (!isType<cyclicGgiFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"cyclicGgiFvsPatchField<Type>::cyclicGgiFvsPatchField\n"
				"(\n"
				"    const cyclicGgiFvsPatchField<Type>& ptf,\n"
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
	cyclicGgiFvsPatchField<Type>::cyclicGgiFvsPatchField
	(
		const cyclicGgiFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(ptf, iF),
		cyclicGgiPatch_(refCast<const cyclicGgiFvPatch>(ptf.patch()))
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
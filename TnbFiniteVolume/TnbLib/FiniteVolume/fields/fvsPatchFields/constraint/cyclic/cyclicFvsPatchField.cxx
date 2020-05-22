#include <cyclicFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	cyclicFvsPatchField<Type>::cyclicFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(p, iF),
		cyclicPatch_(refCast<const cyclicFvPatch>(p))
	{}


	template<class Type>
	cyclicFvsPatchField<Type>::cyclicFvsPatchField
	(
		const cyclicFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		coupledFvsPatchField<Type>(ptf, p, iF, mapper),
		cyclicPatch_(refCast<const cyclicFvPatch>(p))
	{
		if (!isType<cyclicFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"cyclicFvsPatchField<Type>::cyclicFvsPatchField\n"
				"(\n"
				"    const cyclicFvsPatchField<Type>& ptf,\n"
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
	cyclicFvsPatchField<Type>::cyclicFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		coupledFvsPatchField<Type>(p, iF, dict),
		cyclicPatch_(refCast<const cyclicFvPatch>(p))
	{
		if (!isType<cyclicFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"cyclicFvsPatchField<Type>::cyclicFvsPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const Field<Type>& field,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not cyclic type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	cyclicFvsPatchField<Type>::cyclicFvsPatchField
	(
		const cyclicFvsPatchField<Type>& ptf
	)
		:
		coupledFvsPatchField<Type>(ptf),
		cyclicPatch_(ptf.cyclicPatch_)
	{}


	template<class Type>
	cyclicFvsPatchField<Type>::cyclicFvsPatchField
	(
		const cyclicFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(ptf, iF),
		cyclicPatch_(ptf.cyclicPatch_)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
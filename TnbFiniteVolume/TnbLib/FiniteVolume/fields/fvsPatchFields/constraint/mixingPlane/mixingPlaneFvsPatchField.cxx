#include <mixingPlaneFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	mixingPlaneFvsPatchField<Type>::mixingPlaneFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(p, iF),
		mixingPlanePatch_(refCast<const mixingPlaneFvPatch>(p))
	{}


	template<class Type>
	mixingPlaneFvsPatchField<Type>::mixingPlaneFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		coupledFvsPatchField<Type>(p, iF, dict, true),
		mixingPlanePatch_(refCast<const mixingPlaneFvPatch>(p))
	{
		if (!isType<mixingPlaneFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"mixingPlaneFvsPatchField<Type>::mixingPlaneFvsPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, surfaceMesh>& iF,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not mixingPlane type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	mixingPlaneFvsPatchField<Type>::mixingPlaneFvsPatchField
	(
		const mixingPlaneFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		coupledFvsPatchField<Type>(ptf, p, iF, mapper),
		mixingPlanePatch_(refCast<const mixingPlaneFvPatch>(p))
	{
		if (!isType<mixingPlaneFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"mixingPlaneFvsPatchField<Type>::mixingPlaneFvsPatchField\n"
				"(\n"
				"    const mixingPlaneFvsPatchField<Type>& ptf,\n"
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
	mixingPlaneFvsPatchField<Type>::mixingPlaneFvsPatchField
	(
		const mixingPlaneFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		coupledFvsPatchField<Type>(ptf, iF),
		mixingPlanePatch_(refCast<const mixingPlaneFvPatch>(ptf.patch()))
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
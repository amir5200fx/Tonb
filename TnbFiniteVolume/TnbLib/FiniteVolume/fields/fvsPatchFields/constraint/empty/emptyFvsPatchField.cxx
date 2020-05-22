#include <emptyFvsPatchField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	emptyFvsPatchField<Type>::emptyFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(p, iF, Field<Type>(0))
	{}


	template<class Type>
	emptyFvsPatchField<Type>::emptyFvsPatchField
	(
		const emptyFvsPatchField<Type>&,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper&
	)
		:
		fvsPatchField<Type>(p, iF, Field<Type>(0))
	{
		if (!isType<emptyFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"emptyFvsPatchField<Type>::emptyFvsPatchField\n"
				"(\n"
				"    const emptyFvsPatchField<Type>&,\n"
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
	emptyFvsPatchField<Type>::emptyFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		fvsPatchField<Type>(p, iF, Field<Type>(0))
	{
		if (!isType<emptyFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"emptyFvsPatchField<Type>::emptyFvsPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const Field<Type>& field,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not empty type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	emptyFvsPatchField<Type>::emptyFvsPatchField
	(
		const emptyFvsPatchField<Type>& ptf
	)
		:
		fvsPatchField<Type>
		(
			ptf.patch(),
			ptf.dimensionedInternalField(),
			Field<Type>(0)
			)
	{}


	template<class Type>
	emptyFvsPatchField<Type>::emptyFvsPatchField
	(
		const emptyFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(ptf.patch(), iF, Field<Type>(0))
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
#include <symmetryFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	symmetryFvPatchField<Type>::symmetryFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		basicSymmetryFvPatchField<Type>(p, iF)
	{}


	template<class Type>
	symmetryFvPatchField<Type>::symmetryFvPatchField
	(
		const symmetryFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		basicSymmetryFvPatchField<Type>(ptf, p, iF, mapper)
	{
		if (!isType<symmetryFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"symmetryFvPatchField<Type>::symmetryFvPatchField\n"
				"(\n"
				"    const symmetryFvPatchField<Type>& ptf,\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, volMesh>& iF,\n"
				"    const fvPatchFieldMapper& mapper\n"
				")\n"
			) << "\n    patch type '" << p.type()
				<< "' not constraint type '" << typeName << "'"
				<< "\n    for patch " << p.name()
				<< " of field " << this->dimensionedInternalField().name()
				<< " in file " << this->dimensionedInternalField().objectPath()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	symmetryFvPatchField<Type>::symmetryFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		basicSymmetryFvPatchField<Type>(p, iF, dict)
	{
		if (!isType<symmetryFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"symmetryFvPatchField<Type>::symmetryFvPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const Field<Type>& field,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "\n    patch type '" << p.type()
				<< "' not constraint type '" << typeName << "'"
				<< "\n    for patch " << p.name()
				<< " of field " << this->dimensionedInternalField().name()
				<< " in file " << this->dimensionedInternalField().objectPath()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	symmetryFvPatchField<Type>::symmetryFvPatchField
	(
		const symmetryFvPatchField<Type>& ptf
	)
		:
		basicSymmetryFvPatchField<Type>(ptf)
	{}


	template<class Type>
	symmetryFvPatchField<Type>::symmetryFvPatchField
	(
		const symmetryFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		basicSymmetryFvPatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //

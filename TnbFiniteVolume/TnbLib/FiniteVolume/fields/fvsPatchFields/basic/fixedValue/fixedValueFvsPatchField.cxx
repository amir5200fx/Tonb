#include <fixedValueFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(p, iF)
	{}


	template<class Type>
	fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
	(
		const fixedValueFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fvsPatchField<Type>(ptf, p, iF, mapper)
	{}


	template<class Type>
	fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		fvsPatchField<Type>(p, iF, Field<Type>("value", dict, p.size()))
	{}


	template<class Type>
	fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
	(
		const fixedValueFvsPatchField<Type>& ptf
	)
		:
		fvsPatchField<Type>(ptf)
	{}


	template<class Type>
	fixedValueFvsPatchField<Type>::fixedValueFvsPatchField
	(
		const fixedValueFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void fixedValueFvsPatchField<Type>::write(Ostream& os) const
	{
		fvsPatchField<Type>::write(os);
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
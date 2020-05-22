#include <coupledFvsPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	coupledFvsPatchField<Type>::coupledFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(p, iF)
	{}


	template<class Type>
	coupledFvsPatchField<Type>::coupledFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const Field<Type>& f
	)
		:
		fvsPatchField<Type>(p, iF, f)
	{}


	template<class Type>
	coupledFvsPatchField<Type>::coupledFvsPatchField
	(
		const coupledFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fvsPatchField<Type>(ptf, p, iF, mapper)
	{}


	template<class Type>
	coupledFvsPatchField<Type>::coupledFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict,
		const bool valueRequired
	)
		:
		fvsPatchField<Type>(p, iF, dict, valueRequired)
	{}


	template<class Type>
	coupledFvsPatchField<Type>::coupledFvsPatchField
	(
		const coupledFvsPatchField<Type>& ptf
	)
		:
		fvsPatchField<Type>(ptf)
	{}


	template<class Type>
	coupledFvsPatchField<Type>::coupledFvsPatchField
	(
		const coupledFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void coupledFvsPatchField<Type>::write(Ostream& os) const
	{
		fvsPatchField<Type>::write(os);
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
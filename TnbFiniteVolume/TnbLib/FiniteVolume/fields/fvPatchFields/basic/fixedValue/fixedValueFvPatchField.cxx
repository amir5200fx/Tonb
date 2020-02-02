#include <fixedValueFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	fixedValueFvPatchField<Type>::fixedValueFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fvPatchField<Type>(p, iF)
	{}


	template<class Type>
	fixedValueFvPatchField<Type>::fixedValueFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		fvPatchField<Type>(p, iF, dict, true)
	{}


	template<class Type>
	fixedValueFvPatchField<Type>::fixedValueFvPatchField
	(
		const fixedValueFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fvPatchField<Type>(ptf, p, iF, mapper)
	{}


	template<class Type>
	fixedValueFvPatchField<Type>::fixedValueFvPatchField
	(
		const fixedValueFvPatchField<Type>& ptf
	)
		:
		fvPatchField<Type>(ptf)
	{}


	template<class Type>
	fixedValueFvPatchField<Type>::fixedValueFvPatchField
	(
		const fixedValueFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fvPatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	tmp<Field<Type> > fixedValueFvPatchField<Type>::valueInternalCoeffs
	(
		const tmp<scalarField>&
	) const
	{
		return tmp<Field<Type> >
			(
				new Field<Type>(this->size(), pTraits<Type>::zero)
				);
	}


	template<class Type>
	tmp<Field<Type> > fixedValueFvPatchField<Type>::valueBoundaryCoeffs
	(
		const tmp<scalarField>&
	) const
	{
		return *this;
	}


	template<class Type>
	tmp<Field<Type> > fixedValueFvPatchField<Type>::gradientInternalCoeffs() const
	{
		return -pTraits<Type>::one*this->patch().deltaCoeffs();
	}


	template<class Type>
	tmp<Field<Type> > fixedValueFvPatchField<Type>::gradientBoundaryCoeffs() const
	{
		return this->patch().deltaCoeffs()*(*this);
	}


	template<class Type>
	void fixedValueFvPatchField<Type>::write(Ostream& os) const
	{
		fvPatchField<Type>::write(os);
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
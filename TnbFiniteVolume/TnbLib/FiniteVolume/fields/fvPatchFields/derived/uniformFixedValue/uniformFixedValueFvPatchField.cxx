#include <uniformFixedValueFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fixedValueFvPatchField<Type>(p, iF),
		uniformValue_(pTraits<Type>::zero)
	{}


	template<class Type>
	uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
	(
		const uniformFixedValueFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper&
	)
		:
		fixedValueFvPatchField<Type>(p, iF),
		uniformValue_(ptf.uniformValue_)
	{
		fvPatchField<Type>::operator==(uniformValue_);
	}


	template<class Type>
	uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		fixedValueFvPatchField<Type>(p, iF),
		uniformValue_(pTraits<Type>(dict.lookup("uniformValue")))
	{
		fvPatchField<Type>::operator==(uniformValue_);
	}


	template<class Type>
	uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
	(
		const uniformFixedValueFvPatchField<Type>& ptf
	)
		:
		fixedValueFvPatchField<Type>(ptf),
		uniformValue_(ptf.uniformValue_)
	{
		fvPatchField<Type>::operator==(uniformValue_);
	}


	template<class Type>
	uniformFixedValueFvPatchField<Type>::uniformFixedValueFvPatchField
	(
		const uniformFixedValueFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fixedValueFvPatchField<Type>(ptf, iF),
		uniformValue_(ptf.uniformValue_)
	{
		fvPatchField<Type>::operator==(uniformValue_);
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void uniformFixedValueFvPatchField<Type>::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		this->setSize(m.size());
		fvPatchField<Type>::operator==(uniformValue_);
	}


	template<class Type>
	void uniformFixedValueFvPatchField<Type>::write(Ostream& os) const
	{
		fvPatchField<Type>::write(os);
		os.writeKeyword("uniformValue")
			<< uniformValue_ << token::END_STATEMENT << nl;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
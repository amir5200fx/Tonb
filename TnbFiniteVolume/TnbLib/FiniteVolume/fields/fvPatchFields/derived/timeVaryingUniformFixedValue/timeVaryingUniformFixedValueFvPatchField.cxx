#include <timeVaryingUniformFixedValueFvPatchField.hxx>

#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::timeVaryingUniformFixedValueFvPatchField<Type>::
timeVaryingUniformFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	timeSeries_()
{}


template<class Type>
tnbLib::timeVaryingUniformFixedValueFvPatchField<Type>::
timeVaryingUniformFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	timeSeries_(dict)
{
	if (dict.found("value"))
	{
		fvPatchField<Type>::operator==(Field<Type>("value", dict, p.size()));
	}
	else
	{
		updateCoeffs();
	}
}


template<class Type>
tnbLib::timeVaryingUniformFixedValueFvPatchField<Type>::
timeVaryingUniformFixedValueFvPatchField
(
	const timeVaryingUniformFixedValueFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
	timeSeries_(ptf.timeSeries_)
{}


template<class Type>
tnbLib::timeVaryingUniformFixedValueFvPatchField<Type>::
timeVaryingUniformFixedValueFvPatchField
(
	const timeVaryingUniformFixedValueFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf),
	timeSeries_(ptf.timeSeries_)
{}


template<class Type>
tnbLib::timeVaryingUniformFixedValueFvPatchField<Type>::
timeVaryingUniformFixedValueFvPatchField
(
	const timeVaryingUniformFixedValueFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF),
	timeSeries_(ptf.timeSeries_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::timeVaryingUniformFixedValueFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	fvPatchField<Type>::operator==
		(
			timeSeries_(this->db().time().timeOutputValue())
			);
	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::timeVaryingUniformFixedValueFvPatchField<Type>::write
(
	Ostream& os
) const
{
	fvPatchField<Type>::write(os);
	timeSeries_.write(os);
	this->writeEntry("value", os);
}


// ************************************************************************* //
#include <timeVaryingUniformInletOutletFvPatchField.hxx>

#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::timeVaryingUniformInletOutletFvPatchField<Type>::
timeVaryingUniformInletOutletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	inletOutletFvPatchField<Type>(p, iF),
	timeSeries_()
{}


template<class Type>
tnbLib::timeVaryingUniformInletOutletFvPatchField<Type>::
timeVaryingUniformInletOutletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	inletOutletFvPatchField<Type>(p, iF),
	timeSeries_(dict)
{
	this->refValue() = timeSeries_(this->db().time().timeOutputValue());
	this->refGrad() = pTraits<Type>::zero;
	this->valueFraction() = 0.0;

	if (dict.found("value"))
	{
		fvPatchField<Type>::operator==(Field<Type>("value", dict, p.size()));
	}
	else
	{
		fvPatchField<Type>::operator=(this->refValue());
	}
}


template<class Type>
tnbLib::timeVaryingUniformInletOutletFvPatchField<Type>::
timeVaryingUniformInletOutletFvPatchField
(
	const timeVaryingUniformInletOutletFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	inletOutletFvPatchField<Type>(ptf, p, iF, mapper),
	timeSeries_(ptf.timeSeries_)
{}


template<class Type>
tnbLib::timeVaryingUniformInletOutletFvPatchField<Type>::
timeVaryingUniformInletOutletFvPatchField
(
	const timeVaryingUniformInletOutletFvPatchField<Type>& ptf
)
	:
	inletOutletFvPatchField<Type>(ptf),
	timeSeries_(ptf.timeSeries_)
{}


template<class Type>
tnbLib::timeVaryingUniformInletOutletFvPatchField<Type>::
timeVaryingUniformInletOutletFvPatchField
(
	const timeVaryingUniformInletOutletFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	inletOutletFvPatchField<Type>(ptf, iF),
	timeSeries_(ptf.timeSeries_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::timeVaryingUniformInletOutletFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	this->refValue() = timeSeries_(this->db().time().timeOutputValue());
	inletOutletFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::timeVaryingUniformInletOutletFvPatchField<Type>::write
(
	Ostream& os
) const
{
	fvPatchField<Type>::write(os);
	timeSeries_.write(os);
	this->writeEntry("value", os);
}


// ************************************************************************* //
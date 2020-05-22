#include <fixedMeanValueFvPatchField.hxx>

#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	fixedMeanValueFvPatchField<Type>::fixedMeanValueFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fixedValueFvPatchField<Type>(p, iF),
		meanValue_(pTraits<Type>::zero),
		curTimeIndex_(-1)
	{}


	template<class Type>
	fixedMeanValueFvPatchField<Type>::fixedMeanValueFvPatchField
	(
		const fixedMeanValueFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
		meanValue_(ptf.meanValue_),
		curTimeIndex_(-1)
	{}


	template<class Type>
	fixedMeanValueFvPatchField<Type>::fixedMeanValueFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		fixedValueFvPatchField<Type>(p, iF),
		meanValue_(pTraits<Type>(dict.lookup("meanValue"))),
		curTimeIndex_(-1)
	{
		if (dict.found("value"))
		{
			fixedValueFvPatchField<Type>::operator==
				(
					Field<Type>("value", dict, p.size())
					);
		}
		else
		{
			fixedValueFvPatchField<Type>::operator==(meanValue_);
		}
	}


	template<class Type>
	fixedMeanValueFvPatchField<Type>::fixedMeanValueFvPatchField
	(
		const fixedMeanValueFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fixedValueFvPatchField<Type>(ptf, iF),
		meanValue_(ptf.meanValue_),
		curTimeIndex_(-1)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Map from self
	template<class Type>
	void fixedMeanValueFvPatchField<Type>::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		Field<Type>::autoMap(m);
	}


	// Reverse-map the given fvPatchField onto this fvPatchField
	template<class Type>
	void fixedMeanValueFvPatchField<Type>::rmap
	(
		const fvPatchField<Type>& ptf,
		const labelList& addr
	)
	{
		fixedValueFvPatchField<Type>::rmap(ptf, addr);
	}


	// Update the coefficients associated with the patch field
	template<class Type>
	void fixedMeanValueFvPatchField<Type>::updateCoeffs()
	{
		if (this->updated())
		{
			return;
		}

		if (curTimeIndex_ != this->db().time().timeIndex())
		{
			Field<Type>& patchField = *this;

			Field<Type> pif = this->patchInternalField();

			patchField = meanValue_ - gAverage(pif) + pif;

			curTimeIndex_ = this->db().time().timeIndex();
		}

		fixedValueFvPatchField<Type>::updateCoeffs();
	}


	// Write
	template<class Type>
	void fixedMeanValueFvPatchField<Type>::write(Ostream& os) const
	{
		fvPatchField<Type>::write(os);
		os.writeKeyword("meanValue")
			<< meanValue_ << token::END_STATEMENT << nl;
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
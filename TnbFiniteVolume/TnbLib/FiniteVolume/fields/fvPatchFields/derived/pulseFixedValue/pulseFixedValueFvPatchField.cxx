#include <pulseFixedValueFvPatchField.hxx>

#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	template<class Type>
	scalar pulseFixedValueFvPatchField<Type>::currentScale() const
	{
		return
			1.0
			+ amplitude_ *
			pos(1 - 2 * this->db().time().value()*frequency_)*
			sin(2 * mathematicalConstant::pi*frequency_*this->db().time().value());
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	pulseFixedValueFvPatchField<Type>::pulseFixedValueFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fixedValueFvPatchField<Type>(p, iF),
		refValue_(p.size()),
		amplitude_(0.0),
		frequency_(0.0),
		curTimeIndex_(-1)
	{}


	template<class Type>
	pulseFixedValueFvPatchField<Type>::pulseFixedValueFvPatchField
	(
		const pulseFixedValueFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
		refValue_(ptf.refValue_, mapper),
		amplitude_(ptf.amplitude_),
		frequency_(ptf.frequency_),
		curTimeIndex_(-1)
	{}


	template<class Type>
	pulseFixedValueFvPatchField<Type>::pulseFixedValueFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		fixedValueFvPatchField<Type>(p, iF),
		refValue_("refValue", dict, p.size()),
		amplitude_(readScalar(dict.lookup("amplitude"))),
		frequency_(readScalar(dict.lookup("frequency"))),
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
			fixedValueFvPatchField<Type>::operator==(refValue_*currentScale());
		}
	}


	template<class Type>
	pulseFixedValueFvPatchField<Type>::pulseFixedValueFvPatchField
	(
		const pulseFixedValueFvPatchField<Type>& ptf
	)
		:
		fixedValueFvPatchField<Type>(ptf),
		refValue_(ptf.refValue_),
		amplitude_(ptf.amplitude_),
		frequency_(ptf.frequency_),
		curTimeIndex_(-1)
	{}


	template<class Type>
	pulseFixedValueFvPatchField<Type>::pulseFixedValueFvPatchField
	(
		const pulseFixedValueFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fixedValueFvPatchField<Type>(ptf, iF),
		refValue_(ptf.refValue_),
		amplitude_(ptf.amplitude_),
		frequency_(ptf.frequency_),
		curTimeIndex_(-1)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void pulseFixedValueFvPatchField<Type>::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		fixedValueFvPatchField<Type>::autoMap(m);
		refValue_.autoMap(m);
	}


	template<class Type>
	void pulseFixedValueFvPatchField<Type>::rmap
	(
		const fvPatchField<Type>& ptf,
		const labelList& addr
	)
	{
		fixedValueFvPatchField<Type>::rmap(ptf, addr);

		const pulseFixedValueFvPatchField<Type>& tiptf =
			refCast<const pulseFixedValueFvPatchField<Type> >(ptf);

		refValue_.rmap(tiptf.refValue_, addr);
	}


	template<class Type>
	void pulseFixedValueFvPatchField<Type>::updateCoeffs()
	{
		if (this->updated())
		{
			return;
		}

		if (curTimeIndex_ != this->db().time().timeIndex())
		{
			Field<Type>& patchField = *this;

			patchField = refValue_ * currentScale();

			curTimeIndex_ = this->db().time().timeIndex();
		}

		fixedValueFvPatchField<Type>::updateCoeffs();
	}


	template<class Type>
	void pulseFixedValueFvPatchField<Type>::write(Ostream& os) const
	{
		fvPatchField<Type>::write(os);
		refValue_.writeEntry("refValue", os);
		os.writeKeyword("amplitude")
			<< amplitude_ << token::END_STATEMENT << nl;
		os.writeKeyword("frequency")
			<< frequency_ << token::END_STATEMENT << nl;
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
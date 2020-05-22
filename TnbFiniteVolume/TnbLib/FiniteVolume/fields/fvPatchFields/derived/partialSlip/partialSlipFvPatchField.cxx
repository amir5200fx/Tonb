#include <partialSlipFvPatchField.hxx>

#include <symmTransformField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	partialSlipFvPatchField<Type>::partialSlipFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		transformFvPatchField<Type>(p, iF),
		valueFraction_(p.size(), 1.0)
	{}


	template<class Type>
	partialSlipFvPatchField<Type>::partialSlipFvPatchField
	(
		const partialSlipFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		transformFvPatchField<Type>(ptf, p, iF, mapper),
		valueFraction_(ptf.valueFraction_, mapper)
	{}


	template<class Type>
	partialSlipFvPatchField<Type>::partialSlipFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		transformFvPatchField<Type>(p, iF),
		valueFraction_("valueFraction", dict, p.size())
	{
		evaluate();
	}


	template<class Type>
	partialSlipFvPatchField<Type>::partialSlipFvPatchField
	(
		const partialSlipFvPatchField<Type>& ptf
	)
		:
		transformFvPatchField<Type>(ptf),
		valueFraction_(ptf.valueFraction_)
	{}


	template<class Type>
	partialSlipFvPatchField<Type>::partialSlipFvPatchField
	(
		const partialSlipFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		transformFvPatchField<Type>(ptf, iF),
		valueFraction_(ptf.valueFraction_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void partialSlipFvPatchField<Type>::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		transformFvPatchField<Type>::autoMap(m);
		valueFraction_.autoMap(m);
	}


	template<class Type>
	void partialSlipFvPatchField<Type>::rmap
	(
		const fvPatchField<Type>& ptf,
		const labelList& addr
	)
	{
		transformFvPatchField<Type>::rmap(ptf, addr);

		const partialSlipFvPatchField<Type>& dmptf =
			refCast<const partialSlipFvPatchField<Type> >(ptf);

		valueFraction_.rmap(dmptf.valueFraction_, addr);
	}


	template<class Type>
	tmp<Field<Type> > partialSlipFvPatchField<Type>::snGrad() const
	{
		vectorField nHat = this->patch().nf();
		Field<Type> pif = this->patchInternalField();

		return
			(
			(1.0 - valueFraction_)*transform(I - sqr(nHat), pif) - pif
				)*this->patch().deltaCoeffs();
	}


	template<class Type>
	void partialSlipFvPatchField<Type>::evaluate(const Pstream::commsTypes)
	{
		if (!this->updated())
		{
			this->updateCoeffs();
		}

		vectorField nHat = this->patch().nf();

		Field<Type>::operator=
			(
			(1.0 - valueFraction_)
				*transform(I - sqr(nHat), this->patchInternalField())
				);

		transformFvPatchField<Type>::evaluate();
	}


	template<class Type>
	tmp<Field<Type> > partialSlipFvPatchField<Type>::snGradTransformDiag() const
	{
		vectorField nHat = this->patch().nf();
		vectorField diag(nHat.size());

		diag.replace(vector::X, mag(nHat.component(vector::X)));
		diag.replace(vector::Y, mag(nHat.component(vector::Y)));
		diag.replace(vector::Z, mag(nHat.component(vector::Z)));

		return
			valueFraction_ * pTraits<Type>::one
			+ (1.0 - valueFraction_)
			*transformFieldMask<Type>(pow<vector, pTraits<Type>::rank>(diag));
	}


	template<class Type>
	void partialSlipFvPatchField<Type>::write(Ostream& os) const
	{
		transformFvPatchField<Type>::write(os);
		valueFraction_.writeEntry("valueFraction", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
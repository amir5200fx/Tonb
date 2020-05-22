#include <fixedNormalSlipFvPatchField.hxx>

#include <symmTransformField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	fixedNormalSlipFvPatchField<Type>::fixedNormalSlipFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		transformFvPatchField<Type>(p, iF),
		fixedValue_(p.size(), pTraits<Type>::zero)
	{}


	template<class Type>
	fixedNormalSlipFvPatchField<Type>::fixedNormalSlipFvPatchField
	(
		const fixedNormalSlipFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		transformFvPatchField<Type>(ptf, p, iF, mapper),
		fixedValue_(ptf.fixedValue_, mapper)
	{}


	template<class Type>
	fixedNormalSlipFvPatchField<Type>::fixedNormalSlipFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		transformFvPatchField<Type>(p, iF),
		fixedValue_("fixedValue", dict, p.size())
	{
		evaluate();
	}


	template<class Type>
	fixedNormalSlipFvPatchField<Type>::fixedNormalSlipFvPatchField
	(
		const fixedNormalSlipFvPatchField<Type>& ptf
	)
		:
		transformFvPatchField<Type>(ptf),
		fixedValue_(ptf.fixedValue_)
	{}


	template<class Type>
	fixedNormalSlipFvPatchField<Type>::fixedNormalSlipFvPatchField
	(
		const fixedNormalSlipFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		transformFvPatchField<Type>(ptf, iF),
		fixedValue_(ptf.fixedValue_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void fixedNormalSlipFvPatchField<Type>::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		transformFvPatchField<Type>::autoMap(m);
		fixedValue_.autoMap(m);
	}


	template<class Type>
	void fixedNormalSlipFvPatchField<Type>::rmap
	(
		const fvPatchField<Type>& ptf,
		const labelList& addr
	)
	{
		transformFvPatchField<Type>::rmap(ptf, addr);

		const fixedNormalSlipFvPatchField<Type>& dmptf =
			refCast<const fixedNormalSlipFvPatchField<Type> >(ptf);

		fixedValue_.rmap(dmptf.fixedValue_, addr);
	}


	template<class Type>
	tmp<Field<Type> > fixedNormalSlipFvPatchField<Type>::snGrad() const
	{
		vectorField nHat = this->patch().nf();
		Field<Type> pif = this->patchInternalField();

		return
			(
			(nHat*(nHat & fixedValue_) + transform(I - sqr(nHat), pif)) - pif
				)*this->patch().deltaCoeffs();
	}


	template<class Type>
	void fixedNormalSlipFvPatchField<Type>::evaluate(const Pstream::commsTypes)
	{
		if (!this->updated())
		{
			this->updateCoeffs();
		}

		vectorField nHat = this->patch().nf();

		Field<Type>::operator=
			(
				nHat*(nHat & fixedValue_)
				+ transform(I - sqr(nHat), this->patchInternalField())
				);

		transformFvPatchField<Type>::evaluate();
	}


	template<class Type>
	tmp<Field<Type> >
		fixedNormalSlipFvPatchField<Type>::snGradTransformDiag() const
	{
		vectorField nHat = this->patch().nf();
		vectorField diag(nHat.size());

		diag.replace(vector::X, mag(nHat.component(vector::X)));
		diag.replace(vector::Y, mag(nHat.component(vector::Y)));
		diag.replace(vector::Z, mag(nHat.component(vector::Z)));

		return transformFieldMask<Type>(pow<vector, pTraits<Type>::rank>(diag));
	}


	template<class Type>
	void fixedNormalSlipFvPatchField<Type>::write(Ostream& os) const
	{
		transformFvPatchField<Type>::write(os);
		fixedValue_.writeEntry("fixedValue", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
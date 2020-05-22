#include <basicSymmetryFvPatchField.hxx>

#include <symmTransformField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		transformFvPatchField<Type>(p, iF),
		skewCorrected_(false),
		secondOrder_(false)
	{}


	template<class Type>
	basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
	(
		const basicSymmetryFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		transformFvPatchField<Type>(ptf, p, iF, mapper),
		skewCorrected_(ptf.skewCorrected_),
		secondOrder_(ptf.secondOrder_)
	{}


	template<class Type>
	basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		transformFvPatchField<Type>(p, iF, dict),
		skewCorrected_(dict.lookupOrDefault<Switch>("skewCorrected", false)),
		secondOrder_(dict.lookupOrDefault<Switch>("secondOrder", false))
	{
		this->evaluate();
	}


	template<class Type>
	basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
	(
		const basicSymmetryFvPatchField<Type>& ptf
	)
		:
		transformFvPatchField<Type>(ptf),
		skewCorrected_(ptf.skewCorrected_),
		secondOrder_(ptf.secondOrder_)
	{}


	template<class Type>
	basicSymmetryFvPatchField<Type>::basicSymmetryFvPatchField
	(
		const basicSymmetryFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		transformFvPatchField<Type>(ptf, iF),
		skewCorrected_(ptf.skewCorrected_),
		secondOrder_(ptf.secondOrder_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Return gradient at boundary
	// Note: see template specialisations for second order behaviour
	// HJ, 18/Mar/2015
	template<class Type>
	tmp<Field<Type> > basicSymmetryFvPatchField<Type>::snGrad() const
	{
		vectorField nHat = this->patch().nf();

		const Field<Type> pif = this->patchInternalField();

		return
			(
				transform(I - 2.0*sqr(nHat), pif) - pif
				)*(this->patch().deltaCoeffs() / 2.0);
	}


	// Evaluate the field on the patch
	// Note: see template specialisations for second order behaviour
	// HJ, 18/Mar/2015
	template<class Type>
	void basicSymmetryFvPatchField<Type>::evaluate(const Pstream::commsTypes)
	{
		if (!this->updated())
		{
			this->updateCoeffs();
		}

		vectorField nHat = this->patch().nf();

		Field<Type> pif = this->patchInternalField();

		Field<Type>::operator=
			(
				0.5*(pif + transform(I - 2.0*sqr(nHat), pif))
				);

		transformFvPatchField<Type>::evaluate();
	}


	// Return defining fields
	template<class Type>
	tmp<Field<Type> > basicSymmetryFvPatchField<Type>::snGradTransformDiag() const
	{
		vectorField nHat = this->patch().nf();
		vectorField diag(nHat.size());

		diag.replace(vector::X, mag(nHat.component(vector::X)));
		diag.replace(vector::Y, mag(nHat.component(vector::Y)));
		diag.replace(vector::Z, mag(nHat.component(vector::Z)));

		return transformFieldMask<Type>(pow<vector, pTraits<Type>::rank>(diag));
	}


	template<class Type>
	void basicSymmetryFvPatchField<Type>::write(Ostream& os) const
	{
		fvPatchField<Type>::write(os);

		this->writeEntryIfDifferent
		(
			os,
			"skewCorrected",
			Switch(false),
			skewCorrected_
		);

		this->writeEntryIfDifferent
		(
			os,
			"secondOrder",
			Switch(false),
			secondOrder_
		);

		// Write values.  HJ, 18/Mar/2015
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
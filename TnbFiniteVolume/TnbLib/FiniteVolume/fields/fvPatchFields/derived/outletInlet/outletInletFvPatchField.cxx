#include <outletInletFvPatchField.hxx>

#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	outletInletFvPatchField<Type>::outletInletFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		mixedFvPatchField<Type>(p, iF)
	{
		this->refValue() = *this;
		this->refGrad() = pTraits<Type>::zero;
		this->valueFraction() = 0.0;
	}


	template<class Type>
	outletInletFvPatchField<Type>::outletInletFvPatchField
	(
		const outletInletFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		mixedFvPatchField<Type>(ptf, p, iF, mapper)
	{}


	template<class Type>
	outletInletFvPatchField<Type>::outletInletFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		mixedFvPatchField<Type>(p, iF)
	{
		this->refValue() = Field<Type>("outletValue", dict, p.size());

		if (dict.found("value"))
		{
			fvPatchField<Type>::operator=
				(
					Field<Type>("value", dict, p.size())
					);
		}
		else
		{
			fvPatchField<Type>::operator=(this->refValue());
		}

		this->refGrad() = pTraits<Type>::zero;
		this->valueFraction() = 0.0;
	}


	template<class Type>
	outletInletFvPatchField<Type>::outletInletFvPatchField
	(
		const outletInletFvPatchField<Type>& ptf
	)
		:
		mixedFvPatchField<Type>(ptf)
	{}


	template<class Type>
	outletInletFvPatchField<Type>::outletInletFvPatchField
	(
		const outletInletFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		mixedFvPatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void outletInletFvPatchField<Type>::updateCoeffs()
	{
		if (this->updated())
		{
			return;
		}

		const fvsPatchField<scalar>& phip = this->lookupPatchField
		(
			"phi",
			reinterpret_cast<const surfaceScalarField*>(0),
			reinterpret_cast<const scalar*>(0)
		);

		this->valueFraction() = pos(phip);

		mixedFvPatchField<Type>::updateCoeffs();
	}


	template<class Type>
	void outletInletFvPatchField<Type>::write(Ostream& os) const
	{
		fvPatchField<Type>::write(os);
		this->refValue().writeEntry("outletValue", os);
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
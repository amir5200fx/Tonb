#include <fluxFvPatchField.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	fluxFvPatchField<Type>::fluxFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fixedGradientFvPatchField<Type>(p, iF),
		flux_(p.size(), pTraits<Type>::zero),
		reactivity_(p.size(), 0),
		gammaName_("gamma")
	{
		this->gradient() = pTraits<Type>::zero;
	}


	template<class Type>
	fluxFvPatchField<Type>::fluxFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		fixedGradientFvPatchField<Type>(p, iF),
		flux_("flux", dict, p.size()),
		reactivity_("reactivity", dict, p.size()),
		gammaName_(dict.lookup("gamma"))
	{
		// Set dummy gradient
		this->gradient() = pTraits<Type>::zero;

		// Read the value entry from the dictionary
		if (dict.found("value"))
		{
			fvPatchField<Type>::operator=
				(
					Field<Type>("value", dict, p.size())
					);
		}
		else
		{
			FatalIOErrorIn
			(
				"fluxFvPatchField<Type>::fluxFvPatchField"
				"("
				"const fvPatch& p,"
				"const DimensionedField<Type, volMesh>& iF,"
				"const dictionary& dict,"
				"const bool valueRequired"
				")",
				dict
			) << "Essential entry 'value' missing"
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	fluxFvPatchField<Type>::fluxFvPatchField
	(
		const fluxFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fixedGradientFvPatchField<Type>(ptf, p, iF, mapper),
		flux_(ptf.flux_),
		reactivity_(ptf.reactivity_),
		gammaName_(ptf.gammaName_)
	{}


	template<class Type>
	fluxFvPatchField<Type>::fluxFvPatchField
	(
		const fluxFvPatchField<Type>& ptf
	)
		:
		fixedGradientFvPatchField<Type>(ptf),
		flux_(ptf.flux_),
		reactivity_(ptf.reactivity_),
		gammaName_(ptf.gammaName_)
	{}


	template<class Type>
	fluxFvPatchField<Type>::fluxFvPatchField
	(
		const fluxFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fixedGradientFvPatchField<Type>(ptf, iF),
		flux_(ptf.flux_),
		reactivity_(ptf.reactivity_),
		gammaName_(ptf.gammaName_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void fluxFvPatchField<Type>::updateCoeffs()
	{
		if (this->updated())
		{
			return;
		}

		const fvPatchField<scalar>& gammap =
			this->lookupPatchField
			(
				gammaName_,
				reinterpret_cast<const volScalarField*>(NULL),
				reinterpret_cast<const scalar*>(NULL)
			);

		this->gradient() = reactivity_ * flux_ / gammap;

		fixedGradientFvPatchField<Type>::updateCoeffs();
	}


	template<class Type>
	void fluxFvPatchField<Type>::write(Ostream& os) const
	{
		fixedGradientFvPatchField<Type>::write(os);
		flux_.writeEntry("flux", os);
		reactivity_.writeEntry("reactivity", os);
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //

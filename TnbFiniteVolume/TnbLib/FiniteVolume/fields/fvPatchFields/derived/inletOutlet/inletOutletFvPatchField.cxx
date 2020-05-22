#include <inletOutletFvPatchField.hxx>

#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	inletOutletFvPatchField<Type>::inletOutletFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		mixedFvPatchField<Type>(p, iF),
		phiName_("phi")
	{
		this->refValue() = pTraits<Type>::zero;
		this->refGrad() = pTraits<Type>::zero;
		this->valueFraction() = 0.0;
	}


	template<class Type>
	inletOutletFvPatchField<Type>::inletOutletFvPatchField
	(
		const inletOutletFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		mixedFvPatchField<Type>(ptf, p, iF, mapper),
		phiName_(ptf.phiName_)
	{}


	template<class Type>
	inletOutletFvPatchField<Type>::inletOutletFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		mixedFvPatchField<Type>(p, iF),
		phiName_(dict.lookupOrDefault<word>("phi", "phi"))
	{
		this->refValue() = Field<Type>("inletValue", dict, p.size());

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
	inletOutletFvPatchField<Type>::inletOutletFvPatchField
	(
		const inletOutletFvPatchField<Type>& ptf
	)
		:
		mixedFvPatchField<Type>(ptf),
		phiName_(ptf.phiName_)
	{}


	template<class Type>
	inletOutletFvPatchField<Type>::inletOutletFvPatchField
	(
		const inletOutletFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		mixedFvPatchField<Type>(ptf, iF),
		phiName_(ptf.phiName_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void inletOutletFvPatchField<Type>::updateCoeffs()
	{
		if (this->updated())
		{
			return;
		}

		if (!this->db().objectRegistry::found(phiName_))
		{
			// Flux not available, do not update
			InfoIn
			(
				"void inletOutletFvPatchField<Type>::"
				"updateCoeffs()"
			) << "Flux field " << phiName_ << " not found.  "
				<< "Performing mixed update" << endl;

			mixedFvPatchField<Type>::updateCoeffs();

			return;
		}

		const scalarField& phip = this->lookupPatchField
		(
			phiName_,
			reinterpret_cast<const surfaceScalarField*>(0),
			reinterpret_cast<const scalar*>(0)
		);

		this->valueFraction() = 1.0 - pos(phip);

		mixedFvPatchField<Type>::updateCoeffs();
	}


	template<class Type>
	void inletOutletFvPatchField<Type>::write(Ostream& os) const
	{
		fvPatchField<Type>::write(os);
		if (phiName_ != "phi")
		{
			os.writeKeyword("phi")
				<< phiName_ << token::END_STATEMENT << nl;
		}
		this->refValue().writeEntry("inletValue", os);
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	template<class Type>
	void inletOutletFvPatchField<Type>::operator=
		(
			const fvPatchField<Type>& ptf
			)
	{
		fvPatchField<Type>::operator=
			(
				this->valueFraction()*this->refValue()
				+ (1 - this->valueFraction())*ptf
				);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
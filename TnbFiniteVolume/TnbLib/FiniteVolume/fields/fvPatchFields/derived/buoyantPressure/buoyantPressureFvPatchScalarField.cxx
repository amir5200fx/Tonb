#include <buoyantPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	buoyantPressureFvPatchScalarField::
		buoyantPressureFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		fixedGradientFvPatchScalarField(p, iF),
		rhoName_("rho")
	{}


	buoyantPressureFvPatchScalarField::
		buoyantPressureFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
		:
		fixedGradientFvPatchScalarField(p, iF),
		rhoName_(dict.lookupOrDefault<word>("rho", "rho"))
	{
		fvPatchField<scalar>::operator=(patchInternalField());
		gradient() = 0.0;
	}


	buoyantPressureFvPatchScalarField::
		buoyantPressureFvPatchScalarField
		(
			const buoyantPressureFvPatchScalarField& ptf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		fixedGradientFvPatchScalarField(ptf, p, iF, mapper),
		rhoName_(ptf.rhoName_)
	{}


	buoyantPressureFvPatchScalarField::
		buoyantPressureFvPatchScalarField
		(
			const buoyantPressureFvPatchScalarField& ptf
		)
		:
		fixedGradientFvPatchScalarField(ptf),
		rhoName_(ptf.rhoName_)
	{}


	buoyantPressureFvPatchScalarField::
		buoyantPressureFvPatchScalarField
		(
			const buoyantPressureFvPatchScalarField& ptf,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		fixedGradientFvPatchScalarField(ptf, iF),
		rhoName_(ptf.rhoName_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void buoyantPressureFvPatchScalarField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		// If variables are not found, evaluate as zero gradient
		// HJ, 17/Jan/2012
		if
			(
				!db().foundObject<uniformDimensionedVectorField>("g")
				|| !db().foundObject<volScalarField>(rhoName_)
				)
		{
			InfoIn
			(
				"void buoyantPressureFvPatchScalarField::updateCoeffs()"
			) << "Fields required for evaluation not found for patch "
				<< patch().name() << endl;

			gradient() = 0;
			fixedGradientFvPatchScalarField::updateCoeffs();

			return;
		}

		const uniformDimensionedVectorField& g =
			db().lookupObject<uniformDimensionedVectorField>("g");

		const fvPatchField<scalar>& rho =
			lookupPatchField<volScalarField, scalar>(rhoName_);

		// If the variable name is "p_rgh" or "pd" assume it is p - rho*g.h
		// and set the gradient appropriately.
		// Otherwise assume the variable is the static pressure.
		if
			(
				dimensionedInternalField().name() == "p_rgh"
				|| dimensionedInternalField().name() == "pd"
				)
		{
			gradient() = -rho.snGrad()*(g.value() & patch().Cf());
		}
		else
		{
			gradient() = rho * (g.value() & patch().nf());
		}

		fixedGradientFvPatchScalarField::updateCoeffs();
	}


	void buoyantPressureFvPatchScalarField::write(Ostream& os) const
	{
		fixedGradientFvPatchScalarField::write(os);
		os.writeKeyword("rho") << rhoName_ << token::END_STATEMENT << nl;
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		buoyantPressureFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
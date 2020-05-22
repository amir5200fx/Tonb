#include <rotatingTotalPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	rotatingTotalPressureFvPatchScalarField::
		rotatingTotalPressureFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		totalPressureFvPatchScalarField(p, iF),
		omega_(vector::zero)
	{}


	rotatingTotalPressureFvPatchScalarField::rotatingTotalPressureFvPatchScalarField
	(
		const rotatingTotalPressureFvPatchScalarField& ptf,
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		totalPressureFvPatchScalarField(ptf, p, iF, mapper),
		omega_(ptf.omega_)
	{}


	rotatingTotalPressureFvPatchScalarField::rotatingTotalPressureFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const dictionary& dict
	)
		:
		totalPressureFvPatchScalarField(p, iF, dict),
		omega_(dict.lookup("omega"))
	{}


	rotatingTotalPressureFvPatchScalarField::rotatingTotalPressureFvPatchScalarField
	(
		const rotatingTotalPressureFvPatchScalarField& tppsf
	)
		:
		totalPressureFvPatchScalarField(tppsf),
		omega_(tppsf.omega_)
	{}


	rotatingTotalPressureFvPatchScalarField::rotatingTotalPressureFvPatchScalarField
	(
		const rotatingTotalPressureFvPatchScalarField& tppsf,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		totalPressureFvPatchScalarField(tppsf, iF),
		omega_(tppsf.omega_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void rotatingTotalPressureFvPatchScalarField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		if (!this->db().objectRegistry::found(UName()))
		{
			// U not available, do not update
			totalPressureFvPatchScalarField::updateCoeffs();

			return;
		}

		vector axisHat = omega_ / mag(omega_);
		vectorField rotationVelocity =
			omega_ ^ (patch().Cf() - axisHat * (axisHat & patch().Cf()));

		vectorField Up = lookupPatchField<volVectorField, vector>(UName())
			+ rotationVelocity;

		totalPressureFvPatchScalarField::updateCoeffs(Up);
	}


	void rotatingTotalPressureFvPatchScalarField::write(Ostream& os) const
	{
		totalPressureFvPatchScalarField::write(os);
		os.writeKeyword("omega") << omega_ << token::END_STATEMENT << nl;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		rotatingTotalPressureFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
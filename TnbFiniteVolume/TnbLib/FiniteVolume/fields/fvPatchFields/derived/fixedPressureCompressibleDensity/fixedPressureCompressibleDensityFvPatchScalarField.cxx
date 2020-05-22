#include <fixedPressureCompressibleDensityFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	fixedPressureCompressibleDensityFvPatchScalarField::
		fixedPressureCompressibleDensityFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		fixedValueFvPatchField<scalar>(p, iF),
		pName_("pNameIsUndefined")
	{}


	fixedPressureCompressibleDensityFvPatchScalarField::
		fixedPressureCompressibleDensityFvPatchScalarField
		(
			const fixedPressureCompressibleDensityFvPatchScalarField& ptf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		fixedValueFvPatchField<scalar>(ptf, p, iF, mapper),
		pName_(ptf.pName_)
	{}


	fixedPressureCompressibleDensityFvPatchScalarField::
		fixedPressureCompressibleDensityFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
		:
		fixedValueFvPatchField<scalar>(p, iF, dict),
		pName_(dict.lookup("p"))
	{}


	fixedPressureCompressibleDensityFvPatchScalarField::
		fixedPressureCompressibleDensityFvPatchScalarField
		(
			const fixedPressureCompressibleDensityFvPatchScalarField& ptf
		)
		:
		fixedValueFvPatchField<scalar>(ptf),
		pName_(ptf.pName_)
	{}


	fixedPressureCompressibleDensityFvPatchScalarField::
		fixedPressureCompressibleDensityFvPatchScalarField
		(
			const fixedPressureCompressibleDensityFvPatchScalarField& ptf,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		fixedValueFvPatchField<scalar>(ptf, iF),
		pName_(ptf.pName_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void fixedPressureCompressibleDensityFvPatchScalarField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		const fvPatchField<scalar>& pp =
			lookupPatchField<volScalarField, scalar>(pName_);

		const dictionary& thermoProps =
			db().lookupObject<IOdictionary>("thermodynamicProperties");

		const scalar rholSat =
			dimensionedScalar(thermoProps.lookup("rholSat")).value();

		const scalar pSat =
			dimensionedScalar(thermoProps.lookup("pSat")).value();

		const scalar psil = dimensionedScalar(thermoProps.lookup("psil")).value();

		operator==(rholSat + psil * (pp - pSat));

		fixedValueFvPatchField<scalar>::updateCoeffs();
	}


	void fixedPressureCompressibleDensityFvPatchScalarField::write
	(
		Ostream& os
	) const
	{
		fvPatchField<scalar>::write(os);
		os.writeKeyword("p") << pName_ << token::END_STATEMENT << nl;
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		fixedPressureCompressibleDensityFvPatchScalarField
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
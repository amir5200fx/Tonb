#include <freestreamPressureFvPatchScalarField.hxx>

#include <freestreamFvPatchFields.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	freestreamPressureFvPatchScalarField::freestreamPressureFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		zeroGradientFvPatchScalarField(p, iF)
	{}


	freestreamPressureFvPatchScalarField::freestreamPressureFvPatchScalarField
	(
		const freestreamPressureFvPatchScalarField& ptf,
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		zeroGradientFvPatchScalarField(ptf, p, iF, mapper)
	{}


	freestreamPressureFvPatchScalarField::freestreamPressureFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const dictionary& dict
	)
		:
		zeroGradientFvPatchScalarField(p, iF, dict)
	{}


	freestreamPressureFvPatchScalarField::freestreamPressureFvPatchScalarField
	(
		const freestreamPressureFvPatchScalarField& wbppsf
	)
		:
		zeroGradientFvPatchScalarField(wbppsf)
	{}


	freestreamPressureFvPatchScalarField::freestreamPressureFvPatchScalarField
	(
		const freestreamPressureFvPatchScalarField& wbppsf,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		zeroGradientFvPatchScalarField(wbppsf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void freestreamPressureFvPatchScalarField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		const freestreamFvPatchVectorField& Up =
			refCast<const freestreamFvPatchVectorField>
			(
				lookupPatchField<volVectorField, vector>("U")
				);

		const surfaceScalarField& phi =
			db().lookupObject<surfaceScalarField>("phi");

		fvsPatchField<scalar>& phip =
			const_cast<fvsPatchField<scalar>&>
			(
				patch().patchField<surfaceScalarField, scalar>(phi)
				);

		if (phi.dimensions() == dimVelocity * dimArea)
		{
			phip = patch().Sf() & Up.freestreamValue();
		}
		else if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
		{
			const fvPatchField<scalar>& rhop =
				lookupPatchField<volScalarField, scalar>("rho");

			phip = rhop * (patch().Sf() & Up.freestreamValue());
		}
		else
		{
			FatalErrorIn("freestreamPressureFvPatchScalarField::updateCoeffs()")
				<< "dimensions of phi are not correct"
				<< "\n    on patch " << this->patch().name()
				<< " of field " << this->dimensionedInternalField().name()
				<< " in file " << this->dimensionedInternalField().objectPath()
				<< exit(FatalError);
		}

		zeroGradientFvPatchScalarField::updateCoeffs();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField(fvPatchScalarField, freestreamPressureFvPatchScalarField);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
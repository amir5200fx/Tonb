#include <gradientEnthalpyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::gradientEnthalpyFvPatchScalarField::gradientEnthalpyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(p, iF)
{}


tnbLib::gradientEnthalpyFvPatchScalarField::gradientEnthalpyFvPatchScalarField
(
	const gradientEnthalpyFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedGradientFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::gradientEnthalpyFvPatchScalarField::gradientEnthalpyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedGradientFvPatchScalarField(p, iF, dict)
{}


tnbLib::gradientEnthalpyFvPatchScalarField::gradientEnthalpyFvPatchScalarField
(
	const gradientEnthalpyFvPatchScalarField& tppsf
)
	:
	fixedGradientFvPatchScalarField(tppsf)
{}


tnbLib::gradientEnthalpyFvPatchScalarField::gradientEnthalpyFvPatchScalarField
(
	const gradientEnthalpyFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(tppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::gradientEnthalpyFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const basicThermo& thermo = db().lookupObject<basicThermo>
		(
			"thermophysicalProperties"
			);

	const label patchi = patch().index();

	fvPatchScalarField& Tw =
		const_cast<fvPatchScalarField&>(thermo.T().boundaryField()[patchi]);

	Tw.evaluate();

	if
		(
			dimensionedInternalField().name() == db().mangleFileName("h")
			)
	{
		gradient() = thermo.Cp(Tw, patchi)*Tw.snGrad()
			+ patch().deltaCoeffs()*
			(
				thermo.h(Tw, patchi)
				- thermo.h(Tw, patch().faceCells())
				);
	}
	else if
		(
			dimensionedInternalField().name() == db().mangleFileName("i")
			)
	{
		// Get access to relative and rotational velocity
		const word UrelName("Urel");
		const word UrotName("Urot");

		if
			(
				!this->db().objectRegistry::found(UrelName)
				|| !this->db().objectRegistry::found(UrotName)
				)
		{
			// Velocities not available, do not update
			InfoIn
			(
				"void gradientEnthalpyFvPatchScalarField::"
				"updateCoeffs(const vectorField& Up)"
			) << "Velocity fields " << UrelName << " or "
				<< UrotName << " not found.  "
				<< "Performing enthalpy value update for field "
				<< this->dimensionedInternalField().name()
				<< " and patch " << patchi
				<< endl;

			gradient() = thermo.Cp(Tw, patchi)*Tw.snGrad()
				+ patch().deltaCoeffs()*
				(
					thermo.h(Tw, patchi)
					- thermo.h(Tw, patch().faceCells())
					);
		}
		else
		{
			const fvPatchVectorField& Urelp =
				lookupPatchField<volVectorField, vector>(UrelName);

			const fvPatchVectorField& Urotp =
				lookupPatchField<volVectorField, vector>(UrotName);

			gradient() = thermo.Cp(Tw, patchi)*Tw.snGrad()
				+ patch().deltaCoeffs()*
				(
					thermo.h(Tw, patchi)
					- thermo.h(Tw, patch().faceCells())
					)
				- mag(Urotp)*mag(Urotp.snGrad())
				+ mag(Urelp)*mag(Urelp.snGrad());
		}
	}
	else
	{
		gradient() = thermo.Cp(Tw, patchi)*Tw.snGrad()
			+ patch().deltaCoeffs()*
			(
				thermo.hs(Tw, patchi)
				- thermo.hs(Tw, patch().faceCells())
				);
	}

	fixedGradientFvPatchScalarField::updateCoeffs();
}


void tnbLib::gradientEnthalpyFvPatchScalarField::write(Ostream& os) const
{
	fixedGradientFvPatchScalarField::write(os);
	writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		gradientEnthalpyFvPatchScalarField
	);
}


// ************************************************************************* //
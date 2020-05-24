#include <fixedEnthalpyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedEnthalpyFvPatchScalarField::fixedEnthalpyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF)
{}


tnbLib::fixedEnthalpyFvPatchScalarField::fixedEnthalpyFvPatchScalarField
(
	const fixedEnthalpyFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::fixedEnthalpyFvPatchScalarField::fixedEnthalpyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict)
{}


tnbLib::fixedEnthalpyFvPatchScalarField::fixedEnthalpyFvPatchScalarField
(
	const fixedEnthalpyFvPatchScalarField& tppsf
)
	:
	fixedValueFvPatchScalarField(tppsf)
{}


tnbLib::fixedEnthalpyFvPatchScalarField::fixedEnthalpyFvPatchScalarField
(
	const fixedEnthalpyFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(tppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fixedEnthalpyFvPatchScalarField::updateCoeffs()
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
		operator==(thermo.h(Tw, patchi));
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

			operator==(thermo.h(Tw, patchi));
		}
		else
		{
			const fvPatchVectorField& Urelp =
				lookupPatchField<volVectorField, vector>(UrelName);

			const fvPatchVectorField& Urotp =
				lookupPatchField<volVectorField, vector>(UrotName);

			operator==
				(
					thermo.h(Tw, patchi)
					- 0.5*(magSqr(Urotp) - magSqr(Urelp))
					);
		}
	}
	else
	{
		operator==(thermo.hs(Tw, patchi));
	}

	fixedValueFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		fixedEnthalpyFvPatchScalarField
	);
}


// ************************************************************************* //
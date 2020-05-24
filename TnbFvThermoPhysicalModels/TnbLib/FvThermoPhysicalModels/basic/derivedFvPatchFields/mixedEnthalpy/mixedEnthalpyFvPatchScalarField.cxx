#include <mixedEnthalpyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mixedEnthalpyFvPatchScalarField::mixedEnthalpyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF)
{
	valueFraction() = 0.0;
	refValue() = 0.0;
	refGrad() = 0.0;
}


tnbLib::mixedEnthalpyFvPatchScalarField::mixedEnthalpyFvPatchScalarField
(
	const mixedEnthalpyFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::mixedEnthalpyFvPatchScalarField::mixedEnthalpyFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF, dict)
{}


tnbLib::mixedEnthalpyFvPatchScalarField::mixedEnthalpyFvPatchScalarField
(
	const mixedEnthalpyFvPatchScalarField& tppsf
)
	:
	mixedFvPatchScalarField(tppsf)
{}


tnbLib::mixedEnthalpyFvPatchScalarField::mixedEnthalpyFvPatchScalarField
(
	const mixedEnthalpyFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(tppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mixedEnthalpyFvPatchScalarField::updateCoeffs()
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

	mixedFvPatchScalarField& Tw = refCast<mixedFvPatchScalarField>
		(
			const_cast<fvPatchScalarField&>(thermo.T().boundaryField()[patchi])
			);

	Tw.evaluate();

	valueFraction() = Tw.valueFraction();

	if
		(
			dimensionedInternalField().name() == db().mangleFileName("h")
			)
	{
		refValue() = thermo.h(Tw.refValue(), patchi);
		refGrad() = thermo.Cp(Tw, patchi)*Tw.refGrad()
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

			refValue() = thermo.h(Tw.refValue(), patchi);
			refGrad() = thermo.Cp(Tw, patchi)*Tw.refGrad()
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

			refValue() = thermo.h(Tw.refValue(), patchi)
				- 0.5*(magSqr(Urotp) - magSqr(Urelp));

			refGrad() = thermo.Cp(Tw, patchi)*Tw.refGrad()
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
		refValue() = thermo.hs(Tw.refValue(), patchi);
		refGrad() = thermo.Cp(Tw, patchi)*Tw.refGrad()
			+ patch().deltaCoeffs()*
			(
				thermo.hs(Tw, patchi)
				- thermo.hs(Tw, patch().faceCells())
				);
	}

	mixedFvPatchScalarField::updateCoeffs();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		mixedEnthalpyFvPatchScalarField
	);
}


// ************************************************************************* //
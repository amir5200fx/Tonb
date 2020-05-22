#include <fixedFluxPressureFvPatchScalarField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(p, iF),
	UName_("U"),
	phiName_("phi"),
	rhoName_("rho"),
	rAUName_("(1|A(" + UName_ + "))"),
	adjoint_(false)
{}


tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedGradientFvPatchScalarField(p, iF),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
	rAUName_(dict.lookupOrDefault<word>("rAU", "(1|A(" + UName_ + "))")),
	adjoint_(dict.lookupOrDefault<Switch>("adjoint", false))
{
	if (dict.found("gradient"))
	{
		gradient() = scalarField("gradient", dict, p.size());
		fixedGradientFvPatchScalarField::updateCoeffs();
		fixedGradientFvPatchScalarField::evaluate();
	}
	else
	{
		fvPatchField<scalar>::operator=(patchInternalField());
		gradient() = 0.0;
	}
}


tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fixedFluxPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedGradientFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	rAUName_(ptf.rAUName_),
	adjoint_(ptf.adjoint_)
{}


tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fixedFluxPressureFvPatchScalarField& ptf
)
	:
	fixedGradientFvPatchScalarField(ptf),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	rAUName_(ptf.rAUName_),
	adjoint_(ptf.adjoint_)
{}


tnbLib::fixedFluxPressureFvPatchScalarField::fixedFluxPressureFvPatchScalarField
(
	const fixedFluxPressureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedGradientFvPatchScalarField(ptf, iF),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	rAUName_(ptf.rAUName_),
	adjoint_(ptf.adjoint_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fixedFluxPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchField<vector>& Up =
		lookupPatchField<volVectorField, vector>(UName_);

	const surfaceScalarField& phi =
		db().lookupObject<surfaceScalarField>(phiName_);

	fvsPatchField<scalar> phip =
		patch().patchField<surfaceScalarField, scalar>(phi);

	if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchField<scalar>& rhop =
			lookupPatchField<volScalarField, scalar>(rhoName_);

		phip /= rhop;
	}

	// Collect diffusivity from the pressure equation
	scalarField rAp;

	if (this->db().objectRegistry::foundObject<volScalarField>(rAUName_))
	{
		rAp = lookupPatchField<volScalarField, scalar>(rAUName_);
	}
	else if
		(
			this->db().objectRegistry::foundObject<surfaceScalarField>(rAUName_)
			)
	{
		rAp = lookupPatchField<surfaceScalarField, scalar>(rAUName_);
	}
	else
	{
		FatalErrorIn
		(
			"void fixedFluxPressureFvPatchScalarField::updateCoeffs()"
		) << " Field " << rAUName_ << " not found for patch "
			<< patch().name() << " and field "
			<< dimensionedInternalField().name()
			<< abort(FatalError);
	}

	if (adjoint_)
	{
		gradient() = ((patch().Sf() & Up) - phip) / patch().magSf() / rAp;
	}
	else
	{
		gradient() = (phip - (patch().Sf() & Up)) / patch().magSf() / rAp;
	}

	fixedGradientFvPatchScalarField::updateCoeffs();
}


void tnbLib::fixedFluxPressureFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "U", "U", UName_);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntryIfDifferent<word>(os, "rAU", "rAU", rAUName_);
	writeEntryIfDifferent<Switch>(os, "adjoint", false, adjoint_);

	gradient().writeEntry("gradient", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		fixedFluxPressureFvPatchScalarField
	);
}

// ************************************************************************* //
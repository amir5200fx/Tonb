#include <turbulentIntensityKineticEnergyInletFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	inletOutletFvPatchScalarField(p, iF),
	intensity_(0.0),
	UName_("undefined-U"),
	phiName_("undefined-phi")
{
	this->refValue() = 0.0;
	this->refGrad() = 0.0;
	this->valueFraction() = 0.0;
}

tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const turbulentIntensityKineticEnergyInletFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	inletOutletFvPatchScalarField(ptf, p, iF, mapper),
	intensity_(ptf.intensity_),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_)
{}


tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	inletOutletFvPatchScalarField(p, iF),
	intensity_(readScalar(dict.lookup("intensity"))),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi"))
{
	if (intensity_ < 0 || intensity_ > 1)
	{
		FatalErrorIn
		(
			"turbulentIntensityKineticEnergyInletFvPatchScalarField::"
			"turbulentIntensityKineticEnergyInletFvPatchScalarField"
			"(const fvPatch& p, const DimensionedField<scalar, volMesh>& iF, "
			"const dictionary& dict)"
		) << "Turbulence intensity should be specified as a fraction 0-1 "
			"of the mean velocity\n"
			"    value given is " << intensity_
			<< "\n    on patch " << this->patch().name()
			<< " of field " << this->dimensionedInternalField().name()
			<< " in file " << this->dimensionedInternalField().objectPath()
			<< exit(FatalError);
	}

	fvPatchScalarField::operator=(scalarField("value", dict, p.size()));

	this->refValue() = 0.0;
	this->refGrad() = 0.0;
	this->valueFraction() = 0.0;
}

tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const turbulentIntensityKineticEnergyInletFvPatchScalarField& ptf
)
	:
	inletOutletFvPatchScalarField(ptf),
	intensity_(ptf.intensity_),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_)
{}


tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
turbulentIntensityKineticEnergyInletFvPatchScalarField
(
	const turbulentIntensityKineticEnergyInletFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	inletOutletFvPatchScalarField(ptf, iF),
	intensity_(ptf.intensity_),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::
updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchVectorField& Up =
		lookupPatchField<volVectorField, vector>(UName_);

	const fvsPatchScalarField& phip =
		lookupPatchField<surfaceScalarField, scalar>(phiName_);

	this->refValue() = SMALL + 1.5*sqr(intensity_)*magSqr(Up);
	this->valueFraction() = neg(phip);

	inletOutletFvPatchScalarField::updateCoeffs();
}


void tnbLib::turbulentIntensityKineticEnergyInletFvPatchScalarField::write
(
	Ostream& os
) const
{
	fvPatchScalarField::write(os);
	os.writeKeyword("intensity") << intensity_ << token::END_STATEMENT << nl;
	os.writeKeyword("U") << UName_ << token::END_STATEMENT << nl;
	os.writeKeyword("phi") << phiName_ << token::END_STATEMENT << nl;
	writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		turbulentIntensityKineticEnergyInletFvPatchScalarField
	);
}

// ************************************************************************* //
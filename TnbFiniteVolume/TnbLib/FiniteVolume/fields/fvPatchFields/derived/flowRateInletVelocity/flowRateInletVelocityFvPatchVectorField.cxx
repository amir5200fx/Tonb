#include <flowRateInletVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(p, iF),
	flowRate_(0),
	phiName_("phi"),
	rhoName_("rho"),
	gSumArea_(gSum(p.magSf()))
{}


tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<vector>(p, iF, dict),
	flowRate_(readScalar(dict.lookup("flowRate"))),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
	gSumArea_(gSum(p.magSf()))
{}


tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const flowRateInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<vector>(ptf, p, iF, mapper),
	flowRate_(ptf.flowRate_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	gSumArea_(gSum(p.magSf()))
{}


tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const flowRateInletVelocityFvPatchVectorField& ptf
)
	:
	fixedValueFvPatchField<vector>(ptf),
	flowRate_(ptf.flowRate_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	gSumArea_(gSum(ptf.patch().magSf()))
{}


tnbLib::flowRateInletVelocityFvPatchVectorField::
flowRateInletVelocityFvPatchVectorField
(
	const flowRateInletVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	fixedValueFvPatchField<vector>(ptf, iF),
	flowRate_(ptf.flowRate_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	gSumArea_(gSum(ptf.patch().magSf()))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::flowRateInletVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	//     if (patch().boundaryMesh().mesh().moving())
	//     {
	//         WarningIn
	//         (
	//             "void flowRateInletVelocityFvPatchVectorField::updateCoeffs()"
	//         )   << "Patch area not correctly updated on mesh motion"
	//             << endl;
	//     }

		// A simpler way of doing this would be nice
	scalar avgU = -flowRate_ / (gSumArea_ + SMALL);

	vectorField n = patch().nf();

	const surfaceScalarField& phi =
		db().lookupObject<surfaceScalarField>(phiName_);

	if (phi.dimensions() == dimVelocity * dimArea)
	{
		// Volumetric flow-rate
		operator==(n*avgU);
	}
	else if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchField<scalar>& rhop =
			lookupPatchField<volScalarField, scalar>(rhoName_);

		// Mass flow-rate
		operator==(n*avgU / rhop);
	}
	else
	{
		FatalErrorIn
		(
			"flowRateInletVelocityFvPatchVectorField::updateCoeffs()"
		) << "dimensions of " << phiName_ << " are incorrect" << nl
			<< "    on patch " << this->patch().name()
			<< " of field " << this->dimensionedInternalField().name()
			<< " in file " << this->dimensionedInternalField().objectPath()
			<< nl << exit(FatalError);
	}

	fixedValueFvPatchField<vector>::updateCoeffs();
}


void tnbLib::flowRateInletVelocityFvPatchVectorField::write(Ostream& os) const
{
	fvPatchField<vector>::write(os);
	os.writeKeyword("flowRate") << flowRate_ << token::END_STATEMENT << nl;
	if (phiName_ != "phi")
	{
		os.writeKeyword("phi") << phiName_ << token::END_STATEMENT << nl;
	}
	if (rhoName_ != "rho")
	{
		os.writeKeyword("rho") << rhoName_ << token::END_STATEMENT << nl;
	}
	writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		flowRateInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //
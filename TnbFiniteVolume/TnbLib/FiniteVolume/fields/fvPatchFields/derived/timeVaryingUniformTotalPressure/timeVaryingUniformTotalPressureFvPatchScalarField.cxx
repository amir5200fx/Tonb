#include <timeVaryingUniformTotalPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::timeVaryingUniformTotalPressureFvPatchScalarField::
timeVaryingUniformTotalPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	UName_("U"),
	phiName_("phi"),
	rhoName_("none"),
	psiName_("none"),
	gamma_(0.0),
	p0_(0.0),
	timeSeries_()
{}


tnbLib::timeVaryingUniformTotalPressureFvPatchScalarField::
timeVaryingUniformTotalPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	rhoName_(dict.lookupOrDefault<word>("rho", "none")),
	psiName_(dict.lookupOrDefault<word>("psi", "none")),
	gamma_(readScalar(dict.lookup("gamma"))),
	p0_(readScalar(dict.lookup("p0"))),
	timeSeries_(dict)
{
	if (dict.found("value"))
	{
		fvPatchField<scalar>::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchField<scalar>::operator=(p0_);
	}
}


tnbLib::timeVaryingUniformTotalPressureFvPatchScalarField::
timeVaryingUniformTotalPressureFvPatchScalarField
(
	const timeVaryingUniformTotalPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	rhoName_(ptf.rhoName_),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_),
	p0_(ptf.p0_),
	timeSeries_(ptf.timeSeries_)
{}


tnbLib::timeVaryingUniformTotalPressureFvPatchScalarField::
timeVaryingUniformTotalPressureFvPatchScalarField
(
	const timeVaryingUniformTotalPressureFvPatchScalarField& tppsf
)
	:
	fixedValueFvPatchScalarField(tppsf),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	rhoName_(tppsf.rhoName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	p0_(tppsf.p0_),
	timeSeries_(tppsf.timeSeries_)
{}


tnbLib::timeVaryingUniformTotalPressureFvPatchScalarField::
timeVaryingUniformTotalPressureFvPatchScalarField
(
	const timeVaryingUniformTotalPressureFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(tppsf, iF),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	rhoName_(tppsf.rhoName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	p0_(tppsf.p0_),
	timeSeries_(tppsf.timeSeries_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::timeVaryingUniformTotalPressureFvPatchScalarField::updateCoeffs
(
	const vectorField& Up
)
{
	if (updated())
	{
		return;
	}

	p0_ = timeSeries_(this->db().time().timeOutputValue());

	const fvsPatchField<scalar>& phip =
		lookupPatchField<surfaceScalarField, scalar>(phiName_);

	if (psiName_ == "none" && rhoName_ == "none")
	{
		operator==(p0_ - 0.5*(1.0 - pos(phip))*magSqr(Up));
	}
	else if (rhoName_ == "none")
	{
		const fvPatchField<scalar>& psip =
			lookupPatchField<volScalarField, scalar>(psiName_);

		if (gamma_ > 1.0)
		{
			scalar gM1ByG = (gamma_ - 1.0) / gamma_;

			operator==
				(
					p0_
					/ pow
					(
					(1.0 + 0.5*psip*gM1ByG*(1.0 - pos(phip))*magSqr(Up)),
						1.0 / gM1ByG
					)
					);
		}
		else
		{
			operator==(p0_ / (1.0 + 0.5*psip*(1.0 - pos(phip))*magSqr(Up)));
		}
	}
	else if (psiName_ == "none")
	{
		const fvPatchField<scalar>& rho =
			lookupPatchField<volScalarField, scalar>(rhoName_);

		operator==(p0_ - 0.5*rho*(1.0 - pos(phip))*magSqr(Up));
	}
	else
	{
		FatalErrorIn
		(
			"timeVaryingUniformTotalPressureFvPatchScalarField::updateCoeffs()"
		) << " rho or psi set inconsitently, rho = " << rhoName_
			<< ", psi = " << psiName_ << ".\n"
			<< "    Set either rho or psi or neither depending on the "
			"definition of total pressure.\n"
			<< "    Set the unused variables to 'none'.\n"
			<< "    on patch " << this->patch().name()
			<< " of field " << this->dimensionedInternalField().name()
			<< " in file " << this->dimensionedInternalField().objectPath()
			<< exit(FatalError);
	}

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::timeVaryingUniformTotalPressureFvPatchScalarField::updateCoeffs()
{
	updateCoeffs(lookupPatchField<volVectorField, vector>(UName_));
}


void tnbLib::timeVaryingUniformTotalPressureFvPatchScalarField::
write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	if (UName_ != "U")
	{
		os.writeKeyword("U") << UName_ << token::END_STATEMENT << nl;
	}
	if (phiName_ != "phi")
	{
		os.writeKeyword("phi") << phiName_ << token::END_STATEMENT << nl;
	}
	os.writeKeyword("rho") << rhoName_ << token::END_STATEMENT << nl;
	os.writeKeyword("psi") << psiName_ << token::END_STATEMENT << nl;
	os.writeKeyword("gamma") << gamma_ << token::END_STATEMENT << nl;
	os.writeKeyword("p0") << p0_ << token::END_STATEMENT << nl;
	timeSeries_.write(os);
	writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		timeVaryingUniformTotalPressureFvPatchScalarField
	);
}

// ************************************************************************* //
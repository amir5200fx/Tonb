#include <totalTemperatureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	UName_("U"),
	phiName_("phi"),
	psiName_("psi"),
	gamma_(0.0),
	T0_(p.size(), 0.0)
{}


tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const totalTemperatureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_),
	T0_(ptf.T0_, mapper)
{}


tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	psiName_(dict.lookupOrDefault<word>("psi", "psi")),
	gamma_(readScalar(dict.lookup("gamma"))),
	T0_("T0", dict, p.size())
{
	if (dict.found("value"))
	{
		fvPatchScalarField::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchScalarField::operator=(T0_);
	}
}


tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const totalTemperatureFvPatchScalarField& tppsf
)
	:
	fixedValueFvPatchScalarField(tppsf),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	T0_(tppsf.T0_)
{}


tnbLib::totalTemperatureFvPatchScalarField::totalTemperatureFvPatchScalarField
(
	const totalTemperatureFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(tppsf, iF),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	T0_(tppsf.T0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::totalTemperatureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchScalarField::autoMap(m);
	T0_.autoMap(m);
}


void tnbLib::totalTemperatureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchScalarField::rmap(ptf, addr);

	const totalTemperatureFvPatchScalarField& tiptf =
		refCast<const totalTemperatureFvPatchScalarField>(ptf);

	T0_.rmap(tiptf.T0_, addr);
}


void tnbLib::totalTemperatureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchVectorField& Up =
		lookupPatchField<volVectorField, vector>(UName_);

	const fvsPatchScalarField& phip =
		lookupPatchField<surfaceScalarField, scalar>(phiName_);

	const fvPatchScalarField& psip =
		lookupPatchField<volScalarField, scalar>(psiName_);

	scalar gM1ByG = (gamma_ - 1.0) / gamma_;

	operator==
		(
			T0_ / (1.0 + 0.5*psip*gM1ByG*(1.0 - pos(phip))*magSqr(Up))
			);

	fixedValueFvPatchScalarField::updateCoeffs();
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::totalTemperatureFvPatchScalarField::snGrad() const
{
	return tmp<scalarField>
		(
			new scalarField(this->size(), 0.0)
			);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::totalTemperatureFvPatchScalarField::gradientInternalCoeffs() const
{
	return tmp<scalarField>
		(
			new scalarField(this->size(), 0.0)
			);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::totalTemperatureFvPatchScalarField::gradientBoundaryCoeffs() const
{
	return tmp<scalarField>
		(
			new scalarField(this->size(), 0.0)
			);
}


void tnbLib::totalTemperatureFvPatchScalarField::write(Ostream& os) const
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
	if (psiName_ != "psi")
	{
		os.writeKeyword("psi") << psiName_ << token::END_STATEMENT << nl;
	}
	os.writeKeyword("gamma") << gamma_ << token::END_STATEMENT << nl;
	T0_.writeEntry("T0", os);
	writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		totalTemperatureFvPatchScalarField
	);
}

// ************************************************************************* //
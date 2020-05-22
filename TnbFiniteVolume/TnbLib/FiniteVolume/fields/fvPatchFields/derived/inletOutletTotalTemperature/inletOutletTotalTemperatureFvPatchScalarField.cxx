#include <inletOutletTotalTemperatureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF),
	UName_("U"),
	phiName_("phi"),
	psiName_("psi"),
	gamma_(0.0),
	T0_(p.size(), 0.0)
{
	this->refValue() = pTraits<scalar>::zero;
	this->refGrad() = pTraits<scalar>::zero;
	this->valueFraction() = 0.0;
}


tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const inletOutletTotalTemperatureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	phiName_(ptf.phiName_),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_),
	T0_(ptf.T0_, mapper)
{}


tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	psiName_(dict.lookupOrDefault<word>("psi", "psi")),
	gamma_(readScalar(dict.lookup("gamma"))),
	T0_("T0", dict, p.size())
{
	this->refValue() = pTraits<scalar>::zero;
	if (dict.found("value"))
	{
		fvPatchField<scalar>::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		fvPatchField<scalar>::operator=(T0_);
	}

	this->refGrad() = pTraits<scalar>::zero;
	this->valueFraction() = 0.0;
}


tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const inletOutletTotalTemperatureFvPatchScalarField& tppsf
)
	:
	mixedFvPatchScalarField(tppsf),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	T0_(tppsf.T0_)
{}


tnbLib::inletOutletTotalTemperatureFvPatchScalarField::
inletOutletTotalTemperatureFvPatchScalarField
(
	const inletOutletTotalTemperatureFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(tppsf, iF),
	UName_(tppsf.UName_),
	phiName_(tppsf.phiName_),
	psiName_(tppsf.psiName_),
	gamma_(tppsf.gamma_),
	T0_(tppsf.T0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::inletOutletTotalTemperatureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	mixedFvPatchScalarField::autoMap(m);
	T0_.autoMap(m);
}


void tnbLib::inletOutletTotalTemperatureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	mixedFvPatchScalarField::rmap(ptf, addr);

	const inletOutletTotalTemperatureFvPatchScalarField& tiptf =
		refCast<const inletOutletTotalTemperatureFvPatchScalarField>(ptf);

	T0_.rmap(tiptf.T0_, addr);
}


void tnbLib::inletOutletTotalTemperatureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchVectorField& Up =
		lookupPatchField<volVectorField, vector>(UName_);

	const fvsPatchField<scalar>& phip =
		lookupPatchField<surfaceScalarField, scalar>(phiName_);

	const fvPatchField<scalar>& psip =
		lookupPatchField<volScalarField, scalar>(psiName_);

	scalar gM1ByG = (gamma_ - 1.0) / gamma_;

	this->refValue() =
		T0_ / (1.0 + 0.5*psip*gM1ByG*(1.0 - pos(phip))*magSqr(Up));
	this->valueFraction() = 1.0 - pos(phip);

	mixedFvPatchScalarField::updateCoeffs();
}


void tnbLib::inletOutletTotalTemperatureFvPatchScalarField::write(Ostream& os)
const
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
	if (phiName_ != "psi")
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
		inletOutletTotalTemperatureFvPatchScalarField
	);
}

// ************************************************************************* //
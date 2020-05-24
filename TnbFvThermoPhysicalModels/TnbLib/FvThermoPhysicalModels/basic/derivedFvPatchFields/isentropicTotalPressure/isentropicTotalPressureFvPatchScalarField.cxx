#include <isentropicTotalPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <basicThermo.hxx>
#include <isentropicTotalTemperatureFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::isentropicTotalPressureFvPatchScalarField::
isentropicTotalPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	UName_("U"),
	TName_("T"),
	p0_(p.size(), 0.0)
{}


tnbLib::isentropicTotalPressureFvPatchScalarField::
isentropicTotalPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF),
	UName_(dict.lookupOrDefault<word>("U", "U")),
	TName_(dict.lookupOrDefault<word>("T", "T")),
	p0_("p0", dict, p.size())
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


tnbLib::isentropicTotalPressureFvPatchScalarField::
isentropicTotalPressureFvPatchScalarField
(
	const isentropicTotalPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	UName_(ptf.UName_),
	TName_(ptf.TName_),
	p0_(ptf.p0_, mapper)
{}


tnbLib::isentropicTotalPressureFvPatchScalarField::
isentropicTotalPressureFvPatchScalarField
(
	const isentropicTotalPressureFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchScalarField(ptf),
	UName_(ptf.UName_),
	TName_(ptf.TName_),
	p0_(ptf.p0_)
{}


tnbLib::isentropicTotalPressureFvPatchScalarField::
isentropicTotalPressureFvPatchScalarField
(
	const isentropicTotalPressureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(ptf, iF),
	UName_(ptf.UName_),
	TName_(ptf.TName_),
	p0_(ptf.p0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::isentropicTotalPressureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchScalarField::autoMap(m);
	p0_.autoMap(m);
}


void tnbLib::isentropicTotalPressureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchScalarField::rmap(ptf, addr);

	const isentropicTotalPressureFvPatchScalarField& tiptf =
		refCast<const isentropicTotalPressureFvPatchScalarField>(ptf);

	p0_.rmap(tiptf.p0_, addr);
}


void tnbLib::isentropicTotalPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// Get velocity
	const fvPatchVectorField& U =
		patch().lookupPatchField<volVectorField, scalar>(UName_);

	// Get temperature
	const fvPatchScalarField& T =
		patch().lookupPatchField<volScalarField, scalar>(TName_);

	const basicThermo& thermo =
		db().lookupObject<basicThermo>("thermophysicalProperties");

	scalarField Cp = thermo.Cp(T, patch().index());
	scalarField Cv = thermo.Cv(T, patch().index());

	scalarField gamma = Cp / Cv;
	scalarField R = Cp - Cv;

	scalarField Ma = -(patch().nf() & U) / sqrt(gamma*R*T);

	scalarField a = 1 + 0.5*(gamma - 1)*sqr(Ma);

	operator==(p0_*pow(a, -gamma / (gamma - 1)));

	fixedValueFvPatchScalarField::updateCoeffs();
}

void tnbLib::isentropicTotalPressureFvPatchScalarField::updateCoeffs
(
	const vectorField& Up
)
{
	updateCoeffs();
}


void tnbLib::isentropicTotalPressureFvPatchScalarField::write
(
	Ostream& os
) const
{
	fixedValueFvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "T", "T", TName_);
	p0_.writeEntry("p0", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	makePatchTypeField
	(
		fvPatchScalarField,
		isentropicTotalPressureFvPatchScalarField
	);

} // End namespace tnbLib


// ************************************************************************* //
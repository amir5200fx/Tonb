#include <isentropicTotalTemperatureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <basicThermo.hxx>
#include <isentropicTotalPressureFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::isentropicTotalTemperatureFvPatchScalarField::
isentropicTotalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	pName_("p"),
	T0_(p.size(), 0.0)
{}


tnbLib::isentropicTotalTemperatureFvPatchScalarField::
isentropicTotalTemperatureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF),
	pName_(dict.lookupOrDefault<word>("p", "p")),
	T0_("T0", dict, p.size())
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
		fvPatchField<scalar>::operator=(T0_);
	}
}


tnbLib::isentropicTotalTemperatureFvPatchScalarField::
isentropicTotalTemperatureFvPatchScalarField
(
	const isentropicTotalTemperatureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	pName_(ptf.pName_),
	T0_(ptf.T0_, mapper)
{}


tnbLib::isentropicTotalTemperatureFvPatchScalarField::
isentropicTotalTemperatureFvPatchScalarField
(
	const isentropicTotalTemperatureFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchScalarField(ptf),
	pName_(ptf.pName_),
	T0_(ptf.T0_)
{}


tnbLib::isentropicTotalTemperatureFvPatchScalarField::
isentropicTotalTemperatureFvPatchScalarField
(
	const isentropicTotalTemperatureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(ptf, iF),
	pName_(ptf.pName_),
	T0_(ptf.T0_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::isentropicTotalTemperatureFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchScalarField::autoMap(m);
	T0_.autoMap(m);
}


void tnbLib::isentropicTotalTemperatureFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchScalarField::rmap(ptf, addr);

	const isentropicTotalTemperatureFvPatchScalarField& tiptf =
		refCast<const isentropicTotalTemperatureFvPatchScalarField>(ptf);

	T0_.rmap(tiptf.T0_, addr);
}


void tnbLib::isentropicTotalTemperatureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// Get pressure and temperature
	const scalarField& T = *this;

	const fvPatchScalarField& pp =
		patch().lookupPatchField<volScalarField, scalar>(pName_);

	const isentropicTotalPressureFvPatchScalarField& p =
		refCast<const isentropicTotalPressureFvPatchScalarField>(pp);

	const basicThermo& thermo =
		db().lookupObject<basicThermo>("thermophysicalProperties");

	scalarField gamma =
		thermo.Cp(T, patch().index()) / thermo.Cv(T, patch().index());

	operator==(T0_*pow(p / p.p0(), (gamma - 1) / gamma));

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::isentropicTotalTemperatureFvPatchScalarField::updateCoeffs
(
	const vectorField& Up
)
{
	updateCoeffs();
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::isentropicTotalTemperatureFvPatchScalarField::snGrad() const
{
	return tmp<scalarField>
		(
			new scalarField(this->size(), 0.0)
			);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::isentropicTotalTemperatureFvPatchScalarField::
gradientInternalCoeffs() const
{
	return tmp<scalarField>
		(
			new scalarField(this->size(), 0.0)
			);
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::isentropicTotalTemperatureFvPatchScalarField::
gradientBoundaryCoeffs() const
{
	return tmp<scalarField>
		(
			new scalarField(this->size(), 0.0)
			);
}


void tnbLib::isentropicTotalTemperatureFvPatchScalarField::write
(
	Ostream& os
) const
{
	fixedValueFvPatchScalarField::write(os);
	writeEntryIfDifferent<word>(os, "p", "p", pName_);
	T0_.writeEntry("T0", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	makePatchTypeField
	(
		fvPatchScalarField,
		isentropicTotalTemperatureFvPatchScalarField
	);

} // End namespace tnbLib


// ************************************************************************* //
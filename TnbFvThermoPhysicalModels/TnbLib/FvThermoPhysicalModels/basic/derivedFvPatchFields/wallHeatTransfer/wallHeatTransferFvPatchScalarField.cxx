#include <wallHeatTransferFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF),
	Tinf_(p.size(), 0.0),
	alphaWall_(p.size(), 0.0)
{
	refValue() = 0.0;
	refGrad() = 0.0;
	valueFraction() = 0.0;
}


tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const wallHeatTransferFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper),
	Tinf_(ptf.Tinf_, mapper),
	alphaWall_(ptf.alphaWall_, mapper)
{}


tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF),
	Tinf_("Tinf", dict, p.size()),
	alphaWall_("alphaWall", dict, p.size())
{
	refValue() = Tinf_;
	refGrad() = 0.0;
	valueFraction() = 0.0;

	if (dict.found("value"))
	{
		fvPatchField<scalar>::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		evaluate();
	}
}


tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const wallHeatTransferFvPatchScalarField& tppsf
)
	:
	mixedFvPatchScalarField(tppsf),
	Tinf_(tppsf.Tinf_),
	alphaWall_(tppsf.alphaWall_)
{}


tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const wallHeatTransferFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(tppsf, iF),
	Tinf_(tppsf.Tinf_),
	alphaWall_(tppsf.alphaWall_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::wallHeatTransferFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	scalarField::autoMap(m);
	Tinf_.autoMap(m);
	alphaWall_.autoMap(m);
}


void tnbLib::wallHeatTransferFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	mixedFvPatchScalarField::rmap(ptf, addr);

	const wallHeatTransferFvPatchScalarField& tiptf =
		refCast<const wallHeatTransferFvPatchScalarField>(ptf);

	Tinf_.rmap(tiptf.Tinf_, addr);
	alphaWall_.rmap(tiptf.alphaWall_, addr);
}


void tnbLib::wallHeatTransferFvPatchScalarField::updateCoeffs()
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

	const scalarField& Tw = thermo.T().boundaryField()[patchi];
	scalarField Cpw = thermo.Cp(Tw, patchi);

	valueFraction() =
		1.0 /
		(
			1.0
			+ Cpw * thermo.alpha().boundaryField()[patchi]
			* patch().deltaCoeffs() / alphaWall_
			);

	mixedFvPatchScalarField::updateCoeffs();
}


void tnbLib::wallHeatTransferFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	Tinf_.writeEntry("Tinf", os);
	alphaWall_.writeEntry("alphaWall", os);
	writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField(fvPatchScalarField, wallHeatTransferFvPatchScalarField);
}

// ************************************************************************* //
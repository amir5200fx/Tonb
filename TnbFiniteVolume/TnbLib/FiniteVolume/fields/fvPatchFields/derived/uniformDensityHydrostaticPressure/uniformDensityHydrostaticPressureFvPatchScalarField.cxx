#include <uniformDensityHydrostaticPressureFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	rho_(0.0),
	pRefValue_(0.0),
	pRefPoint_(vector::zero)
{}


tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF),
	rho_(readScalar(dict.lookup("rho"))),
	pRefValue_(readScalar(dict.lookup("pRefValue"))),
	pRefPoint_(dict.lookup("pRefPoint"))
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
		// Evaluation not allowed here since g may not be available
		// Bug fix, HJ, 19/May/2011
		fvPatchField<scalar>::operator=(patchInternalField());
		//         evaluate();
	}
}


tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const uniformDensityHydrostaticPressureFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	rho_(ptf.rho_),
	pRefValue_(ptf.pRefValue_),
	pRefPoint_(ptf.pRefPoint_)
{}


tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const uniformDensityHydrostaticPressureFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchScalarField(ptf),
	rho_(ptf.rho_),
	pRefValue_(ptf.pRefValue_),
	pRefPoint_(ptf.pRefPoint_)
{}


tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::
uniformDensityHydrostaticPressureFvPatchScalarField
(
	const uniformDensityHydrostaticPressureFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(ptf, iF),
	rho_(ptf.rho_),
	pRefValue_(ptf.pRefValue_),
	pRefPoint_(ptf.pRefPoint_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const uniformDimensionedVectorField& g =
		db().lookupObject<uniformDimensionedVectorField>("g");

	operator==
		(
			pRefValue_
			+ rho_ * ((g.value() & patch().Cf()) - (g.value() & pRefPoint_))
			);

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::uniformDensityHydrostaticPressureFvPatchScalarField::write
(
	Ostream& os
) const
{
	fvPatchScalarField::write(os);
	os.writeKeyword("rho") << rho_ << token::END_STATEMENT << nl;
	os.writeKeyword("pRefValue") << pRefValue_ << token::END_STATEMENT << nl;
	os.writeKeyword("pRefPoint") << pRefPoint_ << token::END_STATEMENT << nl;
	writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		uniformDensityHydrostaticPressureFvPatchScalarField
	);
}

// ************************************************************************* //
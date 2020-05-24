#include <fixedInternalEnergyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	fixedInternalEnergyFvPatchScalarField::fixedInternalEnergyFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		fixedValueFvPatchScalarField(p, iF)
	{}


	fixedInternalEnergyFvPatchScalarField::fixedInternalEnergyFvPatchScalarField
	(
		const fixedInternalEnergyFvPatchScalarField& ptf,
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fixedValueFvPatchScalarField(ptf, p, iF, mapper)
	{}


	fixedInternalEnergyFvPatchScalarField::fixedInternalEnergyFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const dictionary& dict
	)
		:
		fixedValueFvPatchScalarField(p, iF, dict)
	{}


	fixedInternalEnergyFvPatchScalarField::fixedInternalEnergyFvPatchScalarField
	(
		const fixedInternalEnergyFvPatchScalarField& tppsf
	)
		:
		fixedValueFvPatchScalarField(tppsf)
	{}


	fixedInternalEnergyFvPatchScalarField::fixedInternalEnergyFvPatchScalarField
	(
		const fixedInternalEnergyFvPatchScalarField& tppsf,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		fixedValueFvPatchScalarField(tppsf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void fixedInternalEnergyFvPatchScalarField::updateCoeffs()
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

		fvPatchScalarField& Tw =
			const_cast<fvPatchScalarField&>(thermo.T().boundaryField()[patchi]);
		Tw.evaluate();
		operator==(thermo.e(Tw, patchi));

		fixedValueFvPatchScalarField::updateCoeffs();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField(fvPatchScalarField, fixedInternalEnergyFvPatchScalarField);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
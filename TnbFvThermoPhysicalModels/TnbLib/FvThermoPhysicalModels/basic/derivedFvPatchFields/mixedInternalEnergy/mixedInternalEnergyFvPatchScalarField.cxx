#include <mixedInternalEnergyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	mixedInternalEnergyFvPatchScalarField::mixedInternalEnergyFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		mixedFvPatchScalarField(p, iF)
	{
		valueFraction() = 0.0;
		refValue() = 0.0;
		refGrad() = 0.0;
	}


	mixedInternalEnergyFvPatchScalarField::mixedInternalEnergyFvPatchScalarField
	(
		const mixedInternalEnergyFvPatchScalarField& ptf,
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		mixedFvPatchScalarField(ptf, p, iF, mapper)
	{}


	mixedInternalEnergyFvPatchScalarField::mixedInternalEnergyFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const dictionary& dict
	)
		:
		mixedFvPatchScalarField(p, iF, dict)
	{}


	mixedInternalEnergyFvPatchScalarField::mixedInternalEnergyFvPatchScalarField
	(
		const mixedInternalEnergyFvPatchScalarField& tppsf
	)
		:
		mixedFvPatchScalarField(tppsf)
	{}


	mixedInternalEnergyFvPatchScalarField::mixedInternalEnergyFvPatchScalarField
	(
		const mixedInternalEnergyFvPatchScalarField& tppsf,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		mixedFvPatchScalarField(tppsf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void mixedInternalEnergyFvPatchScalarField::updateCoeffs()
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

		mixedFvPatchScalarField& Tw = refCast<mixedFvPatchScalarField>
			(
				const_cast<fvPatchScalarField&>(thermo.T().boundaryField()[patchi])
				);

		Tw.evaluate();

		valueFraction() = Tw.valueFraction();
		refValue() = thermo.e(Tw.refValue(), patchi);
		refGrad() = thermo.Cv(Tw, patchi)*Tw.refGrad()
			+ patch().deltaCoeffs()*
			(
				thermo.e(Tw, patchi)
				- thermo.e(Tw, patch().faceCells())
				);

		mixedFvPatchScalarField::updateCoeffs();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField(fvPatchScalarField, mixedInternalEnergyFvPatchScalarField);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
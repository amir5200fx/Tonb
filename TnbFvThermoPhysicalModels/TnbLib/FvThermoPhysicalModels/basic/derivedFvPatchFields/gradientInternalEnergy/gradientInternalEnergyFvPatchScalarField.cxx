#include <gradientInternalEnergyFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <basicThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	gradientInternalEnergyFvPatchScalarField::
		gradientInternalEnergyFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		fixedGradientFvPatchScalarField(p, iF)
	{}


	gradientInternalEnergyFvPatchScalarField::
		gradientInternalEnergyFvPatchScalarField
		(
			const gradientInternalEnergyFvPatchScalarField& ptf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		fixedGradientFvPatchScalarField(ptf, p, iF, mapper)
	{}


	gradientInternalEnergyFvPatchScalarField::
		gradientInternalEnergyFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
		:
		fixedGradientFvPatchScalarField(p, iF, dict)
	{}


	gradientInternalEnergyFvPatchScalarField::
		gradientInternalEnergyFvPatchScalarField
		(
			const gradientInternalEnergyFvPatchScalarField& tppsf
		)
		:
		fixedGradientFvPatchScalarField(tppsf)
	{}


	gradientInternalEnergyFvPatchScalarField::
		gradientInternalEnergyFvPatchScalarField
		(
			const gradientInternalEnergyFvPatchScalarField& tppsf,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		fixedGradientFvPatchScalarField(tppsf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void gradientInternalEnergyFvPatchScalarField::updateCoeffs()
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

		gradient() = thermo.Cv(Tw, patchi)*Tw.snGrad()
			+ patch().deltaCoeffs()*
			(
				thermo.e(Tw, patchi)
				- thermo.e(Tw, patch().faceCells())
				);

		fixedGradientFvPatchScalarField::updateCoeffs();
	}


	void tnbLib::gradientInternalEnergyFvPatchScalarField::write(Ostream& os) const
	{
		fixedGradientFvPatchScalarField::write(os);
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		gradientInternalEnergyFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
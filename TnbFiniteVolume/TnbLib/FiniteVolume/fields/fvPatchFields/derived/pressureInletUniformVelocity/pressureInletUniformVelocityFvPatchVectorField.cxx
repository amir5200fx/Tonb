#include <pressureInletUniformVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	pressureInletUniformVelocityFvPatchVectorField::
		pressureInletUniformVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		pressureInletVelocityFvPatchVectorField(p, iF)
	{}


	pressureInletUniformVelocityFvPatchVectorField::
		pressureInletUniformVelocityFvPatchVectorField
		(
			const pressureInletUniformVelocityFvPatchVectorField& ptf,
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		pressureInletVelocityFvPatchVectorField(ptf, p, iF, mapper)
	{}


	pressureInletUniformVelocityFvPatchVectorField::
		pressureInletUniformVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const dictionary& dict
		)
		:
		pressureInletVelocityFvPatchVectorField(p, iF, dict)
	{}


	pressureInletUniformVelocityFvPatchVectorField::
		pressureInletUniformVelocityFvPatchVectorField
		(
			const pressureInletUniformVelocityFvPatchVectorField& pivpvf
		)
		:
		pressureInletVelocityFvPatchVectorField(pivpvf)
	{}


	pressureInletUniformVelocityFvPatchVectorField::
		pressureInletUniformVelocityFvPatchVectorField
		(
			const pressureInletUniformVelocityFvPatchVectorField& pivpvf,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		pressureInletVelocityFvPatchVectorField(pivpvf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void pressureInletUniformVelocityFvPatchVectorField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		pressureInletVelocityFvPatchVectorField::updateCoeffs();

		operator==(patch().nf()*gSum(patch().Sf() & *this) / gSum(patch().magSf()));
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	void pressureInletUniformVelocityFvPatchVectorField::operator=
		(
			const fvPatchField<vector>& pvf
			)
	{
		operator==(patch().nf()*gSum(patch().Sf() & pvf) / gSum(patch().magSf()));
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchVectorField,
		pressureInletUniformVelocityFvPatchVectorField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
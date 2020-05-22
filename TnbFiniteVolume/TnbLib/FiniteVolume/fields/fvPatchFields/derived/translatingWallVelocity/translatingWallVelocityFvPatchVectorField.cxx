#include <translatingWallVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	translatingWallVelocityFvPatchVectorField::
		translatingWallVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		fixedValueFvPatchVectorField(p, iF),
		U_(vector::zero)
	{}


	translatingWallVelocityFvPatchVectorField::
		translatingWallVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const dictionary& dict
		)
		:
		fixedValueFvPatchVectorField(p, iF),
		U_(dict.lookup("U"))
	{
		// Evaluate the wall velocity
		updateCoeffs();
	}


	translatingWallVelocityFvPatchVectorField::
		translatingWallVelocityFvPatchVectorField
		(
			const translatingWallVelocityFvPatchVectorField& ptf,
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		fixedValueFvPatchVectorField(ptf, p, iF, mapper),
		U_(ptf.U_)
	{}


	translatingWallVelocityFvPatchVectorField::
		translatingWallVelocityFvPatchVectorField
		(
			const translatingWallVelocityFvPatchVectorField& twvpvf
		)
		:
		fixedValueFvPatchVectorField(twvpvf),
		U_(twvpvf.U_)
	{}


	translatingWallVelocityFvPatchVectorField::
		translatingWallVelocityFvPatchVectorField
		(
			const translatingWallVelocityFvPatchVectorField& twvpvf,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		fixedValueFvPatchVectorField(twvpvf, iF),
		U_(twvpvf.U_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void translatingWallVelocityFvPatchVectorField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		// Remove the component of U normal to the wall in case the wall
		// is not flat
		vectorField n = patch().nf();
		vectorField::operator=(U_ - n * (n & U_));

		fixedValueFvPatchVectorField::updateCoeffs();
	}


	void translatingWallVelocityFvPatchVectorField::write(Ostream& os) const
	{
		fvPatchVectorField::write(os);
		os.writeKeyword("U") << U_ << token::END_STATEMENT << nl;
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchVectorField,
		translatingWallVelocityFvPatchVectorField
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
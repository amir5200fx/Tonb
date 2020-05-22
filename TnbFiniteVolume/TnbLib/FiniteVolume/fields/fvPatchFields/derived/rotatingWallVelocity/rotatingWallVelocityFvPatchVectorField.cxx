#include <rotatingWallVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	rotatingWallVelocityFvPatchVectorField::rotatingWallVelocityFvPatchVectorField
	(
		const fvPatch& p,
		const DimensionedField<vector, volMesh>& iF
	)
		:
		fixedValueFvPatchField<vector>(p, iF),
		origin_(vector::zero),
		axis_(vector::zero),
		omega_(0)
	{}


	rotatingWallVelocityFvPatchVectorField::rotatingWallVelocityFvPatchVectorField
	(
		const rotatingWallVelocityFvPatchVectorField& ptf,
		const fvPatch& p,
		const DimensionedField<vector, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fixedValueFvPatchField<vector>(ptf, p, iF, mapper),
		origin_(ptf.origin_),
		axis_(ptf.axis_),
		omega_(ptf.omega_)
	{}


	rotatingWallVelocityFvPatchVectorField::rotatingWallVelocityFvPatchVectorField
	(
		const fvPatch& p,
		const DimensionedField<vector, volMesh>& iF,
		const dictionary& dict
	)
		:
		fixedValueFvPatchField<vector>(p, iF),
		origin_(dict.lookup("origin")),
		axis_(dict.lookup("axis")),
		omega_(readScalar(dict.lookup("omega")))
	{
		// Evaluate the wall velocity
		updateCoeffs();
	}


	rotatingWallVelocityFvPatchVectorField::rotatingWallVelocityFvPatchVectorField
	(
		const rotatingWallVelocityFvPatchVectorField& pivpvf
	)
		:
		fixedValueFvPatchField<vector>(pivpvf),
		origin_(pivpvf.origin_),
		axis_(pivpvf.axis_),
		omega_(pivpvf.omega_)
	{}


	rotatingWallVelocityFvPatchVectorField::rotatingWallVelocityFvPatchVectorField
	(
		const rotatingWallVelocityFvPatchVectorField& pivpvf,
		const DimensionedField<vector, volMesh>& iF
	)
		:
		fixedValueFvPatchField<vector>(pivpvf, iF),
		origin_(pivpvf.origin_),
		axis_(pivpvf.axis_),
		omega_(pivpvf.omega_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void rotatingWallVelocityFvPatchVectorField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		// Calculate the rotating wall velocity from the specification of the motion
		vectorField Up = (-omega_)*((patch().Cf() - origin_) ^ (axis_ / mag(axis_)));

		// Remove the component of Up normal to the wall
		// just in case it is not exactly circular
		vectorField n = patch().nf();
		vectorField::operator=(Up - n * (n & Up));

		fixedValueFvPatchVectorField::updateCoeffs();
	}


	void rotatingWallVelocityFvPatchVectorField::write(Ostream& os) const
	{
		fvPatchVectorField::write(os);
		os.writeKeyword("origin") << origin_ << token::END_STATEMENT << nl;
		os.writeKeyword("axis") << axis_ << token::END_STATEMENT << nl;
		os.writeKeyword("omega") << omega_ << token::END_STATEMENT << nl;
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchVectorField,
		rotatingWallVelocityFvPatchVectorField
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
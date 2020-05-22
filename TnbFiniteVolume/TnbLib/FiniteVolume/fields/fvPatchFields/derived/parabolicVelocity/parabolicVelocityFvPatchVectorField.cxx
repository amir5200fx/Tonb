#include <parabolicVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	parabolicVelocityFvPatchVectorField::parabolicVelocityFvPatchVectorField
	(
		const fvPatch& p,
		const DimensionedField<vector, volMesh>& iF
	)
		:
		fixedValueFvPatchVectorField(p, iF),
		maxValue_(0),
		n_(1, 0, 0),
		y_(0, 1, 0)
	{}


	parabolicVelocityFvPatchVectorField::parabolicVelocityFvPatchVectorField
	(
		const parabolicVelocityFvPatchVectorField& ptf,
		const fvPatch& p,
		const DimensionedField<vector, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fixedValueFvPatchVectorField(ptf, p, iF, mapper),
		maxValue_(ptf.maxValue_),
		n_(ptf.n_),
		y_(ptf.y_)
	{}


	parabolicVelocityFvPatchVectorField::parabolicVelocityFvPatchVectorField
	(
		const fvPatch& p,
		const DimensionedField<vector, volMesh>& iF,
		const dictionary& dict
	)
		:
		fixedValueFvPatchVectorField(p, iF),
		maxValue_(readScalar(dict.lookup("maxValue"))),
		n_(dict.lookup("n")),
		y_(dict.lookup("y"))
	{
		if (mag(n_) < SMALL || mag(y_) < SMALL)
		{
			FatalErrorIn("parabolicVelocityFvPatchVectorField(dict)")
				<< "n or y given with zero size not correct"
				<< abort(FatalError);
		}

		n_ /= mag(n_);
		y_ /= mag(y_);

		evaluate();
	}


	parabolicVelocityFvPatchVectorField::parabolicVelocityFvPatchVectorField
	(
		const parabolicVelocityFvPatchVectorField& fcvpvf,
		const DimensionedField<vector, volMesh>& iF
	)
		:
		fixedValueFvPatchVectorField(fcvpvf, iF),
		maxValue_(fcvpvf.maxValue_),
		n_(fcvpvf.n_),
		y_(fcvpvf.y_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void parabolicVelocityFvPatchVectorField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		// Get range and orientation
		boundBox bb(patch().patch().localPoints(), true);

		vector ctr = 0.5*(bb.max() + bb.min());

		const vectorField& c = patch().Cf();

		// Calculate local 1-D coordinate for the parabolic profile
		scalarField coord = 2 * ((c - ctr) & y_) / ((bb.max() - bb.min()) & y_);

		vectorField::operator=(n_*maxValue_*(1.0 - sqr(coord)));
	}


	// Write
	void parabolicVelocityFvPatchVectorField::write(Ostream& os) const
	{
		fvPatchVectorField::write(os);
		os.writeKeyword("maxValue")
			<< maxValue_ << token::END_STATEMENT << nl;
		os.writeKeyword("n")
			<< n_ << token::END_STATEMENT << nl;
		os.writeKeyword("y")
			<< y_ << token::END_STATEMENT << nl;
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField(fvPatchVectorField, parabolicVelocityFvPatchVectorField);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
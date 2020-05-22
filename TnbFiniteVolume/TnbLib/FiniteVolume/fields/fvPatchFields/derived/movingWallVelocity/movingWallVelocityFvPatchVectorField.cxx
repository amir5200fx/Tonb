#include <movingWallVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvcMeshPhi.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	movingWallVelocityFvPatchVectorField::movingWallVelocityFvPatchVectorField
	(
		const fvPatch& p,
		const DimensionedField<vector, volMesh>& iF
	)
		:
		fixedValueFvPatchVectorField(p, iF)
	{}


	movingWallVelocityFvPatchVectorField::movingWallVelocityFvPatchVectorField
	(
		const movingWallVelocityFvPatchVectorField& ptf,
		const fvPatch& p,
		const DimensionedField<vector, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fixedValueFvPatchVectorField(ptf, p, iF, mapper)
	{}


	movingWallVelocityFvPatchVectorField::movingWallVelocityFvPatchVectorField
	(
		const fvPatch& p,
		const DimensionedField<vector, volMesh>& iF,
		const dictionary& dict
	)
		:
		fixedValueFvPatchVectorField(p, iF)
	{
		fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
	}


	movingWallVelocityFvPatchVectorField::movingWallVelocityFvPatchVectorField
	(
		const movingWallVelocityFvPatchVectorField& pivpvf
	)
		:
		fixedValueFvPatchVectorField(pivpvf)
	{}


	movingWallVelocityFvPatchVectorField::movingWallVelocityFvPatchVectorField
	(
		const movingWallVelocityFvPatchVectorField& pivpvf,
		const DimensionedField<vector, volMesh>& iF
	)
		:
		fixedValueFvPatchVectorField(pivpvf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void movingWallVelocityFvPatchVectorField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		const fvMesh& mesh = dimensionedInternalField().mesh();

		if (mesh.changing())
		{
			const fvPatch& p = patch();
			const polyPatch& pp = p.patch();
			const pointField& oldPoints = mesh.oldPoints();

			vectorField oldFc(pp.size());

			forAll(oldFc, i)
			{
				oldFc[i] = pp[i].centre(oldPoints);
			}

			// Get wall-parallel mesh motion velocity from geometry
			vectorField Up =
				(pp.faceCentres() - oldFc) / mesh.time().deltaT().value();

			const volVectorField& U =
				mesh.lookupObject<volVectorField>
				(
					dimensionedInternalField().name()
					);

			scalarField phip =
				p.patchField<surfaceScalarField, scalar>(fvc::meshPhi(U));

			vectorField n = p.nf();
			const scalarField& magSf = p.magSf();
			scalarField Un = phip / (magSf + VSMALL);

			// Adjust for surface-normal mesh motion flux
			vectorField::operator=(Up + n * (Un - (n & Up)));
		}

		fixedValueFvPatchVectorField::updateCoeffs();
	}


	void movingWallVelocityFvPatchVectorField::write(Ostream& os) const
	{
		fvPatchVectorField::write(os);
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchVectorField,
		movingWallVelocityFvPatchVectorField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
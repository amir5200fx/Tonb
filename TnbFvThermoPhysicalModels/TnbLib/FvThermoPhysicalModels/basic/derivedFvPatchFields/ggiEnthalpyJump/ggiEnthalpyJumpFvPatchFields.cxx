#include <ggiEnthalpyJumpFvPatchFields.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makeTemplatePatchTypeField
	(
		fvPatchScalarField,
		ggiEnthalpyJumpFvPatchScalarField
	);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<>
void tnbLib::ggiEnthalpyJumpFvPatchField<tnbLib::scalar>::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	// Get access to relative and rotational velocity
	const word UrelName("Urel");
	const word UName("U");

	if
		(
			!this->db().objectRegistry::found(UrelName)
			|| !this->db().objectRegistry::found(UName)
			)
	{
		// Velocities not available, do not update
		InfoIn
		(
			"void gradientEnthalpyFvPatchScalarField::"
			"updateCoeffs(const vectorField& Up)"
		) << "Velocity fields " << UrelName << " or "
			<< UName << " not found.  "
			<< "Performing enthalpy value update" << endl;

		jump_ = 0;
	}
	else
	{
		const fvPatchVectorField& Urelp =
			lookupPatchField<volVectorField, vector>(UrelName);

		const fvPatchVectorField& Up =
			lookupPatchField<volVectorField, vector>(UName);

		if (rotating_)
		{
			jump_ =
				mag(Up.patchInternalField())*mag(Urelp.patchInternalField())
				- magSqr(Up.patchInternalField());
		}
		else
		{
			jump_ =
				mag(Up.patchNeighbourField())*mag(Urelp.patchNeighbourField())
				- magSqr(Up.patchNeighbourField());
		}
	}

	jumpGgiFvPatchField<scalar>::updateCoeffs();
}


// ************************************************************************* //
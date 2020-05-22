#include <fanFvPatchFields.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makeTemplatePatchTypeField(fvPatchScalarField, fanFvPatchScalarField);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

//- Specialisation of the jump-condition for the pressure
template<>
void tnbLib::fanFvPatchField<tnbLib::scalar>::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	jump_ = f_[0];

	if (f_.size() > 1)
	{
		const surfaceScalarField& phi =
			db().lookupObject<surfaceScalarField>("phi");

		const fvsPatchField<scalar>& phip =
			patch().patchField<surfaceScalarField, scalar>(phi);

		scalarField Un = max
		(
			scalarField::subField(phip, size() / 2)
			/ scalarField::subField(patch().magSf(), size() / 2),
			scalar(0)
		);

		if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
		{
			Un /=
				scalarField::subField
				(
					lookupPatchField<volScalarField, scalar>("rho"),
					size() / 2
				);
		}

		for (label i = 1; i < f_.size(); i++)
		{
			jump_ += f_[i] * pow(Un, i);
		}

		jump_ = max(jump_, scalar(0));
	}

	jumpCyclicFvPatchField<scalar>::updateCoeffs();
}


// ************************************************************************* //
#include <pressureNormalInletOutletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	pressureNormalInletOutletVelocityFvPatchVectorField::
		pressureNormalInletOutletVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		mixedFvPatchVectorField(p, iF),
		phiName_("phi"),
		rhoName_("rho")
	{
		refValue() = *this;
		refGrad() = vector::zero;
		valueFraction() = 0.0;
	}


	pressureNormalInletOutletVelocityFvPatchVectorField::
		pressureNormalInletOutletVelocityFvPatchVectorField
		(
			const pressureNormalInletOutletVelocityFvPatchVectorField& ptf,
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		mixedFvPatchVectorField(ptf, p, iF, mapper),
		phiName_(ptf.phiName_),
		rhoName_(ptf.rhoName_)
	{}


	pressureNormalInletOutletVelocityFvPatchVectorField::
		pressureNormalInletOutletVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const dictionary& dict
		)
		:
		mixedFvPatchVectorField(p, iF),
		phiName_(dict.lookupOrDefault<word>("phi", "phi")),
		rhoName_(dict.lookupOrDefault<word>("rho", "rho"))
	{
		fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
		refValue() = *this;
		refGrad() = vector::zero;
		valueFraction() = 0.0;
	}


	pressureNormalInletOutletVelocityFvPatchVectorField::
		pressureNormalInletOutletVelocityFvPatchVectorField
		(
			const pressureNormalInletOutletVelocityFvPatchVectorField& pivpvf
		)
		:
		mixedFvPatchVectorField(pivpvf),
		phiName_(pivpvf.phiName_),
		rhoName_(pivpvf.rhoName_)
	{}


	pressureNormalInletOutletVelocityFvPatchVectorField::
		pressureNormalInletOutletVelocityFvPatchVectorField
		(
			const pressureNormalInletOutletVelocityFvPatchVectorField& pivpvf,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		mixedFvPatchVectorField(pivpvf, iF),
		phiName_(pivpvf.phiName_),
		rhoName_(pivpvf.rhoName_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void pressureNormalInletOutletVelocityFvPatchVectorField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}


		if (!this->db().objectRegistry::found(phiName_))
		{
			// Flux not available, do not update
			InfoIn
			(
				"void pressureNormalInletOutletVelocityFvPatchVectorField::"
				"updateCoeffs()"
			) << "Flux field " << phiName_ << " not found.  "
				<< "Performing mixed update" << endl;

			mixedFvPatchVectorField::updateCoeffs();

			return;
		}

		const surfaceScalarField& phi =
			db().lookupObject<surfaceScalarField>(phiName_);

		const fvsPatchField<scalar>& phip =
			patch().patchField<surfaceScalarField, scalar>(phi);

		vectorField n = patch().nf();
		const Field<scalar>& magS = patch().magSf();

		if (phi.dimensions() == dimVelocity * dimArea)
		{
			refValue() = n * phip / magS;
		}
		else if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
		{
			if (!this->db().objectRegistry::found(rhoName_))
			{
				// Rho not available, do not update
				mixedFvPatchVectorField::updateCoeffs();

				return;
			}

			const fvPatchField<scalar>& rhop =
				lookupPatchField<volScalarField, scalar>(rhoName_);

			refValue() = n * phip / (rhop*magS);
		}
		else
		{
			FatalErrorIn
			(
				"pressureNormalInletOutletVelocityFvPatchVectorField::"
				"updateCoeffs()"
			) << "dimensions of phi are not correct"
				<< "\n    on patch " << this->patch().name()
				<< " of field " << this->dimensionedInternalField().name()
				<< " in file " << this->dimensionedInternalField().objectPath()
				<< exit(FatalError);
		}

		valueFraction() = 1.0 - pos(phip);

		mixedFvPatchVectorField::updateCoeffs();
	}


	void pressureNormalInletOutletVelocityFvPatchVectorField::
		write(Ostream& os) const
	{
		fvPatchVectorField::write(os);
		os.writeKeyword("phi") << phiName_ << token::END_STATEMENT << nl;
		os.writeKeyword("rho") << rhoName_ << token::END_STATEMENT << nl;
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	void pressureNormalInletOutletVelocityFvPatchVectorField::operator=
		(
			const fvPatchField<vector>& pvf
			)
	{
		fvPatchField<vector>::operator=
			(
				valueFraction()*(patch().nf()*(patch().nf() & pvf))
				+ (1 - valueFraction())*pvf
				);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchVectorField,
		pressureNormalInletOutletVelocityFvPatchVectorField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
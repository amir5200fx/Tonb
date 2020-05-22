#include <pressureDirectedInletOutletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	pressureDirectedInletOutletVelocityFvPatchVectorField::
		pressureDirectedInletOutletVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		mixedFvPatchVectorField(p, iF),
		phiName_("phi"),
		rhoName_("rho"),
		inletDir_(p.size())
	{
		refValue() = *this;
		refGrad() = vector::zero;
		valueFraction() = 0.0;
	}


	pressureDirectedInletOutletVelocityFvPatchVectorField::
		pressureDirectedInletOutletVelocityFvPatchVectorField
		(
			const pressureDirectedInletOutletVelocityFvPatchVectorField& ptf,
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		mixedFvPatchVectorField(ptf, p, iF, mapper),
		phiName_(ptf.phiName_),
		rhoName_(ptf.rhoName_),
		inletDir_(ptf.inletDir_, mapper)
	{}


	pressureDirectedInletOutletVelocityFvPatchVectorField::
		pressureDirectedInletOutletVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const dictionary& dict
		)
		:
		mixedFvPatchVectorField(p, iF),
		phiName_(dict.lookupOrDefault<word>("phi", "phi")),
		rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
		inletDir_("inletDirection", dict, p.size())
	{
		fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
		refValue() = *this;
		refGrad() = vector::zero;
		valueFraction() = 0.0;
	}


	pressureDirectedInletOutletVelocityFvPatchVectorField::
		pressureDirectedInletOutletVelocityFvPatchVectorField
		(
			const pressureDirectedInletOutletVelocityFvPatchVectorField& pivpvf
		)
		:
		mixedFvPatchVectorField(pivpvf),
		phiName_(pivpvf.phiName_),
		rhoName_(pivpvf.rhoName_),
		inletDir_(pivpvf.inletDir_)
	{}


	pressureDirectedInletOutletVelocityFvPatchVectorField::
		pressureDirectedInletOutletVelocityFvPatchVectorField
		(
			const pressureDirectedInletOutletVelocityFvPatchVectorField& pivpvf,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		mixedFvPatchVectorField(pivpvf, iF),
		phiName_(pivpvf.phiName_),
		rhoName_(pivpvf.rhoName_),
		inletDir_(pivpvf.inletDir_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void pressureDirectedInletOutletVelocityFvPatchVectorField::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		mixedFvPatchVectorField::autoMap(m);
		inletDir_.autoMap(m);
	}


	void pressureDirectedInletOutletVelocityFvPatchVectorField::rmap
	(
		const fvPatchVectorField& ptf,
		const labelList& addr
	)
	{
		mixedFvPatchVectorField::rmap(ptf, addr);

		const pressureDirectedInletOutletVelocityFvPatchVectorField& tiptf =
			refCast<const pressureDirectedInletOutletVelocityFvPatchVectorField>
			(ptf);

		inletDir_.rmap(tiptf.inletDir_, addr);
	}


	void pressureDirectedInletOutletVelocityFvPatchVectorField::updateCoeffs()
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
				"void pressureDirectedInletOutletVelocityFvPatchVectorField::"
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
		scalarField ndmagS = (n & inletDir_)*patch().magSf();

		if (phi.dimensions() == dimVelocity * dimArea)
		{
			refValue() = inletDir_ * phip / ndmagS;
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

			refValue() = inletDir_ * phip / (rhop*ndmagS);
		}
		else
		{
			FatalErrorIn
			(
				"pressureDirectedInletOutletVelocityFvPatchVectorField::"
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


	void pressureDirectedInletOutletVelocityFvPatchVectorField::
		write(Ostream& os) const
	{
		fvPatchVectorField::write(os);
		if (phiName_ != "phi")
		{
			os.writeKeyword("phi") << phiName_ << token::END_STATEMENT << nl;
		}
		if (rhoName_ != "rho")
		{
			os.writeKeyword("rho") << rhoName_ << token::END_STATEMENT << nl;
		}
		inletDir_.writeEntry("inletDirection", os);
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	void pressureDirectedInletOutletVelocityFvPatchVectorField::operator=
		(
			const fvPatchField<vector>& pvf
			)
	{
		fvPatchField<vector>::operator=
			(
				valueFraction()*(inletDir_*(inletDir_ & pvf))
				+ (1 - valueFraction())*pvf
				);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchVectorField,
		pressureDirectedInletOutletVelocityFvPatchVectorField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
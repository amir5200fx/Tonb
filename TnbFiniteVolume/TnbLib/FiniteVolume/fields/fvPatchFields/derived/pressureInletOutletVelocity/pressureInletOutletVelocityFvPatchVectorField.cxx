#include <pressureInletOutletVelocityFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvPatchFieldMapper.hxx>
#include <transformField.hxx>
#include <symmTransformField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	pressureInletOutletVelocityFvPatchVectorField::
		pressureInletOutletVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		directionMixedFvPatchVectorField(p, iF),
		phiName_("phi")
	{
		refValue() = vector::zero;
		refGrad() = vector::zero;
		valueFraction() = symmTensor::zero;
	}


	pressureInletOutletVelocityFvPatchVectorField::
		pressureInletOutletVelocityFvPatchVectorField
		(
			const pressureInletOutletVelocityFvPatchVectorField& ptf,
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		directionMixedFvPatchVectorField(ptf, p, iF, mapper),
		phiName_(ptf.phiName_)
	{
		if (ptf.tangentialVelocity_.size())
		{
			tangentialVelocity_ = mapper(ptf.tangentialVelocity_);
		}
	}


	pressureInletOutletVelocityFvPatchVectorField::
		pressureInletOutletVelocityFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const dictionary& dict
		)
		:
		directionMixedFvPatchVectorField(p, iF),
		phiName_(dict.lookupOrDefault<word>("phi", "phi"))
	{
		fvPatchVectorField::operator=(vectorField("value", dict, p.size()));

		if (dict.found("tangentialVelocity"))
		{
			setTangentialVelocity
			(
				vectorField("tangentialVelocity", dict, p.size())
			);
		}
		else
		{
			refValue() = vector::zero;
		}

		refGrad() = vector::zero;
		valueFraction() = symmTensor::zero;
	}


	pressureInletOutletVelocityFvPatchVectorField::
		pressureInletOutletVelocityFvPatchVectorField
		(
			const pressureInletOutletVelocityFvPatchVectorField& pivpvf
		)
		:
		directionMixedFvPatchVectorField(pivpvf),
		phiName_(pivpvf.phiName_),
		tangentialVelocity_(pivpvf.tangentialVelocity_)
	{}


	pressureInletOutletVelocityFvPatchVectorField::
		pressureInletOutletVelocityFvPatchVectorField
		(
			const pressureInletOutletVelocityFvPatchVectorField& pivpvf,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		directionMixedFvPatchVectorField(pivpvf, iF),
		phiName_(pivpvf.phiName_),
		tangentialVelocity_(pivpvf.tangentialVelocity_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void pressureInletOutletVelocityFvPatchVectorField::
		setTangentialVelocity(const vectorField& tangentialVelocity)
	{
		tangentialVelocity_ = tangentialVelocity;
		vectorField n = patch().nf();
		refValue() = tangentialVelocity_ - n * (n & tangentialVelocity_);
	}


	void pressureInletOutletVelocityFvPatchVectorField::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		directionMixedFvPatchVectorField::autoMap(m);
		if (tangentialVelocity_.size())
		{
			tangentialVelocity_.autoMap(m);
		}
	}


	void pressureInletOutletVelocityFvPatchVectorField::rmap
	(
		const fvPatchVectorField& ptf,
		const labelList& addr
	)
	{
		directionMixedFvPatchVectorField::rmap(ptf, addr);

		if (tangentialVelocity_.size())
		{
			const pressureInletOutletVelocityFvPatchVectorField& tiptf =
				refCast<const pressureInletOutletVelocityFvPatchVectorField>(ptf);

			tangentialVelocity_.rmap(tiptf.tangentialVelocity_, addr);
		}
	}


	void pressureInletOutletVelocityFvPatchVectorField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		if (this->db().objectRegistry::found(phiName_))
		{
			const fvsPatchField<scalar>& phip =
				lookupPatchField<surfaceScalarField, scalar>(phiName_);

			valueFraction() = neg(phip)*(I - sqr(patch().nf()));
		}
		else
		{
			InfoIn
			(
				"pressureInletOutletVelocityFvPatchVectorField::updateCoeffs()"
			) << "Cannot find phi.  Return" << endl;

			valueFraction() = symmTensor::one;
		}

		directionMixedFvPatchVectorField::updateCoeffs();
		directionMixedFvPatchVectorField::evaluate();
	}


	void pressureInletOutletVelocityFvPatchVectorField::write(Ostream& os) const
	{
		fvPatchVectorField::write(os);
		if (phiName_ != "phi")
		{
			os.writeKeyword("phi") << phiName_ << token::END_STATEMENT << nl;
		}
		if (tangentialVelocity_.size())
		{
			tangentialVelocity_.writeEntry("tangentialVelocity", os);
		}
		writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	void pressureInletOutletVelocityFvPatchVectorField::operator=
		(
			const fvPatchField<vector>& pvf
			)
	{
		vectorField normalValue = transform(valueFraction(), refValue());
		vectorField transformGradValue = transform(I - valueFraction(), pvf);
		fvPatchField<vector>::operator=(normalValue + transformGradValue);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchVectorField,
		pressureInletOutletVelocityFvPatchVectorField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
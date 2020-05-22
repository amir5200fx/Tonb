#include <surfaceNormalFixedValueFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	surfaceNormalFixedValueFvPatchVectorField::
		surfaceNormalFixedValueFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		fixedValueFvPatchVectorField(p, iF),
		refValue_(p.size(), 0)
	{}


	surfaceNormalFixedValueFvPatchVectorField::
		surfaceNormalFixedValueFvPatchVectorField
		(
			const surfaceNormalFixedValueFvPatchVectorField& ptf,
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		fixedValueFvPatchVectorField(ptf, p, iF, mapper),
		refValue_(ptf.refValue_, mapper)
	{}


	surfaceNormalFixedValueFvPatchVectorField::
		surfaceNormalFixedValueFvPatchVectorField
		(
			const fvPatch& p,
			const DimensionedField<vector, volMesh>& iF,
			const dictionary& dict
		)
		:
		fixedValueFvPatchVectorField(p, iF, dict),
		refValue_("refValue", dict, p.size())
	{}


	surfaceNormalFixedValueFvPatchVectorField::
		surfaceNormalFixedValueFvPatchVectorField
		(
			const surfaceNormalFixedValueFvPatchVectorField& pivpvf
		)
		:
		fixedValueFvPatchVectorField(pivpvf),
		refValue_(pivpvf.refValue_)
	{}


	surfaceNormalFixedValueFvPatchVectorField::
		surfaceNormalFixedValueFvPatchVectorField
		(
			const surfaceNormalFixedValueFvPatchVectorField& pivpvf,
			const DimensionedField<vector, volMesh>& iF
		)
		:
		fixedValueFvPatchVectorField(pivpvf, iF),
		refValue_(pivpvf.refValue_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void surfaceNormalFixedValueFvPatchVectorField::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		fixedValueFvPatchVectorField::autoMap(m);
		refValue_.autoMap(m);
	}


	void surfaceNormalFixedValueFvPatchVectorField::rmap
	(
		const fvPatchVectorField& ptf,
		const labelList& addr
	)
	{
		fixedValueFvPatchVectorField::rmap(ptf, addr);

		const surfaceNormalFixedValueFvPatchVectorField& tiptf =
			refCast<const surfaceNormalFixedValueFvPatchVectorField>(ptf);

		refValue_.rmap(tiptf.refValue_, addr);
	}


	void surfaceNormalFixedValueFvPatchVectorField::updateCoeffs()
	{
		if (updated())
		{
			return;
		}

		// Bug fix: update for moving mesh.  HJ, 15/Oct/2010
		operator==(refValue_*patch().nf());
	}


	void surfaceNormalFixedValueFvPatchVectorField::write(Ostream& os) const
	{
		fixedValueFvPatchVectorField::write(os);
		refValue_.writeEntry("refValue", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchVectorField,
		surfaceNormalFixedValueFvPatchVectorField
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
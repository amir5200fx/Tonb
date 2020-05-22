#include <timeVaryingFlowRateInletVelocityFvPatchVectorField.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <surfaceFields.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::timeVaryingFlowRateInletVelocityFvPatchVectorField::
timeVaryingFlowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	flowRateInletVelocityFvPatchVectorField(p, iF),
	timeSeries_()
{}


tnbLib::timeVaryingFlowRateInletVelocityFvPatchVectorField::
timeVaryingFlowRateInletVelocityFvPatchVectorField
(
	const timeVaryingFlowRateInletVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	flowRateInletVelocityFvPatchVectorField(ptf, p, iF, mapper),
	timeSeries_(ptf.timeSeries_)
{}


tnbLib::timeVaryingFlowRateInletVelocityFvPatchVectorField::
timeVaryingFlowRateInletVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	flowRateInletVelocityFvPatchVectorField(p, iF, dict),
	timeSeries_(dict)
{}


tnbLib::timeVaryingFlowRateInletVelocityFvPatchVectorField::
timeVaryingFlowRateInletVelocityFvPatchVectorField
(
	const timeVaryingFlowRateInletVelocityFvPatchVectorField& ptf
)
	:
	flowRateInletVelocityFvPatchVectorField(ptf),
	timeSeries_(ptf.timeSeries_)
{}


tnbLib::timeVaryingFlowRateInletVelocityFvPatchVectorField::
timeVaryingFlowRateInletVelocityFvPatchVectorField
(
	const timeVaryingFlowRateInletVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	flowRateInletVelocityFvPatchVectorField(ptf, iF),
	timeSeries_(ptf.timeSeries_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::timeVaryingFlowRateInletVelocityFvPatchVectorField::
updateCoeffs()
{
	if (updated())
	{
		return;
	}

	flowRate() = timeSeries_(this->db().time().timeOutputValue());
	flowRateInletVelocityFvPatchVectorField::updateCoeffs();
}


void tnbLib::timeVaryingFlowRateInletVelocityFvPatchVectorField::
write(Ostream& os) const
{
	flowRateInletVelocityFvPatchVectorField::write(os);
	timeSeries_.write(os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		timeVaryingFlowRateInletVelocityFvPatchVectorField
	);
}


// ************************************************************************* //
#include <alphatWallFunctionFvPatchScalarField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{
		namespace RASModels
		{

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			alphatWallFunctionFvPatchScalarField::
				alphatWallFunctionFvPatchScalarField
				(
					const fvPatch& p,
					const DimensionedField<scalar, volMesh>& iF
				)
				:
				fixedValueFvPatchScalarField(p, iF),
				mutName_("mut"),
				Prt_(0.85)
			{}


			alphatWallFunctionFvPatchScalarField::
				alphatWallFunctionFvPatchScalarField
				(
					const alphatWallFunctionFvPatchScalarField& ptf,
					const fvPatch& p,
					const DimensionedField<scalar, volMesh>& iF,
					const fvPatchFieldMapper& mapper
				)
				:
				fixedValueFvPatchScalarField(ptf, p, iF, mapper),
				mutName_(ptf.mutName_),
				Prt_(ptf.Prt_)
			{}


			alphatWallFunctionFvPatchScalarField::
				alphatWallFunctionFvPatchScalarField
				(
					const fvPatch& p,
					const DimensionedField<scalar, volMesh>& iF,
					const dictionary& dict
				)
				:
				fixedValueFvPatchScalarField(p, iF, dict),
				mutName_(dict.lookupOrDefault<word>("mut", "mut")),
				Prt_(dict.lookupOrDefault<scalar>("Prt", 0.85))
			{}


			alphatWallFunctionFvPatchScalarField::
				alphatWallFunctionFvPatchScalarField
				(
					const alphatWallFunctionFvPatchScalarField& awfpsf
				)
				:
				fixedValueFvPatchScalarField(awfpsf),
				mutName_(awfpsf.mutName_),
				Prt_(awfpsf.Prt_)
			{}


			alphatWallFunctionFvPatchScalarField::
				alphatWallFunctionFvPatchScalarField
				(
					const alphatWallFunctionFvPatchScalarField& awfpsf,
					const DimensionedField<scalar, volMesh>& iF
				)
				:
				fixedValueFvPatchScalarField(awfpsf, iF),
				mutName_(awfpsf.mutName_),
				Prt_(awfpsf.Prt_)
			{}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

			void alphatWallFunctionFvPatchScalarField::updateCoeffs()
			{
				if (updated())
				{
					return;
				}

				const scalarField& mutw =
					lookupPatchField<volScalarField, scalar>(mutName_);

				operator==(mutw / Prt_);

				fixedValueFvPatchScalarField::updateCoeffs();
			}


			void alphatWallFunctionFvPatchScalarField::write(Ostream& os) const
			{
				fvPatchField<scalar>::write(os);
				writeEntryIfDifferent<word>(os, "mut", "mut", mutName_);
				os.writeKeyword("Prt") << Prt_ << token::END_STATEMENT << nl;
				writeEntry("value", os);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			makePatchTypeField(fvPatchScalarField, alphatWallFunctionFvPatchScalarField);

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //
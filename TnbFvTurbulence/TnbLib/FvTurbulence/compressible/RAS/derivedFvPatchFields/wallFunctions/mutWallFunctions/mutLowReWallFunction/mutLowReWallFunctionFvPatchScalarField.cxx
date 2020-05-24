#include <mutLowReWallFunctionFvPatchScalarField.hxx>

#include <compRASModel.hxx>
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

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			tmp<scalarField> mutLowReWallFunctionFvPatchScalarField::calcMut() const
			{
				return tmp<scalarField>(new scalarField(patch().size(), 0.0));
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			mutLowReWallFunctionFvPatchScalarField::mutLowReWallFunctionFvPatchScalarField
			(
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF
			)
				:
				mutWallFunctionFvPatchScalarField(p, iF)
			{}


			mutLowReWallFunctionFvPatchScalarField::mutLowReWallFunctionFvPatchScalarField
			(
				const mutLowReWallFunctionFvPatchScalarField& ptf,
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF,
				const fvPatchFieldMapper& mapper
			)
				:
				mutWallFunctionFvPatchScalarField(ptf, p, iF, mapper)
			{}


			mutLowReWallFunctionFvPatchScalarField::mutLowReWallFunctionFvPatchScalarField
			(
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF,
				const dictionary& dict
			)
				:
				mutWallFunctionFvPatchScalarField(p, iF, dict)
			{}


			mutLowReWallFunctionFvPatchScalarField::mutLowReWallFunctionFvPatchScalarField
			(
				const mutLowReWallFunctionFvPatchScalarField& mlrwfpsf
			)
				:
				mutWallFunctionFvPatchScalarField(mlrwfpsf)
			{}


			mutLowReWallFunctionFvPatchScalarField::mutLowReWallFunctionFvPatchScalarField
			(
				const mutLowReWallFunctionFvPatchScalarField& mlrwfpsf,
				const DimensionedField<scalar, volMesh>& iF
			)
				:
				mutWallFunctionFvPatchScalarField(mlrwfpsf, iF)
			{}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			makePatchTypeField
			(
				fvPatchScalarField,
				mutLowReWallFunctionFvPatchScalarField
			);

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //
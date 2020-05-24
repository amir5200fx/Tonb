#include <mutSptAlmStdWFunFvPatchScalarField.hxx>

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

			tmp<scalarField>
				mutSpalartAllmarasStandardWallFunctionFvPatchScalarField::calcYPlus
				(
					const scalarField& magUp
				) const
			{
				const label patchI = patch().index();

				const RASModel& rasModel = db().lookupObject<RASModel>("RASProperties");
				const scalarField& y = rasModel.y()[patchI];
				const fvPatchScalarField& rhow = rasModel.rho().boundaryField()[patchI];
				const fvPatchScalarField& muw = rasModel.mu().boundaryField()[patchI];

				tmp<scalarField> tyPlus(new scalarField(patch().size(), 0.0));
				scalarField& yPlus = tyPlus();

				forAll(yPlus, faceI)
				{
					scalar kappaRe = kappa_ * magUp[faceI] * y[faceI] / (muw[faceI] / rhow[faceI]);

					scalar yp = yPlusLam_;
					scalar ryPlusLam = 1.0 / yp;

					int iter = 0;
					scalar yPlusLast = 0.0;

					do
					{
						yPlusLast = yp;
						yp = (kappaRe + yp) / (1.0 + log(E_*yp));

					} while (mag(ryPlusLam*(yp - yPlusLast)) > 0.01 && ++iter < 10);

					yPlus[faceI] = max(0.0, yp);
				}

				return tyPlus;
			}


			tmp<scalarField>
				mutSpalartAllmarasStandardWallFunctionFvPatchScalarField::calcMut() const
			{
				const label patchI = patch().index();

				const RASModel& rasModel = db().lookupObject<RASModel>("RASProperties");
				const fvPatchVectorField& Uw = rasModel.U().boundaryField()[patchI];
				const scalarField magUp = mag(Uw.patchInternalField() - Uw);
				const fvPatchScalarField& muw = rasModel.mu().boundaryField()[patchI];

				tmp<scalarField> tyPlus = calcYPlus(magUp);
				scalarField& yPlus = tyPlus();

				tmp<scalarField> tmutw(new scalarField(patch().size(), 0.0));
				scalarField& mutw = tmutw();

				forAll(yPlus, faceI)
				{
					if (yPlus[faceI] > yPlusLam_)
					{
						mutw[faceI] =
							muw[faceI] * (yPlus[faceI] * kappa_ / log(E_*yPlus[faceI]) - 1.0);
					}
				}

				return tmutw;
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			mutSpalartAllmarasStandardWallFunctionFvPatchScalarField::
				mutSpalartAllmarasStandardWallFunctionFvPatchScalarField
				(
					const fvPatch& p,
					const DimensionedField<scalar, volMesh>& iF
				)
				:
				mutWallFunctionFvPatchScalarField(p, iF)
			{}


			mutSpalartAllmarasStandardWallFunctionFvPatchScalarField::
				mutSpalartAllmarasStandardWallFunctionFvPatchScalarField
				(
					const mutSpalartAllmarasStandardWallFunctionFvPatchScalarField& ptf,
					const fvPatch& p,
					const DimensionedField<scalar, volMesh>& iF,
					const fvPatchFieldMapper& mapper
				)
				:
				mutWallFunctionFvPatchScalarField(ptf, p, iF, mapper)
			{}


			mutSpalartAllmarasStandardWallFunctionFvPatchScalarField::
				mutSpalartAllmarasStandardWallFunctionFvPatchScalarField
				(
					const fvPatch& p,
					const DimensionedField<scalar, volMesh>& iF,
					const dictionary& dict
				)
				:
				mutWallFunctionFvPatchScalarField(p, iF, dict)
			{}


			mutSpalartAllmarasStandardWallFunctionFvPatchScalarField::
				mutSpalartAllmarasStandardWallFunctionFvPatchScalarField
				(
					const mutSpalartAllmarasStandardWallFunctionFvPatchScalarField& sawfpsf
				)
				:
				mutWallFunctionFvPatchScalarField(sawfpsf)
			{}


			mutSpalartAllmarasStandardWallFunctionFvPatchScalarField::
				mutSpalartAllmarasStandardWallFunctionFvPatchScalarField
				(
					const mutSpalartAllmarasStandardWallFunctionFvPatchScalarField& sawfpsf,
					const DimensionedField<scalar, volMesh>& iF
				)
				:
				mutWallFunctionFvPatchScalarField(sawfpsf, iF)
			{}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

			tmp<scalarField>
				mutSpalartAllmarasStandardWallFunctionFvPatchScalarField::yPlus() const
			{
				const label patchI = patch().index();
				const RASModel& rasModel = db().lookupObject<RASModel>("RASProperties");
				const fvPatchVectorField& Uw = rasModel.U().boundaryField()[patchI];
				const scalarField magUp = mag(Uw.patchInternalField() - Uw);

				return calcYPlus(magUp);
			}


			void mutSpalartAllmarasStandardWallFunctionFvPatchScalarField::write
			(
				Ostream& os
			) const
			{
				fvPatchField<scalar>::write(os);
				writeLocalEntries(os);
				writeEntry("value", os);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			makePatchTypeField
			(
				fvPatchScalarField,
				mutSpalartAllmarasStandardWallFunctionFvPatchScalarField
			);

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //
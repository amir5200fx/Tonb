#include <mutSpalartAllmarasWallFuncFvPatchScalarField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <compRASModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{
		namespace RASModels
		{

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			tmp<scalarField> mutSpalartAllmarasWallFunctionFvPatchScalarField::calcUTau
			(
				const scalarField& magGradU
			) const
			{
				const RASModel& rasModel = db().lookupObject<RASModel>("RASProperties");
				const scalarField& y = rasModel.y()[patch().index()];

				const fvPatchVectorField& Uw =
					rasModel.U().boundaryField()[patch().index()];

				scalarField magUp = mag(Uw.patchInternalField() - Uw);

				const fvPatchScalarField& rhow =
					rasModel.rho().boundaryField()[patch().index()];

				const fvPatchScalarField& muw =
					rasModel.mu().boundaryField()[patch().index()];
				const scalarField& mutw = *this;

				tmp<scalarField> tuTau(new scalarField(patch().size(), 0.0));
				scalarField& uTau = tuTau();

				forAll(mutw, faceI)
				{
					scalar magUpara = magUp[faceI];

					scalar ut =
						sqrt((mutw[faceI] + muw[faceI])*magGradU[faceI] / rhow[faceI]);

					if (ut > VSMALL)
					{
						int iter = 0;
						scalar err = GREAT;

						do
						{
							scalar kUu = min(kappa_*magUpara / ut, 50);
							scalar fkUu = exp(kUu) - 1 - kUu * (1 + 0.5*kUu);

							scalar f =
								-ut * y[faceI] / (muw[faceI] / rhow[faceI])
								+ magUpara / ut
								+ 1 / E_ * (fkUu - 1.0 / 6.0*kUu*sqr(kUu));

							scalar df =
								y[faceI] / (muw[faceI] / rhow[faceI])
								+ magUpara / sqr(ut)
								+ 1 / E_ * kUu*fkUu / ut;

							scalar uTauNew = ut + f / df;
							err = mag((ut - uTauNew) / ut);
							ut = uTauNew;

						} while (ut > VSMALL && err > 0.01 && ++iter < 10);

						uTau[faceI] = max(0.0, ut);
					}
				}

				return tuTau;
			}


			tmp<scalarField>
				mutSpalartAllmarasWallFunctionFvPatchScalarField::calcMut() const
			{
				const label patchI = patch().index();

				const RASModel& rasModel = db().lookupObject<RASModel>("RASProperties");
				const fvPatchVectorField& Uw = rasModel.U().boundaryField()[patchI];
				const scalarField magGradU = mag(Uw.snGrad());
				const scalarField& rhow = rasModel.rho().boundaryField()[patchI];
				const scalarField& muw = rasModel.mu().boundaryField()[patchI];

				return max
				(
					scalar(0),
					rhow*sqr(calcUTau(magGradU)) / (magGradU + ROOTVSMALL) - muw
				);
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			mutSpalartAllmarasWallFunctionFvPatchScalarField::
				mutSpalartAllmarasWallFunctionFvPatchScalarField
				(
					const fvPatch& p,
					const DimensionedField<scalar, volMesh>& iF
				)
				:
				mutWallFunctionFvPatchScalarField(p, iF)
			{}


			mutSpalartAllmarasWallFunctionFvPatchScalarField::
				mutSpalartAllmarasWallFunctionFvPatchScalarField
				(
					const mutSpalartAllmarasWallFunctionFvPatchScalarField& ptf,
					const fvPatch& p,
					const DimensionedField<scalar, volMesh>& iF,
					const fvPatchFieldMapper& mapper
				)
				:
				mutWallFunctionFvPatchScalarField(ptf, p, iF, mapper)
			{}


			mutSpalartAllmarasWallFunctionFvPatchScalarField::
				mutSpalartAllmarasWallFunctionFvPatchScalarField
				(
					const fvPatch& p,
					const DimensionedField<scalar, volMesh>& iF,
					const dictionary& dict
				)
				:
				mutWallFunctionFvPatchScalarField(p, iF, dict)
			{}


			mutSpalartAllmarasWallFunctionFvPatchScalarField::
				mutSpalartAllmarasWallFunctionFvPatchScalarField
				(
					const mutSpalartAllmarasWallFunctionFvPatchScalarField& wfpsf
				)
				:
				mutWallFunctionFvPatchScalarField(wfpsf)
			{}


			mutSpalartAllmarasWallFunctionFvPatchScalarField::
				mutSpalartAllmarasWallFunctionFvPatchScalarField
				(
					const mutSpalartAllmarasWallFunctionFvPatchScalarField& wfpsf,
					const DimensionedField<scalar, volMesh>& iF
				)
				:
				mutWallFunctionFvPatchScalarField(wfpsf, iF)
			{}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

			tmp<scalarField>
				mutSpalartAllmarasWallFunctionFvPatchScalarField::yPlus() const
			{
				const label patchI = patch().index();

				const RASModel& rasModel = db().lookupObject<RASModel>("RASProperties");
				const scalarField& y = rasModel.y()[patchI];
				const fvPatchVectorField& Uw = rasModel.U().boundaryField()[patchI];
				const scalarField& rhow = rasModel.rho().boundaryField()[patchI];
				const scalarField& muw = rasModel.mu().boundaryField()[patchI];

				return y * calcUTau(mag(Uw.snGrad())) / (muw / rhow);
			}


			void mutSpalartAllmarasWallFunctionFvPatchScalarField::write
			(
				Ostream& os
			) const
			{
				fvPatchField<scalar>::write(os);
				writeLocalEntries(os);
				writeEntry("value", os);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			makePatchTypeField(fvPatchScalarField, mutSpalartAllmarasWallFunctionFvPatchScalarField);

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //
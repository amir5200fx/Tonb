#include <compSpalartAllmaras.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <backwardsCompatibilityWallFunctions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{
		namespace RASModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(SpalartAllmaras, 0);
			addToRunTimeSelectionTable(RASModel, SpalartAllmaras, dictionary);

			// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

			tmp<volScalarField> SpalartAllmaras::chi() const
			{
				return rho_ * nuTilda_ / mu();
			}


			tmp<volScalarField> SpalartAllmaras::fv1(const volScalarField& chi) const
			{
				volScalarField chi3 = pow3(chi);
				return chi3 / (chi3 + pow3(Cv1_));
			}


			tmp<volScalarField> SpalartAllmaras::fv2
			(
				const volScalarField& chi,
				const volScalarField& fv1
			) const
			{
				return 1.0 / pow3(scalar(1) + chi / Cv2_);
			}


			tmp<volScalarField> SpalartAllmaras::fv3
			(
				const volScalarField& chi,
				const volScalarField& fv1
			) const
			{
				volScalarField chiByCv2 = (1 / Cv2_)*chi;

				return
					(scalar(1) + chi * fv1)
					*(1 / Cv2_)
					*(3 * (scalar(1) + chiByCv2) + sqr(chiByCv2))
					/ pow3(scalar(1) + chiByCv2);
			}


			tmp<volScalarField> SpalartAllmaras::fw(const volScalarField& Stilda) const
			{
				volScalarField r = min
				(
					nuTilda_
					/ (
						max(Stilda, dimensionedScalar("SMALL", Stilda.dimensions(), SMALL))
						*sqr(kappa_*d_)
						),
					scalar(10.0)
				);
				r.boundaryField() == 0.0;

				volScalarField g = r + Cw2_ * (pow6(r) - r);

				return g * pow((1.0 + pow6(Cw3_)) / (pow6(g) + pow6(Cw3_)), 1.0 / 6.0);
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			SpalartAllmaras::SpalartAllmaras
			(
				const volScalarField& rho,
				const volVectorField& U,
				const surfaceScalarField& phi,
				const basicThermo& thermophysicalModel
			)
				:
				RASModel(typeName, rho, U, phi, thermophysicalModel),

				sigmaNut_
				(
					dimensionedScalar::lookupOrAddToDict
					(
						"sigmaNut",
						coeffDict_,
						0.66666
					)
				),
				kappa_
				(
					dimensionedScalar::lookupOrAddToDict
					(
						"kappa",
						coeffDict_,
						0.41
					)
				),
				Prt_
				(
					dimensionedScalar::lookupOrAddToDict
					(
						"Prt",
						coeffDict_,
						1.0
					)
				),

				Cb1_
				(
					dimensionedScalar::lookupOrAddToDict
					(
						"Cb1",
						coeffDict_,
						0.1355
					)
				),
				Cb2_
				(
					dimensionedScalar::lookupOrAddToDict
					(
						"Cb2",
						coeffDict_,
						0.622
					)
				),
				Cw1_(Cb1_ / sqr(kappa_) + (1.0 + Cb2_) / sigmaNut_),
				Cw2_
				(
					dimensionedScalar::lookupOrAddToDict
					(
						"Cw2",
						coeffDict_,
						0.3
					)
				),
				Cw3_
				(
					dimensionedScalar::lookupOrAddToDict
					(
						"Cw3",
						coeffDict_,
						2.0
					)
				),
				Cv1_
				(
					dimensionedScalar::lookupOrAddToDict
					(
						"Cv1",
						coeffDict_,
						7.1
					)
				),
				Cv2_
				(
					dimensionedScalar::lookupOrAddToDict
					(
						"Cv2",
						coeffDict_,
						5.0
					)
				),

				nuTilda_
				(
					IOobject
					(
						"nuTilda",
						runTime_.timeName(),
						U_.db(),
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					mesh_
				),

				mut_
				(
					IOobject
					(
						"mut",
						runTime_.timeName(),
						U_.db(),
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					mesh_
				),

				alphat_
				(
					IOobject
					(
						"alphat",
						runTime_.timeName(),
						U_.db(),
						IOobject::NO_READ,
						IOobject::AUTO_WRITE
					),
					autoCreateAlphat("alphat", mesh_)
				),

				d_(mesh_)
			{
				alphat_ = mut_ / Prt_;
				alphat_.correctBoundaryConditions();

				printCoeffs();
			}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

			tmp<volSymmTensorField> SpalartAllmaras::R() const
			{
				return tmp<volSymmTensorField>
					(
						new volSymmTensorField
						(
							IOobject
							(
								"R",
								runTime_.timeName(),
								U_.db(),
								IOobject::NO_READ,
								IOobject::NO_WRITE
							),
							((2.0 / 3.0)*I)*k() - (mut_ / rho_)*dev(twoSymm(fvc::grad(U_)))
						)
						);
			}


			tmp<volSymmTensorField> SpalartAllmaras::devRhoReff() const
			{
				return tmp<volSymmTensorField>
					(
						new volSymmTensorField
						(
							IOobject
							(
								"devRhoReff",
								runTime_.timeName(),
								U_.db(),
								IOobject::NO_READ,
								IOobject::NO_WRITE
							),
							-muEff()*dev(twoSymm(fvc::grad(U_)))
						)
						);
			}


			tmp<fvVectorMatrix> SpalartAllmaras::divDevRhoReff() const
			{
				volScalarField muEff_ = muEff();

				return
					(
						-fvm::laplacian(muEff_, U_)
						- fvc::div(muEff_*dev2(T(fvc::grad(U_))))
						);
			}


			bool SpalartAllmaras::read()
			{
				if (RASModel::read())
				{
					sigmaNut_.readIfPresent(coeffDict());
					kappa_.readIfPresent(coeffDict());
					Prt_.readIfPresent(coeffDict());

					Cb1_.readIfPresent(coeffDict());
					Cb2_.readIfPresent(coeffDict());
					Cw1_ = Cb1_ / sqr(kappa_) + (1.0 + Cb2_) / sigmaNut_;
					Cw2_.readIfPresent(coeffDict());
					Cw3_.readIfPresent(coeffDict());
					Cv1_.readIfPresent(coeffDict());
					Cv2_.readIfPresent(coeffDict());

					return true;
				}
				else
				{
					return false;
				}
			}


			void SpalartAllmaras::correct()
			{
				// Bound in case of topological change
				// HJ, 22/Aug/2007
				if (mesh_.changing())
				{
					bound(nuTilda_, dimensionedScalar("0", nuTilda_.dimensions(), 0.0));
				}

				if (!turbulence_)
				{
					// Re-calculate viscosity
					mut_ = rho_ * nuTilda_*fv1(chi());
					mut_.correctBoundaryConditions();

					// Re-calculate thermal diffusivity
					alphat_ = mut_ / Prt_;
					alphat_.correctBoundaryConditions();

					return;
				}

				RASModel::correct();

				if (mesh_.changing())
				{
					d_.correct();
				}

				volScalarField chi = this->chi();
				volScalarField fv1 = this->fv1(chi);

				volScalarField Stilda =
					fv3(chi, fv1)*::sqrt(2.0)*mag(skew(fvc::grad(U_)))
					+ fv2(chi, fv1)*nuTilda_ / sqr(kappa_*d_);

				tmp<fvScalarMatrix> nuTildaEqn
				(
					fvm::ddt(rho_, nuTilda_)
					+ fvm::div(phi_, nuTilda_)
					- fvm::laplacian(DnuTildaEff(), nuTilda_)
					- Cb2_ / sigmaNut_ * rho_*magSqr(fvc::grad(nuTilda_))
					==
					Cb1_ * rho_*Stilda*nuTilda_
					- fvm::Sp(Cw1_*fw(Stilda)*nuTilda_*rho_ / sqr(d_), nuTilda_)
				);

				nuTildaEqn().relax();
				solve(nuTildaEqn);
				bound(nuTilda_, dimensionedScalar("0", nuTilda_.dimensions(), 0.0));
				nuTilda_.correctBoundaryConditions();

				// Re-calculate viscosity
				mut_.internalField() = fv1 * nuTilda_.internalField()*rho_.internalField();
				mut_.correctBoundaryConditions();

				// Re-calculate thermal diffusivity
				alphat_ = mut_ / Prt_;
				alphat_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //
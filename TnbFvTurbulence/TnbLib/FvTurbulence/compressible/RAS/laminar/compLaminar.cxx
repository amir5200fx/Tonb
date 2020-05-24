#include <compLaminar.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{
		namespace RASModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(laminar, 0);
			addToRunTimeSelectionTable(RASModel, laminar, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			laminar::laminar
			(
				const volScalarField& rho,
				const volVectorField& U,
				const surfaceScalarField& phi,
				const basicThermo& thermophysicalModel
			)
				:
				RASModel(typeName, rho, U, phi, thermophysicalModel)
			{}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

			tmp<volScalarField> laminar::mut() const
			{
				return tmp<volScalarField>
					(
						new volScalarField
						(
							IOobject
							(
								"mut",
								runTime_.timeName(),
								U_.db(),
								IOobject::NO_READ,
								IOobject::NO_WRITE
							),
							mesh_,
							dimensionedScalar("mut", mu().dimensions(), 0.0)
						)
						);
			}


			tmp<volScalarField> laminar::k() const
			{
				return tmp<volScalarField>
					(
						new volScalarField
						(
							IOobject
							(
								"k",
								runTime_.timeName(),
								U_.db(),
								IOobject::NO_READ,
								IOobject::NO_WRITE
							),
							mesh_,
							dimensionedScalar("k", sqr(U_.dimensions()), 0.0)
						)
						);
			}


			tmp<volScalarField> laminar::epsilon() const
			{
				return tmp<volScalarField>
					(
						new volScalarField
						(
							IOobject
							(
								"epsilon",
								runTime_.timeName(),
								U_.db(),
								IOobject::NO_READ,
								IOobject::NO_WRITE
							),
							mesh_,
							dimensionedScalar
							(
								"epsilon", sqr(U_.dimensions()) / dimTime, 0.0
							)
						)
						);
			}


			tmp<volSymmTensorField> laminar::R() const
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
							mesh_,
							dimensionedSymmTensor
							(
								"R", sqr(U_.dimensions()), symmTensor::zero
							)
						)
						);
			}


			tmp<volSymmTensorField> laminar::devRhoReff() const
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
							-mu()*dev(twoSymm(fvc::grad(U_)))
						)
						);
			}


			tmp<fvVectorMatrix> laminar::divDevRhoReff() const
			{
				return
					(
						-fvm::laplacian(muEff(), U_)
						- fvc::div(muEff()*dev2(T(fvc::grad(U_))))
						);
			}


			bool laminar::read()
			{
				return RASModel::read();
			}


			void laminar::correct()
			{}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //
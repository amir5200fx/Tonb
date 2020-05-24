#include <CompTurbulenceModel.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(turbulenceModel, 0);
		defineRunTimeSelectionTable(turbulenceModel, turbulenceModel);

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		turbulenceModel::turbulenceModel
		(
			const volScalarField& rho,
			const volVectorField& U,
			const surfaceScalarField& phi,
			const basicThermo& thermophysicalModel
		)
			:
			runTime_(U.time()),
			mesh_(U.mesh()),

			rho_(rho),
			U_(U),
			phi_(phi),
			thermophysicalModel_(thermophysicalModel)
		{}


		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		autoPtr<turbulenceModel> turbulenceModel::New
		(
			const volScalarField& rho,
			const volVectorField& U,
			const surfaceScalarField& phi,
			const basicThermo& thermophysicalModel
		)
		{
			word modelName;

			// Enclose the creation of the dictionary to ensure it is deleted
			// before the turbulenceModel is created otherwise the dictionary is
			// entered in the database twice
			{
				IOdictionary dict
				(
					IOobject
					(
						"turbulenceProperties",
						U.time().constant(),
						U.db(),
						IOobject::MUST_READ,
						IOobject::NO_WRITE
					)
				);

				dict.lookup("simulationType") >> modelName;
			}

			Info << "Selecting turbulence model type " << modelName << endl;

			turbulenceModelConstructorTable::iterator cstrIter =
				turbulenceModelConstructorTablePtr_->find(modelName);

			if (cstrIter == turbulenceModelConstructorTablePtr_->end())
			{
				FatalErrorIn
				(
					"turbulenceModel::New(const volScalarField&, "
					"const volVectorField&, const surfaceScalarField&, "
					"basicThermo&)"
				) << "Unknown turbulenceModel type " << modelName
					<< endl << endl
					<< "Valid turbulenceModel types are :" << endl
					<< turbulenceModelConstructorTablePtr_->sortedToc()
					<< exit(FatalError);
			}

			return autoPtr<turbulenceModel>
				(
					cstrIter()(rho, U, phi, thermophysicalModel)
					);
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		void turbulenceModel::correct()
		{}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //
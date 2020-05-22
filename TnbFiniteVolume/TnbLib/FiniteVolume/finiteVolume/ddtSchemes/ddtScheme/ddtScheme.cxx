#include <ddtScheme.hxx>

#include <fv.hxx>
#include <surfaceInterpolate.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<ddtScheme<Type> > ddtScheme<Type>::New
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				Info << "ddtScheme<Type>::New(const fvMesh&, Istream&) : "
					"constructing ddtScheme<Type>"
					<< endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorIn
				(
					"ddtScheme<Type>::New(const fvMesh&, Istream&)",
					schemeData
				) << "Ddt scheme not specified" << nl << nl
					<< "Valid ddt schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			const word schemeName(schemeData);

			typename IstreamConstructorTable::iterator cstrIter =
				IstreamConstructorTablePtr_->find(schemeName);

			if (cstrIter == IstreamConstructorTablePtr_->end())
			{
				FatalIOErrorIn
				(
					"ddtScheme<Type>::New(const fvMesh&, Istream&)",
					schemeData
				) << "Unknown ddt scheme " << schemeName << nl << nl
					<< "Valid ddt schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return cstrIter()(mesh, schemeData);
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		ddtScheme<Type>::~ddtScheme()
		{}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<surfaceScalarField> ddtScheme<Type>::fvcDdtPhiCoeff
		(
			const GeometricField<Type, fvPatchField, volMesh>& U,
			const fluxFieldType& phi,
			const fluxFieldType& phiCorr
		)
		{
			tmp<surfaceScalarField> tddtCouplingCoeff = scalar(1)
				- min
				(
					mag(phiCorr)
					/ (mag(phi) + dimensionedScalar("small", phi.dimensions(), SMALL)),
					scalar(1)
				);

			surfaceScalarField& ddtCouplingCoeff = tddtCouplingCoeff();

			forAll(U.boundaryField(), patchi)
			{
				if (U.boundaryField()[patchi].fixesValue())
				{
					ddtCouplingCoeff.boundaryField()[patchi] = 0.0;
				}
			}

			if (debug > 1)
			{
				Info << "ddtCouplingCoeff mean max min = "
					<< gAverage(ddtCouplingCoeff.internalField())
					<< " " << gMax(ddtCouplingCoeff.internalField())
					<< " " << gMin(ddtCouplingCoeff.internalField())
					<< endl;
			}

			return tddtCouplingCoeff;
		}


		template<class Type>
		tmp<surfaceScalarField> ddtScheme<Type>::fvcDdtPhiCoeff
		(
			const GeometricField<Type, fvPatchField, volMesh>& U,
			const fluxFieldType& phi
		)
		{
			dimensionedScalar rDeltaT = 1.0 / mesh().time().deltaT();

			tmp<surfaceScalarField> tddtCouplingCoeff = scalar(1)
				- min
				(
					mag(phi - (mesh().Sf() & fvc::interpolate(U)))
					/ (mag(phi) + dimensionedScalar("small", phi.dimensions(), VSMALL)),
					//(rDeltaT*mesh().magSf()/mesh().deltaCoeffs()),
					scalar(1)
				);

			surfaceScalarField& ddtCouplingCoeff = tddtCouplingCoeff();

			forAll(U.boundaryField(), patchi)
			{
				if (U.boundaryField()[patchi].fixesValue())
				{
					ddtCouplingCoeff.boundaryField()[patchi] = 0.0;
				}
			}

			if (debug > 1)
			{
				Info << "ddtCouplingCoeff mean max min = "
					<< gAverage(ddtCouplingCoeff.internalField())
					<< " " << gMax(ddtCouplingCoeff.internalField())
					<< " " << gMin(ddtCouplingCoeff.internalField())
					<< endl;
			}

			return tddtCouplingCoeff;
		}


		template<class Type>
		tmp<surfaceScalarField> ddtScheme<Type>::fvcDdtPhiCoeff
		(
			const volScalarField& rho,
			const GeometricField<Type, fvPatchField, volMesh>& rhoU,
			const fluxFieldType& phi
		)
		{
			dimensionedScalar rDeltaT = 1.0 / mesh().time().deltaT();

			tmp<surfaceScalarField> tddtCouplingCoeff = scalar(1)
				- min
				(
					mag(phi - (mesh().Sf() & fvc::interpolate(rhoU)))
					/ (
						mag(phi) + dimensionedScalar("small", phi.dimensions(), VSMALL)
						//fvc::interpolate(rho)*rDeltaT
						//*mesh().magSf()/mesh().deltaCoeffs()
						),
					scalar(1)
				);

			surfaceScalarField& ddtCouplingCoeff = tddtCouplingCoeff();

			forAll(rhoU.boundaryField(), patchi)
			{
				if (rhoU.boundaryField()[patchi].fixesValue())
				{
					ddtCouplingCoeff.boundaryField()[patchi] = 0.0;
				}
			}

			if (debug > 1)
			{
				Info << "ddtCouplingCoeff mean max min = "
					<< gAverage(ddtCouplingCoeff.internalField())
					<< " " << gMax(ddtCouplingCoeff.internalField())
					<< " " << gMin(ddtCouplingCoeff.internalField())
					<< endl;
			}

			return tddtCouplingCoeff;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
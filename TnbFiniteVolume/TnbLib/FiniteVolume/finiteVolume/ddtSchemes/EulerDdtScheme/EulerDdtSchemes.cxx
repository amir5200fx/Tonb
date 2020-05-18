#include <EulerDdtScheme.hxx>

#include <fvMesh.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		makeFvDdtTypeScheme(EulerDdtScheme, scalar)
		makeFvDdtTypeScheme(EulerDdtScheme, vector)
		makeFvDdtTypeScheme(EulerDdtScheme, sphericalTensor)
		makeFvDdtTypeScheme(EulerDdtScheme, symmTensor)
		makeFvDdtTypeScheme(EulerDdtScheme, symmTensor4thOrder)
		makeFvDdtTypeScheme(EulerDdtScheme, diagTensor)
		makeFvDdtTypeScheme(EulerDdtScheme, tensor)

		template <>
		tmp<surfaceScalarField> EulerDdtScheme<scalar>::fvcDdtPhiCorr(const volScalarField& rA, const volScalarField& U,
		                                                              const surfaceScalarField& phi)
		{
			notImplemented("EulerDdtScheme""<scalar>::fvcDdtPhiCorr");
			return surfaceScalarField::null();
		}

		template <>
		tmp<surfaceScalarField> EulerDdtScheme<scalar>::fvcDdtPhiCorr(const volScalarField& rA, const volScalarField& rho,
		                                                              const volScalarField& U, const surfaceScalarField& phi)
		{
			notImplemented("EulerDdtScheme""<scalar>::fvcDdtPhiCorr");
			return surfaceScalarField::null();
		}
	}
}

// ************************************************************************* //
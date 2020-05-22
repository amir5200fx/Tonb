#include <fvcMeshPhi.hxx>

#include <surfaceInterpolate.hxx>
#include <fvc.hxx>
#include <fvMesh.hxx>
#include <ddtScheme.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::meshPhi
(
	const volVectorField& vf
)
{
	return fv::ddtScheme<vector>::New
	(
		vf.mesh(),
		vf.mesh().schemesDict().ddtScheme("ddt(" + vf.name() + ')')
	)().meshPhi(vf);
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::meshPhi
(
	const dimensionedScalar& rho,
	const volVectorField& vf
)
{
	return fv::ddtScheme<vector>::New
	(
		vf.mesh(),
		vf.mesh().schemesDict().ddtScheme
		(
			"ddt(" + rho.name() + ',' + vf.name() + ')'
		)
	)().meshPhi(vf);
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::meshPhi
(
	const volScalarField& rho,
	const volVectorField& vf
)
{
	return fv::ddtScheme<vector>::New
	(
		vf.mesh(),
		vf.mesh().schemesDict().ddtScheme
		(
			"ddt(" + rho.name() + ',' + vf.name() + ')'
		)
	)().meshPhi(vf);
}


void tnbLib::fvc::makeRelative
(
	surfaceScalarField& phi,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi -= fvc::meshPhi(U);
	}
}


void tnbLib::fvc::makeRelative
(
	surfaceScalarField& phi,
	const dimensionedScalar& rho,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi -= rho * fvc::meshPhi(rho, U);
	}
}


void tnbLib::fvc::makeRelative
(
	surfaceScalarField& phi,
	const volScalarField& rho,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi -= fvc::interpolate(rho)*fvc::meshPhi(rho, U);
	}
}


void tnbLib::fvc::makeAbsolute
(
	surfaceScalarField& phi,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi += fvc::meshPhi(U);
	}
}


void tnbLib::fvc::makeAbsolute
(
	surfaceScalarField& phi,
	const dimensionedScalar& rho,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi += rho * fvc::meshPhi(rho, U);
	}
}


void tnbLib::fvc::makeAbsolute
(
	surfaceScalarField& phi,
	const volScalarField& rho,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi += fvc::interpolate(rho)*fvc::meshPhi(rho, U);
	}
}


// ************************************************************************* //
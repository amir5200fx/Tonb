#include <basicPsiThermo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(basicPsiThermo, 0);
	defineRunTimeSelectionTable(basicPsiThermo, fvMesh);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::basicPsiThermo::basicPsiThermo(const fvMesh& mesh, const objectRegistry& obj)
	:
	basicThermo(mesh, obj)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::basicPsiThermo::~basicPsiThermo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::volScalarField& tnbLib::basicPsiThermo::drhodh() const
{
	notImplemented("basicPsiThermo::drhodh()");
	return const_cast<volScalarField&>(volScalarField::null());
}

const tnbLib::volScalarField& tnbLib::basicPsiThermo::drhode() const
{
	notImplemented("basicPsiThermo::drhode()");
	return const_cast<volScalarField&>(volScalarField::null());
}


// ************************************************************************* //
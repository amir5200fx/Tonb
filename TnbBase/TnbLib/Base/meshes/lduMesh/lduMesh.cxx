#include <lduMesh.hxx>

#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::lduMesh, 0);


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::objectRegistry& tnbLib::lduMesh::thisDb() const
{
	notImplemented("lduMesh::thisDb() const");
	const objectRegistry* orPtr_ = NULL;
	return *orPtr_;
}


// ************************************************************************* //
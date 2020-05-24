#include <basicMixture.hxx>

#include <error.hxx>
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(basicMixture, 0);

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	basicMixture::basicMixture
	(
		const dictionary&,
		const fvMesh&,
		const objectRegistry&
	)
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	basicMixture::~basicMixture()
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
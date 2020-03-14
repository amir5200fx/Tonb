#include <triSurfModifier.hxx>

#include <demandDrivenData.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Construct from parts
	triSurfModifier::triSurfModifier(triSurf& surface)
		:
		surface_(surface)
	{}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	triSurfModifier::~triSurfModifier()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
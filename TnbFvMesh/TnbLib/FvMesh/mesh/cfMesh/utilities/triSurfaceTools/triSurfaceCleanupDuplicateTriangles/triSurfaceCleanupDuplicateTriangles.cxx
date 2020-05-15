#include <triSurfaceCleanupDuplicateTriangles.hxx>

#include <triSurf.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	triSurfaceCleanupDuplicateTriangles::triSurfaceCleanupDuplicateTriangles
	(
		triSurf& surf
	)
		:
		surf_(surf),
		newTriangleLabel_()
	{
		checkDuplicateTriangles();
	}

	triSurfaceCleanupDuplicateTriangles::~triSurfaceCleanupDuplicateTriangles()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
#include <meshOctreeCube.hxx>

#include <triSurf.hxx>
#include <VRWGraph.hxx>
#include <helperFunctions.hxx>

//#define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	bool meshOctreeCube::hasContainedTriangles
	(
		const triSurf& surface,
		const boundBox& rootBox,
		const VRWGraph& containedElements
	) const
	{
		if (containedElementsLabel_ == -1)
			return false;

		forAllRow(containedElements, containedElementsLabel_, tI)
			if (
				intersectsTriangleExact
				(
					surface,
					rootBox,
					containedElements(containedElementsLabel_, tI)
				)
				)
				return true;

		return false;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
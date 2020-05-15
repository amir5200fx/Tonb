#include <triSurfaceClassifyEdges.hxx>

#include <helperFunctions.hxx>
#include <demandDrivenData.hxx>
#include <triSurfModifier.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	triSurfaceClassifyEdges::triSurfaceClassifyEdges
	(
		const meshOctree& octree
	)
		:
		octree_(octree),
		edgeTypes_(),
		facetOrientation_()
	{
		checkOrientation();

		classifyEdgesTypes();
	}

	triSurfaceClassifyEdges::~triSurfaceClassifyEdges()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const List<direction>& triSurfaceClassifyEdges::edgeTypes() const
	{
		return edgeTypes_;
	}
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
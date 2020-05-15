#include <meshOctreeCreator.hxx>

#include <triSurf.hxx>
#include <IOdictionary.hxx>

//#define DEBUGBalancing

# ifdef DEBUGBalancing
#include <sstream>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Private member functions

	void meshOctreeCreator::loadDistribution(const bool distributeUsed)
	{
		if (octree_.neiProcs().size() == 0 || !meshDictPtr_)
			return;

		direction usedType(0);
		if (distributeUsed)
		{
			usedType |= meshOctreeCubeBasic::INSIDE;
			if (meshDictPtr_->found("keepCellsIntersectingBoundary"))
				usedType |= meshOctreeCubeBasic::DATA;
		}

		meshOctreeModifier(octree_).loadDistribution(usedType);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
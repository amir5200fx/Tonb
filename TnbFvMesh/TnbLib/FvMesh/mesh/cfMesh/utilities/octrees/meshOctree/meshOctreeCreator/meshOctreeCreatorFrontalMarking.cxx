#include <meshOctreeCreator.hxx>

#include <meshOctreeInsideOutside.hxx>

//#define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshOctreeCreator::createInsideOutsideInformation()
	{
		Info << "Marking inside/outside." << endl;

		meshOctreeInsideOutside insideOutside(octree_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
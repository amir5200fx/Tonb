#include <checkIrregularSurfaceConnections.hxx>

#include <PstreamReduceOps.hxx>

//#define DEBUGCheck

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //
	// Constructors

	checkIrregularSurfaceConnections::checkIrregularSurfaceConnections
	(
		polyMeshGen& mesh
	)
		:
		mesh_(mesh),
		meshSurfacePtr_(NULL)
	{
	}

	// * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * * * * //

	checkIrregularSurfaceConnections::~checkIrregularSurfaceConnections()
	{
		clearMeshEngine();

		mesh_.clearAddressingData();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void checkIrregularSurfaceConnections::checkIrregularVertices
	(
		labelHashSet& badVertices
	)
	{
		checkAndFixCellGroupsAtBndVertices(badVertices, false);

		checkEdgeFaceConnections(badVertices, false);

		checkFaceGroupsAtBndVertices(badVertices, false);
	}

	bool checkIrregularSurfaceConnections::checkAndFixIrregularConnections()
	{
		Info << "Checking for irregular surface connections" << endl;

		bool finished;

		labelHashSet badVertices;

		do
		{
			finished = true;

			while (checkAndFixCellGroupsAtBndVertices(badVertices, true))
				finished = false;

			while (checkEdgeFaceConnections(badVertices, true))
				finished = false;

			if (checkFaceGroupsAtBndVertices(badVertices, true))
				finished = false;
		} while (!finished);

		polyMeshGenModifier(mesh_).removeUnusedVertices();

		Info << "Finished checking for irregular surface connections" << endl;

		if (returnReduce(badVertices.size(), sumOp<label>()) != 0)
			return true;

		return false;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
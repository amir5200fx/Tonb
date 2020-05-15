#include <cartesianMeshExtractor.hxx>

#include <meshOctree.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Private member functions

	void cartesianMeshExtractor::createPointsAndAddressing()
	{
		Info << "Creating octree vertices" << endl;

		Info << "Octree nodes " << octreeCheck_.numberOfNodes() << endl;

		//- set the size of the point field
		pointFieldPMG& points = mesh_.points();
		points.setSize(octreeCheck_.numberOfNodes());

		//- store vertices into the pointField
		const pointField& octreePoints = octreeCheck_.octreePoints();

		forAll(points, pointI)
			points[pointI] = octreePoints[pointI];

		Info << "Finished creating octree vertices" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
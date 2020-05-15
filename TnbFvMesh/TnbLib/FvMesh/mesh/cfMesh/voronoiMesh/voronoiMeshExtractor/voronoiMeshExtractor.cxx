#include <voronoiMeshExtractor.hxx>

#include <demandDrivenData.hxx>

// #define DEBUGTets

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	label voronoiMeshExtractor::sameOrientation_[6] = { 3, 1, 2, 2, 3, 0 };

	label voronoiMeshExtractor::oppositeOrientation_[6] = { 2, 3, 1, 0, 0, 1 };

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void voronoiMeshExtractor::clearOut()
	{
		deleteDemandDrivenData(pointEdgesPtr_);
		deleteDemandDrivenData(edgesPtr_);
		deleteDemandDrivenData(edgeTetsPtr_);
		deleteDemandDrivenData(boundaryEdgePtr_);
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from octree and mesh data
	voronoiMeshExtractor::voronoiMeshExtractor
	(
		const meshOctree& octree,
		const IOdictionary& meshDict,
		polyMeshGen& mesh
	)
		:
		tetCreator_(octree, meshDict),
		mesh_(mesh),
		pointEdgesPtr_(NULL),
		edgesPtr_(NULL),
		edgeTetsPtr_(NULL),
		boundaryEdgePtr_(NULL)
	{}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	voronoiMeshExtractor::~voronoiMeshExtractor()
	{
		clearOut();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void voronoiMeshExtractor::createMesh()
	{
		Info << "Extracting voronoi mesh" << endl;

		//- copy tet points into the mesh
		createPoints();

		//- create the mesh
		createPolyMesh();

		polyMeshGenModifier(mesh_).reorderBoundaryFaces();
		polyMeshGenModifier(mesh_).removeUnusedVertices();

		Info << "Mesh has :" << nl
			<< mesh_.points().size() << " vertices " << nl
			<< mesh_.faces().size() << " faces" << nl
			<< mesh_.cells().size() << " cells" << endl;

		Info << "Finished extracting voronoi mesh" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
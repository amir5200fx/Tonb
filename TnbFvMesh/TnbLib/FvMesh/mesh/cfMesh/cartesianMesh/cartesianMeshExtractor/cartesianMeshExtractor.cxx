#include <cartesianMeshExtractor.hxx>

#include <meshOctree.hxx>
#include <Pstream.hxx>
#include <PstreamReduceOps.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void cartesianMeshExtractor::clearOut()
	{
		deleteDemandDrivenData(leafCellLabelPtr_);
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from octree and mesh data
	cartesianMeshExtractor::cartesianMeshExtractor
	(
		meshOctree& octree,
		const IOdictionary& meshDict,
		polyMeshGen& mesh
	)
		:
		octreeCheck_(octree, meshDict, false),
		mesh_(mesh),
		decomposeSplitHexes_(false),
		leafCellLabelPtr_(new labelList(octree.numberOfLeaves(), -1))
	{
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	cartesianMeshExtractor::~cartesianMeshExtractor()
	{
		clearOut();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void cartesianMeshExtractor::decomposeSplitHexes()
	{
		decomposeSplitHexes_ = true;
	}

	void cartesianMeshExtractor::createMesh()
	{
		Info << "Extracting polyMesh" << endl;

		//- create points and pointLeaves addressing
		createPointsAndAddressing();

		//- create the mesh
		createPolyMesh();

		//- decompose split-hex cells into tetrahedra and pyramids
		decomposeSplitHexesIntoTetsAndPyramids();

		//- remove unused vertices
		polyMeshGenModifier(mesh_).removeUnusedVertices();

		Info << "Mesh has :" << nl
			<< mesh_.points().size() << " vertices " << nl
			<< mesh_.faces().size() << " faces" << nl
			<< mesh_.cells().size() << " cells" << endl;

		if (Pstream::parRun())
		{
			label nCells = mesh_.cells().size();
			reduce(nCells, sumOp<label>());
			Info << "Total number of cells " << nCells << endl;
		}
		if (mesh_.cells().size() == 0)
		{
			FatalErrorIn
			(
				"void cartesianMeshExtractor::createMesh()"
			) << "There are no cells in the mesh!"
				<< nl << "The reasons for this can be fwofold:"
				<< nl << "1. Inadequate mesh resolution."
				<< nl << "2. You maxCellSize is a multiplier of the domain length."
				<< " This can be reolved by reducing the maxCellSize by a fraction."
				<< "i.e. 2.49999 instead of 2.5." << exit(FatalError);
		}

		Info << "Finished extracting polyMesh" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
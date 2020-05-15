#include <tetCreatorOctree.hxx>

#include <meshOctree.hxx>
#include <demandDrivenData.hxx>


//#define DEBUGTets

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const meshOctreeCubeCoordinates tetCreatorOctree::edgeCoordinates_[12][4] =
	{
		{    //- edge 0
			meshOctreeCubeCoordinates(0, 0, 1, 0),
			meshOctreeCubeCoordinates(0, -1, 1, 0),
			meshOctreeCubeCoordinates(0, -1, 0, 0),
			meshOctreeCubeCoordinates(0, 0, 0, 0)
		},
		{    //- edge 1
			meshOctreeCubeCoordinates(0, 0, 0, 0),
			meshOctreeCubeCoordinates(0, -1, 0, 0),
			meshOctreeCubeCoordinates(0, -1, -1, 0),
			meshOctreeCubeCoordinates(0, 0, -1, 0)
		},
		{   //- edge 2
			meshOctreeCubeCoordinates(0, 1, 0, 0),
			meshOctreeCubeCoordinates(0, 0, 0, 0),
			meshOctreeCubeCoordinates(0, 0, -1, 0),
			meshOctreeCubeCoordinates(0, 1, -1, 0)
		},
		{    //- edge 3
			meshOctreeCubeCoordinates(0, 1, 1, 0),
			meshOctreeCubeCoordinates(0, 0, 1, 0),
			meshOctreeCubeCoordinates(0, 0, 0, 0),
			meshOctreeCubeCoordinates(0, 1, 0, 0)
		},
		{    //- edge 4
			meshOctreeCubeCoordinates(0, 0, 0, 0),
			meshOctreeCubeCoordinates(0, 0, 1, 0),
			meshOctreeCubeCoordinates(1, 0, 1, 0),
			meshOctreeCubeCoordinates(1, 0, 0, 0)
		},
		{    //- edge 5
			meshOctreeCubeCoordinates(0, 0, -1, 0),
			meshOctreeCubeCoordinates(0, 0, 0, 0),
			meshOctreeCubeCoordinates(1, 0, 0, 0),
			meshOctreeCubeCoordinates(1, 0, -1, 0)
		},
		{   //- edge 6
			meshOctreeCubeCoordinates(-1, 0, -1, 0),
			meshOctreeCubeCoordinates(-1, 0, 0, 0),
			meshOctreeCubeCoordinates(0, 0, 0, 0),
			meshOctreeCubeCoordinates(0, 0, -1, 0)
		},
		{    //- edge 7
			meshOctreeCubeCoordinates(-1, 0, 0, 0),
			meshOctreeCubeCoordinates(-1, 0, 1, 0),
			meshOctreeCubeCoordinates(0, 0, 1, 0),
			meshOctreeCubeCoordinates(0, 0, 0, 0)
		},
		{    //- edge 8
			meshOctreeCubeCoordinates(-1, 0, 0, 0),
			meshOctreeCubeCoordinates(-1, -1, 0, 0),
			meshOctreeCubeCoordinates(0, -1, 0, 0),
			meshOctreeCubeCoordinates(0, 0, 0, 0)
		},
		{    //- edge 9
			meshOctreeCubeCoordinates(0, 0, 0, 0),
			meshOctreeCubeCoordinates(0, -1, 0, 0),
			meshOctreeCubeCoordinates(1, -1, 0, 0),
			meshOctreeCubeCoordinates(1, 0, 0, 0)
		},
		{   //- edge 10
			meshOctreeCubeCoordinates(0, 1, 0, 0),
			meshOctreeCubeCoordinates(0, 0, 0, 0),
			meshOctreeCubeCoordinates(1, 0, 0, 0),
			meshOctreeCubeCoordinates(1, 1, 0, 0)
		},
		{    //- edge 11
			meshOctreeCubeCoordinates(-1, 1, 0, 0),
			meshOctreeCubeCoordinates(-1, 0, 0, 0),
			meshOctreeCubeCoordinates(0, 0, 0, 0),
			meshOctreeCubeCoordinates(0, 1, 0, 0)
		}
	};

	const label tetCreatorOctree::faceCentreHelper_[3][4] =
	{
		{3, 5, 2, 4},
		{5, 1, 4, 0},
		{1, 3, 0, 2}
	};

	void tetCreatorOctree::createTets()
	{
		createPointsAndAddressing();

		createTetsFromFacesWithCentreNode();

		createTetsAroundSplitEdges();

		createTetsAroundEdges();

		createTetsFromSplitFaces();

		clearOut();
		sortedLeaves_.setSize(0);

		created_ = true;
	}

	void tetCreatorOctree::clearOut()
	{
		sortedLeaves_.clear();
		deleteDemandDrivenData(subNodeLabelsPtr_);
		deleteDemandDrivenData(cubeLabelPtr_);
		deleteDemandDrivenData(faceCentreLabelPtr_);
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from octree and mesh data
	tetCreatorOctree::tetCreatorOctree
	(
		const meshOctree& octree,
		const IOdictionary& meshDict
	)
		:
		octreeCheck_(octree, meshDict, true),
		tetPoints_(),
		tets_(),
		sortedLeaves_(),
		subNodeLabelsPtr_(NULL),
		cubeLabelPtr_(NULL),
		faceCentreLabelPtr_(NULL),
		created_(false)
	{
		createTets();

		clearOut();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	tetCreatorOctree::~tetCreatorOctree()
	{
		clearOut();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
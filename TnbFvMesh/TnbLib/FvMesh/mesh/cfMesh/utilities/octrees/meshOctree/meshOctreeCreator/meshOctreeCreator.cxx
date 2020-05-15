#include <meshOctreeCreator.hxx>

#include <triSurf.hxx>
#include <boundBox.hxx>
#include <demandDrivenData.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	meshOctreeCreator::meshOctreeCreator(meshOctree& mo)
		:
		octree_(mo),
		scalingFactor_(1.0),
		meshDictPtr_(NULL),
		hexRefinement_(false),
		globalRefLevel_(0),
		surfRefLevel_(mo.surface().size())
	{}

	meshOctreeCreator::meshOctreeCreator
	(
		meshOctree& mo,
		const IOdictionary& dict
	)
		:
		octree_(mo),
		scalingFactor_(1.0),
		meshDictPtr_(&dict),
		hexRefinement_(false),
		globalRefLevel_(0),
		surfRefLevel_(mo.surface().size())
	{}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshOctreeCreator::~meshOctreeCreator()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshOctreeCreator::setScalingFactor(const scalar s)
	{
		scalingFactor_ = s;
	}

	void meshOctreeCreator::activateHexRefinement()
	{
		hexRefinement_ = true;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
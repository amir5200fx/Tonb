#include <meshSurfaceOptimizer.hxx>

#include <demandDrivenData.hxx>
#include <meshSurfaceOptimizer.hxx>
#include <meshSurfaceEngine.hxx>
#include <meshSurfacePartitioner.hxx>
#include <meshSurfaceMapper.hxx>
#include <polyMeshGenChecks.hxx>

#include <map>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshSurfaceOptimizer::classifySurfaceVertices()
	{
		const labelHashSet& corners = partitionerPtr_->corners();
		const labelHashSet& edgePoints = partitionerPtr_->edgePoints();

		//- set all vertices to partition
		vertexType_ = PARTITION;

		//- set corners
		forAllConstIter(labelHashSet, corners, it)
			vertexType_[it.key()] = CORNER;

		//- set edges
		forAllConstIter(labelHashSet, edgePoints, it)
			vertexType_[it.key()] = EDGE;

		if (Pstream::parRun())
		{
			//- mark nodes at parallel boundaries
			const Map<label>& globalToLocal =
				surfaceEngine_.globalToLocalBndPointAddressing();

			forAllConstIter(Map<label>, globalToLocal, iter)
			{
				const label bpI = iter();

				vertexType_[bpI] |= PROCBND;
			}
		}
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	meshSurfaceOptimizer::meshSurfaceOptimizer(const meshSurfaceEngine& surface)
		:
		surfaceEngine_(surface),
		vertexType_(surface.boundaryPoints().size()),
		partitionerPtr_(new meshSurfacePartitioner(surface)),
		deletePartitioner_(true),
		octreePtr_(NULL),
		triMeshPtr_(NULL),
		enforceConstraints_(false),
		badPointsSubsetName_("invertedBoundaryPoints")
	{
		classifySurfaceVertices();
	}

	meshSurfaceOptimizer::meshSurfaceOptimizer(const meshSurfacePartitioner& mPart)
		:
		surfaceEngine_(mPart.surfaceEngine()),
		vertexType_(surfaceEngine_.boundaryPoints().size()),
		partitionerPtr_(&mPart),
		deletePartitioner_(true),
		octreePtr_(NULL),
		triMeshPtr_(NULL),
		enforceConstraints_(false),
		badPointsSubsetName_("invertedBoundaryPoints")
	{
		classifySurfaceVertices();
	}

	meshSurfaceOptimizer::meshSurfaceOptimizer
	(
		const meshSurfaceEngine& surface,
		const meshOctree& octree
	)
		:
		surfaceEngine_(surface),
		vertexType_(surface.boundaryPoints().size()),
		partitionerPtr_(new meshSurfacePartitioner(surface)),
		deletePartitioner_(true),
		octreePtr_(&octree),
		triMeshPtr_(NULL),
		enforceConstraints_(false),
		badPointsSubsetName_("invertedBoundaryPoints")
	{
		classifySurfaceVertices();
	}

	meshSurfaceOptimizer::meshSurfaceOptimizer
	(
		const meshSurfacePartitioner& partitioner,
		const meshOctree& octree
	)
		:
		surfaceEngine_(partitioner.surfaceEngine()),
		vertexType_(surfaceEngine_.boundaryPoints().size()),
		partitionerPtr_(&partitioner),
		deletePartitioner_(false),
		octreePtr_(&octree),
		triMeshPtr_(NULL),
		enforceConstraints_(false),
		badPointsSubsetName_("invertedBoundaryPoints")
	{
		classifySurfaceVertices();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshSurfaceOptimizer::~meshSurfaceOptimizer()
	{
		deleteDemandDrivenData(triMeshPtr_);

		if (deletePartitioner_)
			deleteDemandDrivenData(partitionerPtr_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshSurfaceOptimizer::removeUserConstraints()
	{
# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 100)
# endif
		forAll(vertexType_, bpI)
			if (vertexType_[bpI] & LOCKED)
				vertexType_[bpI] ^= LOCKED;
	}

	void meshSurfaceOptimizer::enforceConstraints(const word subsetName)
	{
		enforceConstraints_ = true;

		badPointsSubsetName_ = subsetName;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
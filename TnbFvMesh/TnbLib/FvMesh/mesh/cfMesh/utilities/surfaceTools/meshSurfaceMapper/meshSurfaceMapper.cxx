#include <meshSurfaceMapper.hxx>

#include <meshSurfaceEngine.hxx>
#include <meshSurfacePartitioner.hxx>
#include <triSurf.hxx>
#include <triSurfacePartitioner.hxx>
#include <demandDrivenData.hxx>
#include <meshOctree.hxx>
#include <Pstream.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshSurfaceMapper::createMeshSurfacePartitioner() const
	{
		surfaceEnginePartitionerPtr_ = new meshSurfacePartitioner(surfaceEngine_);
	}

	void meshSurfaceMapper::createTriSurfacePartitioner() const
	{
		surfPartitionerPtr_ = new triSurfacePartitioner(meshOctree_.surface());
	}

	void meshSurfaceMapper::clearOut()
	{
		if (deletePartitioner_)
			deleteDemandDrivenData(surfaceEnginePartitionerPtr_);
		deleteDemandDrivenData(surfPartitionerPtr_);
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	meshSurfaceMapper::meshSurfaceMapper
	(
		const meshSurfaceEngine& mse,
		const meshOctree& octree
	)
		:
		surfaceEngine_(mse),
		meshOctree_(octree),
		surfaceEnginePartitionerPtr_(NULL),
		deletePartitioner_(true),
		surfPartitionerPtr_(NULL)
	{
		if (Pstream::parRun())
		{
			//- allocate bpAtProcs and other addressing
			//- this is done here to prevent possible deadlocks
			surfaceEngine_.bpAtProcs();
		}
	}

	meshSurfaceMapper::meshSurfaceMapper
	(
		const meshSurfacePartitioner& mPart,
		const meshOctree& octree
	)
		:
		surfaceEngine_(mPart.surfaceEngine()),
		meshOctree_(octree),
		surfaceEnginePartitionerPtr_(&mPart),
		deletePartitioner_(false),
		surfPartitionerPtr_(NULL)
	{
		if (Pstream::parRun())
		{
			//- allocate bpAtProcs and other addressing
			//- this is done here to prevent possible deadlocks
			surfaceEngine_.bpAtProcs();
		}
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshSurfaceMapper::~meshSurfaceMapper()
	{
		clearOut();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
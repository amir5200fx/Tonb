#include <meshOctreeAutomaticRefinement.hxx>

#include <demandDrivenData.hxx>
#include <triSurfacePartitioner.hxx>
#include <triSurfaceCurvatureEstimator.hxx>
#include <meshOctreeAddressing.hxx>
#include <IOdictionary.hxx>
#include <triSurf.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	void meshOctreeAutomaticRefinement::createOctreeAddressing() const
	{
		octreeAddressingPtr_ =
			new meshOctreeAddressing(octree_, meshDict_, useDATABoxes_);
	}

	const meshOctreeAddressing& meshOctreeAutomaticRefinement::octreeAddressing()
		const
	{
		if (!octreeAddressingPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const meshOctreeAddressing& meshOctreeAutomaticRefinement"
					"::octreeAddressing() const"
				) << "Cannot calculate addressing!" << abort(FatalError);
# endif

			createOctreeAddressing();
		}

		return *octreeAddressingPtr_;
	}

	void meshOctreeAutomaticRefinement::createSurfacePartitioner() const
	{
		partitionerPtr_ = new triSurfacePartitioner(octree_.surface());
	}

	const triSurfacePartitioner& meshOctreeAutomaticRefinement::partitioner() const
	{
		if (!partitionerPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const triSurfacePartitioner& meshOctreeAutomaticRefinement"
					"::partitioner() const"
				) << "Cannot calculate addressing!" << abort(FatalError);
# endif

			createSurfacePartitioner();
		}

		return *partitionerPtr_;
	}

	void meshOctreeAutomaticRefinement::createCurvatureEstimator() const
	{
		curvaturePtr_ = new triSurfaceCurvatureEstimator(octree_.surface());
	}

	const triSurfaceCurvatureEstimator& meshOctreeAutomaticRefinement::curvature()
		const
	{
		if (!curvaturePtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const triSurfaceCurvatureEstimator& "
					"meshOctreeAutomaticRefinement::curvature() const"
				) << "Cannot calculate addressing!" << abort(FatalError);
# endif

			createCurvatureEstimator();
		}

		return *curvaturePtr_;
	}

	void meshOctreeAutomaticRefinement::setMaxRefLevel()
	{
		const boundBox& rootBox = octree_.rootBox();
		const scalar size = rootBox.max().x() - rootBox.min().x();
		maxRefLevel_ = 0;

		if (meshDict_.found("minCellSize"))
		{
			const scalar maxSize(readScalar(meshDict_.lookup("maxCellSize")));
			scalar cs(readScalar(meshDict_.lookup("minCellSize")));
			cs *= (1.0 + SMALL);

			if (cs > maxSize)
				return;

			bool finished;
			do
			{
				finished = false;

				const scalar lSize = size / pow(2, label(maxRefLevel_));

				if (lSize < cs)
				{
					finished = true;
				}
				else
				{
					++maxRefLevel_;
				}
			} while (!finished);

			useDATABoxes_ = true;

			Info << "Requested min cell size corresponds to octree level "
				<< label(maxRefLevel_) << endl;
		}
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from surface and IOdictionary
	meshOctreeAutomaticRefinement::meshOctreeAutomaticRefinement
	(
		meshOctree& mo,
		const IOdictionary& dict,
		bool useDATABoxes
	)
		:
		octree_(mo),
		meshDict_(dict),
		useDATABoxes_(useDATABoxes),
		hexRefinement_(false),
		octreeAddressingPtr_(NULL),
		partitionerPtr_(NULL),
		curvaturePtr_(NULL),
		maxRefLevel_(0)
	{
		if (!useDATABoxes_ && dict.found("keepCellsIntersectingBoundary"))
		{
			useDATABoxes_ = readBool(dict.lookup("keepCellsIntersectingBoundary"));
		}

		//- calculate maximum allowed refinement level from the minimum cell size
		setMaxRefLevel();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshOctreeAutomaticRefinement::~meshOctreeAutomaticRefinement()
	{
		deleteDemandDrivenData(octreeAddressingPtr_);
		deleteDemandDrivenData(curvaturePtr_);
		deleteDemandDrivenData(partitionerPtr_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
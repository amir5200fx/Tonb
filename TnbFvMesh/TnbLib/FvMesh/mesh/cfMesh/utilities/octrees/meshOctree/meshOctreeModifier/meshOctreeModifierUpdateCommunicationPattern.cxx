#include <meshOctreeModifier.hxx>

#include <HashSet.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

//#define OCTREETiming
//#define OCTREE_DEBUG

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshOctreeModifier::updateCommunicationPattern()
	{
# ifdef OCTREETiming
		const scalar startTime = omp_get_wtime();
# endif

		const LongList<meshOctreeCube*>& leaves = octree_.leaves_;

		//- create the list which contains ranges of addresses at a given processor
		List<Pair<meshOctreeCubeCoordinates> > range(Pstream::nProcs());

		//- create the range for the current processor
		range[Pstream::myProcNo()].first() = leaves[0]->coordinates();
		range[Pstream::myProcNo()].second() =
			leaves[leaves.size() - 1]->coordinates();

		//- communicate missing ranges
		Pstream::gatherList(range);
		Pstream::scatterList(range);

		//- find missing child cubes in the tree. These coordinates are located on
		//- other processors, and they must fit in the range of cubes located
		//- on that processor.
		LongList<meshOctreeCubeCoordinates> migratedCubes;
		octree_.initialCubePtr_->findCoordinatesOfMissingCubes(migratedCubes);

		labelHashSet newNeiProcs;
		forAll(migratedCubes, mcI)
		{
			const meshOctreeCubeCoordinates& cc = migratedCubes[mcI];
			forAll(range, procI)
			{
				if (procI == Pstream::myProcNo())
					continue;

				if ((cc >= range[procI].first()) && (cc <= range[procI].second()))
					newNeiProcs.insert(procI);
			}
		}

		//- create new neighbour procs and their range
		octree_.neiProcs_ = newNeiProcs.toc();

		octree_.neiRange_.setSize(octree_.neiProcs_.size());
		forAll(octree_.neiProcs_, i)
			octree_.neiRange_[i] = range[octree_.neiProcs_[i]];

# ifdef OCTREETiming
		Info << "Time for updating communication pattern "
			<< (omp_get_wtime() - startTime) << endl;
# endif
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
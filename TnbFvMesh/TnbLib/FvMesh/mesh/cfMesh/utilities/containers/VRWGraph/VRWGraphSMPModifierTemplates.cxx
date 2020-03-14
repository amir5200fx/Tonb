#include <VRWGraphSMPModifier.hxx>

#include <labelPair.hxx>
#include <DynList.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class ListType>
	void VRWGraphSMPModifier::setSizeAndRowSize(const ListType& s)
	{
		graph_.rows_.setSize(s.size());

# ifdef USE_OMP
		label nThreads = 3 * omp_get_num_procs();
		if (s.size() < 1000)
			nThreads = 1;
# else
		const label nThreads(1);
# endif

		label nEntries(0);
		DynList<label> procEntries;
		procEntries.setSize(nThreads);

# ifdef USE_OMP
# pragma omp parallel num_threads(nThreads)
# endif
		{
# ifdef USE_OMP
			label& nLocalEntries = procEntries[omp_get_thread_num()];
# else
			label& nLocalEntries = procEntries[0];
# endif
			nLocalEntries = 0;

# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(s, i)
				nLocalEntries += s[i];

# ifdef USE_OMP
# pragma omp critical
# endif
			nEntries += nLocalEntries;

# ifdef USE_OMP
# pragma omp barrier

# pragma omp master
# endif
			{
				graph_.data_.setSize(nEntries);
			}

# ifdef USE_OMP
# pragma omp barrier
# endif

			label start(0);
# ifdef USE_OMP
			for (label i = 0; i < omp_get_thread_num(); ++i)
				start += procEntries[i];
# endif

# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(s, i)
			{
				graph_.rows_[i].start() = start;
				graph_.rows_[i].size() = s[i];
				start += s[i];
			}
		}
	}

	template<class GraphType>
	void VRWGraphSMPModifier::reverseAddressing(const GraphType& origGraph)
	{
		graph_.setSize(0);
		labelLongList nAppearances;

# ifdef USE_OMP
		label nThreads = 3 * omp_get_num_procs();
		if (origGraph.size() < 1000)
			nThreads = 1;
# else
		const label nThreads(1);
# endif

		label minRow(INT_MAX), maxRow(-1);
		List<List<LongList<labelPair> > > dataForOtherThreads(nThreads);

# ifdef USE_OMP
# pragma omp parallel num_threads(nThreads)
# endif
		{
# ifdef USE_OMP
			const label threadI = omp_get_thread_num();
# else
			const label threadI(0);
# endif

			List<LongList<labelPair> >& dot = dataForOtherThreads[threadI];
			dot.setSize(nThreads);

			//- find min and max entry in the graph
			//- they are used for assigning ranges of values local for each process
			label localMinRow(INT_MAX), localMaxRow(-1);
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(origGraph, rowI)
			{
				forAll(origGraph[rowI], i)
				{
					const label entryI = origGraph[rowI][i];
					localMaxRow = tnbLib::max(localMaxRow, entryI);
					localMinRow = tnbLib::min(localMinRow, entryI);
				}
			}

			++localMaxRow;

# ifdef USE_OMP
# pragma omp critical
# endif
			{
				minRow = tnbLib::min(minRow, localMinRow);
				maxRow = tnbLib::max(maxRow, localMaxRow);

				nAppearances.setSize(maxRow);
			}

# ifdef USE_OMP
# pragma omp barrier

			//- initialise appearances
# pragma omp for schedule(static)
# endif
			for (label i = 0; i < maxRow; ++i)
				nAppearances[i] = 0;

# ifdef USE_OMP
# pragma omp barrier
# endif

			const label range = (maxRow - minRow) / nThreads + 1;
			const label localMin = minRow + threadI * range;
			const label localMax = tnbLib::min(localMin + range, maxRow);

			//- find the number of appearances of each element in the original graph
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(origGraph, rowI)
			{
				forAll(origGraph[rowI], j)
				{
					const label entryI = origGraph[rowI][j];

					const label threadNo = (entryI - minRow) / range;

					if (threadNo == threadI)
					{
						++nAppearances[entryI];
					}
					else
					{
						dot[threadNo].append(labelPair(entryI, rowI));
					}
				}
			}

# ifdef USE_OMP
# pragma omp barrier
# endif

			//- count the appearances which are not local to the processor
			for (label i = 0; i < nThreads; ++i)
			{
				const LongList<labelPair>& data =
					dataForOtherThreads[i][threadI];

				forAll(data, j)
					++nAppearances[data[j].first()];
			}

# ifdef USE_OMP
# pragma omp barrier

			//- allocate graph
# pragma omp master
# endif
			setSizeAndRowSize(nAppearances);

# ifdef USE_OMP
# pragma omp barrier
# endif

			for (label i = localMin; i < localMax; ++i)
			{
				nAppearances[i] = 0;
			}

			//- start filling reverse addressing graph
			//- update data from processors with smaller labels
			for (label i = 0; i < threadI; ++i)
			{
				const LongList<labelPair>& data =
					dataForOtherThreads[i][threadI];

				forAll(data, j)
				{
					const label entryI = data[j].first();
					graph_(entryI, nAppearances[entryI]++) = data[j].second();
				}
			}

			//- update data local to the processor
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(origGraph, rowI)
			{
				forAll(origGraph[rowI], j)
				{
					const label entryI = origGraph[rowI][j];

					if ((entryI >= localMin) && (entryI < localMax))
						graph_(entryI, nAppearances[entryI]++) = rowI;
				}
			}

			//- update data from the processors with higher labels
			for (label i = threadI + 1; i < nThreads; ++i)
			{
				const LongList<labelPair>& data =
					dataForOtherThreads[i][threadI];

				forAll(data, j)
				{
					const label entryI = data[j].first();
					graph_(entryI, nAppearances[entryI]++) = data[j].second();
				}
			}
		}
	}

	template<class ListType, class GraphType>
	void VRWGraphSMPModifier::reverseAddressing
	(
		const ListType& mapper,
		const GraphType& origGraph
	)
	{
		ListType nAppearances;

# ifdef USE_OMP
		label nThreads = 3 * omp_get_num_procs();
		if (origGraph.size() < 1000)
			nThreads = 1;
# else
		const label nThreads(1);
# endif

		label minRow(INT_MAX), maxRow(-1);
		List<List<LongList<labelPair> > > dataForOtherThreads(nThreads);

# ifdef USE_OMP
# pragma omp parallel num_threads(nThreads)
# endif
		{
# ifdef USE_OMP
			const label threadI = omp_get_thread_num();
# else
			const label threadI(0);
# endif

			List<LongList<labelPair> >& dot = dataForOtherThreads[threadI];
			dot.setSize(nThreads);

			//- find min and max entry in the graph
			//- they are used for assigning ranges of values local for each process
			label localMinRow(INT_MAX), localMaxRow(-1);
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(origGraph, rowI)
			{
				forAll(origGraph[rowI], i)
				{
					const label entryI = mapper[origGraph[rowI][i]];
					localMaxRow = tnbLib::max(localMaxRow, entryI);
					localMinRow = tnbLib::min(localMinRow, entryI);
				}
			}

			++localMaxRow;

# ifdef USE_OMP
# pragma omp critical
# endif
			{
				minRow = tnbLib::min(minRow, localMinRow);
				maxRow = tnbLib::max(maxRow, localMaxRow);
				nAppearances.setSize(maxRow);
			}

# ifdef USE_OMP
# pragma omp barrier

			//- initialise appearances
# pragma omp for schedule(static)
# endif
			for (label i = 0; i < maxRow; ++i)
				nAppearances[i] = 0;

# ifdef USE_OMP
# pragma omp barrier
# endif

			const label range = (maxRow - minRow) / nThreads + 1;
			const label localMin = minRow + threadI * range;
			const label localMax = tnbLib::min(localMin + range, maxRow);

			//- find the number of appearances of each element in the original graph
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(origGraph, rowI)
			{
				forAll(origGraph[rowI], i)
				{
					const label entryI = mapper[origGraph[rowI][i]];

					const label threadNo = (entryI - minRow) / range;

					if (threadNo == threadI)
					{
						++nAppearances[entryI];
					}
					else
					{
						dot[threadNo].append(labelPair(entryI, rowI));
					}
				}
			}

# ifdef USE_OMP
# pragma omp barrier
# endif

			//- count the appearances which are not local to the processor
			for (label i = 0; i < nThreads; ++i)
			{
				const LongList<labelPair>& data =
					dataForOtherThreads[i][threadI];

				forAll(data, j)
					++nAppearances[data[j].first()];
			}

# ifdef USE_OMP
# pragma omp barrier

			//- allocate graph
# pragma omp master
# endif
			{
				setSizeAndRowSize(nAppearances);
			}

# ifdef USE_OMP
# pragma omp barrier
# endif

			for (label i = localMin; i < localMax; ++i)
			{
				nAppearances[i] = 0;
			}

			//- start filling reverse addressing graph
			//- update data from processors with smaller labels
			for (label i = 0; i < threadI; ++i)
			{
				const LongList<labelPair>& data =
					dataForOtherThreads[i][threadI];

				forAll(data, j)
				{
					const label entryI = data[j].first();
					graph_(entryI, nAppearances[entryI]++) = data[j].second();
				}
			}

			//- update data local to the processor
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(origGraph, rowI)
			{
				forAll(origGraph[rowI], j)
				{
					const label entryI = mapper[origGraph[rowI][j]];

					if ((entryI >= localMin) && (entryI < localMax))
						graph_(entryI, nAppearances[entryI]++) = rowI;
				}
			}

			//- update data from the processors with higher labels
			for (label i = threadI + 1; i < nThreads; ++i)
			{
				const LongList<labelPair>& data =
					dataForOtherThreads[i][threadI];

				forAll(data, j)
				{
					const label entryI = data[j].first();
					graph_(entryI, nAppearances[entryI]++) = data[j].second();
				}
			}
		}
	}

	template<class ListType>
	void VRWGraphSMPModifier::reverseAddressing
	(
		const ListType& mapper,
		const VRWGraph& origGraph
	)
	{
		ListType nAppearances;

# ifdef USE_OMP
		label nThreads = 3 * omp_get_num_procs();
		if (origGraph.size() < 1000)
			nThreads = 1;
# else
		const label nThreads(1);
# endif

		label minRow(INT_MAX), maxRow(-1);
		List<List<LongList<labelPair> > > dataForOtherThreads(nThreads);

# ifdef USE_OMP
# pragma omp parallel num_threads(nThreads)
# endif
		{
# ifdef USE_OMP
			const label threadI = omp_get_thread_num();
# else
			const label threadI(0);
# endif

			List<LongList<labelPair> >& dot = dataForOtherThreads[threadI];
			dot.setSize(nThreads);

			//- find min and max entry in the graph
			//- they are used for assigning ranges of values local for each process
			label localMinRow(INT_MAX), localMaxRow(-1);
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(origGraph, rowI)
			{
				forAllRow(origGraph, rowI, i)
				{
					const label entryI = mapper[origGraph(rowI, i)];
					localMaxRow = tnbLib::max(localMaxRow, entryI);
					localMinRow = tnbLib::min(localMinRow, entryI);
				}
			}

			++localMaxRow;

# ifdef USE_OMP
# pragma omp critical
# endif
			{
				minRow = tnbLib::min(minRow, localMinRow);
				maxRow = tnbLib::max(maxRow, localMaxRow);
				nAppearances.setSize(maxRow);
			}

# ifdef USE_OMP
# pragma omp barrier

			//- initialise appearances
# pragma omp for schedule(static)
# endif
			for (label i = 0; i < maxRow; ++i)
				nAppearances[i] = 0;

# ifdef USE_OMP
# pragma omp barrier
# endif

			const label range = (maxRow - minRow) / nThreads + 1;
			const label localMin = minRow + threadI * range;
			const label localMax = tnbLib::min(localMin + range, maxRow);

			//- find the number of appearances of each element in the original graph
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(origGraph, rowI)
			{
				forAllRow(origGraph, rowI, i)
				{
					const label entryI = mapper[origGraph(rowI, i)];

					const label threadNo = (entryI - minRow) / range;

					if (threadNo == threadI)
					{
						++nAppearances[entryI];
					}
					else
					{
						dot[threadNo].append(labelPair(entryI, rowI));
					}
				}
			}

# ifdef USE_OMP
# pragma omp barrier
# endif

			//- count the appearances which are not local to the processor
			for (label i = 0; i < nThreads; ++i)
			{
				const LongList<labelPair>& data =
					dataForOtherThreads[i][threadI];

				forAll(data, j)
					++nAppearances[data[j].first()];
			}

# ifdef USE_OMP
# pragma omp barrier

			//- allocate graph
# pragma omp master
# endif
			{
				setSizeAndRowSize(nAppearances);
			}

# ifdef USE_OMP
# pragma omp barrier
# endif
			for (label i = localMin; i < localMax; ++i)
				nAppearances[i] = 0;

			//- start filling reverse addressing graph
			//- update data from processors with smaller labels
			for (label i = 0; i < threadI; ++i)
			{
				const LongList<labelPair>& data =
					dataForOtherThreads[i][threadI];

				forAll(data, j)
				{
					const label entryI = data[j].first();
					graph_(entryI, nAppearances[entryI]++) = data[j].second();
				}
			}

			//- update data local to the processor
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(origGraph, rowI)
			{
				forAllRow(origGraph, rowI, j)
				{
					const label entryI = mapper[origGraph(rowI, j)];

					if ((entryI >= localMin) && (entryI < localMax))
						graph_(entryI, nAppearances[entryI]++) = rowI;
				}
			}

			//- update data from the processors with higher labels
			for (label i = threadI + 1; i < nThreads; ++i)
			{
				const LongList<labelPair>& data =
					dataForOtherThreads[i][threadI];

				forAll(data, j)
				{
					const label entryI = data[j].first();
					graph_(entryI, nAppearances[entryI]++) = data[j].second();
				}
			}
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
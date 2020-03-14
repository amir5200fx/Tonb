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

	VRWGraphSMPModifier::VRWGraphSMPModifier(VRWGraph& graph)
		:
		graph_(graph)
	{}

	VRWGraphSMPModifier::~VRWGraphSMPModifier()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void VRWGraphSMPModifier::mergeGraphs(const List<VRWGraph>& graphParts)
	{
		const label nGraphs = graphParts.size();
		const label nRows = graphParts[0].size();
		forAll(graphParts, i)
		{
			if (nRows != graphParts[i].size())
				FatalErrorIn
				(
					"inline void tnbLib::VRWGraph::mergeGraphs(const List<VRWGraph>&)"
				) << "Cannot merge graphs" << abort(FatalError);
		}

		//- find the number of elements in each row
		labelLongList nElmtsInRow(nRows);

# ifdef USE_OMP
# pragma omp parallel for schedule(static, 1)
# endif
		for (label rowI = 0; rowI < nRows; ++rowI)
		{
			label sum(0);
			for (label i = 0; i < nGraphs; ++i)
				sum += graphParts[i].sizeOfRow(rowI);

			nElmtsInRow[rowI] = sum;
		}

		//- set the size of graph
		setSizeAndRowSize(nElmtsInRow);

		//- Finally, assemble the merged graph
# ifdef USE_OMP
# pragma omp parallel for schedule(static, 1)
# endif
		for (label rowI = 0; rowI < nRows; ++rowI)
		{
			forAll(graphParts, i)
			{
				const VRWGraph& gp = graphParts[i];
				for (label j = 0; j < gp.sizeOfRow(rowI); ++j)
					graph_(rowI, --nElmtsInRow[rowI]) = gp(rowI, j);
			}
		}
	}

	void VRWGraphSMPModifier::reverseAddressing(const VRWGraph& origGraph)
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
				forAllRow(origGraph, rowI, i)
				{
					const label entryI = origGraph(rowI, i);
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
# endif

			//- initialise appearances
# ifdef USE_OMP
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
				forAllRow(origGraph, rowI, j)
				{
					const label entryI = origGraph(rowI, j);

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
# endif

			//- allocate graph
# ifdef USE_OMP
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
				forAllRow(origGraph, rowI, j)
				{
					const label entryI = origGraph(rowI, j);

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

	void VRWGraphSMPModifier::optimizeMemoryUsage()
	{
# ifdef USE_OMP
		label nThreads = 3 * omp_get_num_procs();
		if (graph_.size() < 1000)
			nThreads = 1;
# else
		const label nThreads(1);
# endif

		DynList<label> nRows, nEntries;
		nRows.setSize(nThreads);
		nEntries.setSize(nThreads);

		LongList<rowElement> newRows;
		labelLongList newData;

# ifdef USE_OMP
# pragma omp parallel num_threads(nThreads)
# endif
		{
# ifdef USE_OMP
			const label threadI = omp_get_thread_num();
# else
			const label threadI(0);
# endif
			nRows[threadI] = 0;
			nEntries[threadI] = 0;

# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(graph_.rows_, rowI)
			{
				if (graph_.rows_[rowI].start() == VRWGraph::INVALIDROW)
					continue;

				++nRows[threadI];
				nEntries[threadI] += graph_.rows_[rowI].size();
			}

# ifdef USE_OMP
# pragma omp barrier

# pragma omp master
# endif
			{
				//- find the number of rows
				label counter(0);
				forAll(nRows, i)
					counter += nRows[i];

				newRows.setSize(counter);

				//- find the number of data entries
				counter = 0;
				forAll(nEntries, i)
					counter += nEntries[i];

				newData.setSize(counter);
			}

# ifdef USE_OMP
# pragma omp barrier
# endif

			//- find the starting position for each thread
			label rowStart(0), entryStart(0);
			for (label i = 0; i < threadI; ++i)
			{
				rowStart += nRows[i];
				entryStart += nEntries[i];
			}

			//- copy the data into the location
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
			forAll(graph_, rowI)
			{
				rowElement& el = newRows[rowStart];
				el.start() += entryStart;
				++rowStart;

				el.size() = graph_.sizeOfRow(rowI);
				forAllRow(graph_, rowI, i)
				{
					newData[entryStart] = graph_(rowI, i);
					++entryStart;
				}
			}
		}

		//- replace the original data with the compressed data
		graph_.rows_.transfer(newRows);
		graph_.data_.transfer(newData);
	}

	void VRWGraphSMPModifier::operator=(const VRWGraph& og)
	{
		graph_.data_.setSize(og.data_.size());
		graph_.rows_.setSize(og.rows_.size());

# ifdef USE_OMP
# pragma omp parallel
# endif
		{
# ifdef USE_OMP
# pragma omp for schedule(static, 1)
# endif
			forAll(graph_.data_, i)
				graph_.data_[i] = og.data_[i];

# ifdef USE_OMP
# pragma omp for schedule(static, 1)
# endif
			forAll(graph_.rows_, rowI)
				graph_.rows_[rowI] = og.rows_[rowI];
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
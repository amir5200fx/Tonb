#include <ProcessorTopologyTemplate.hxx>

#include <ListOps.hxx>
#include <Pstream.hxx>
#include <commSchedule.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Patch, class ProcPatch>
tnbLib::labelList tnbLib::ProcessorTopology<Patch, ProcPatch>::procNeighbours
(
	const PtrList<Patch>& patches
)
{
	// Determine number of processor neighbours and max neighbour id.

	label nNeighbours = 0;

	label maxNb = 0;

	forAll(patches, patchi)
	{
		const Patch& patch = patches[patchi];

		if (isA<ProcPatch>(patch))
		{
			const ProcPatch& procPatch =
				refCast<const ProcPatch>(patch);

			nNeighbours++;

			maxNb = max(maxNb, procPatch.neighbProcNo());
		}
	}

	labelList neighbours(nNeighbours);

	procPatchMap_.setSize(maxNb + 1);
	procPatchMap_ = -1;

	nNeighbours = 0;

	forAll(patches, patchi)
	{
		const Patch& patch = patches[patchi];

		if (isA<ProcPatch>(patch))
		{
			const ProcPatch& procPatch =
				refCast<const ProcPatch>(patch);

			neighbours[nNeighbours++] = procPatch.neighbProcNo();

			// Construct reverse map
			procPatchMap_[procPatch.neighbProcNo()] = patchi;
		}
	}

	return neighbours;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
template<class Patch, class ProcPatch>
tnbLib::ProcessorTopology<Patch, ProcPatch>::ProcessorTopology
(
	const PtrList<Patch>& patches
)
	:
	labelListList(Pstream::nProcs()),
	patchSchedule_(2 * patches.size())
{
	if (Pstream::parRun())
	{
		// Fill my 'slot' with my neighbours
		operator[](Pstream::myProcNo()) = procNeighbours(patches);

		// Distribute to all processors
		Pstream::gatherList(*this);
		Pstream::scatterList(*this);
	}

	if (Pstream::parRun() && Pstream::defaultCommsType() == Pstream::scheduled)
	{
		label patchEvali = 0;

		// 1. All non-processor patches
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		forAll(patches, patchi)
		{
			if (!isA<ProcPatch>(patches[patchi]))
			{
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = true;
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = false;
			}
		}

		// 2. All processor patches
		// ~~~~~~~~~~~~~~~~~~~~~~~~

		// Determine the schedule for all. Insert processor pair once
		// to determine the schedule. Each processor pair stands for both
		// send and receive.
		label nComms = 0;
		forAll(*this, procI)
		{
			nComms += operator[](procI).size();
		}
		DynamicList<labelPair> comms(nComms);

		forAll(*this, procI)
		{
			const labelList& nbrs = operator[](procI);

			forAll(nbrs, i)
			{
				if (procI < nbrs[i])
				{
					comms.append(labelPair(procI, nbrs[i]));
				}
			}
		}
		comms.shrink();

		// Determine a schedule.
		labelList mySchedule
		(
			commSchedule
			(
				Pstream::nProcs(),
				comms
			).procSchedule()[Pstream::myProcNo()]
		);

		forAll(mySchedule, iter)
		{
			label commI = mySchedule[iter];

			// Get the other processor
			label nb = comms[commI][0];
			if (nb == Pstream::myProcNo())
			{
				nb = comms[commI][1];
			}
			label patchi = procPatchMap_[nb];

			if (Pstream::myProcNo() > nb)
			{
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = true;
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = false;
			}
			else
			{
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = false;
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = true;
			}
		}
	}
	else
	{
		label patchEvali = 0;

		// 1. All non-processor patches
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		// Have evaluate directly after initEvaluate. Could have them separated
		// as long as they're not intermingled with processor patches since
		// then e.g. any reduce parallel traffic would interfere with the
		// processor swaps.

		forAll(patches, patchi)
		{
			if (!isA<ProcPatch>(patches[patchi]))
			{
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = true;
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = false;
			}
		}

		// 2. All processor patches
		// ~~~~~~~~~~~~~~~~~~~~~~~~

		// 2a. initEvaluate
		forAll(patches, patchi)
		{
			if (isA<ProcPatch>(patches[patchi]))
			{
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = true;
			}
		}

		// 2b. evaluate
		forAll(patches, patchi)
		{
			if (isA<ProcPatch>(patches[patchi]))
			{
				patchSchedule_[patchEvali].patch = patchi;
				patchSchedule_[patchEvali++].init = false;
			}
		}
	}
}


// ************************************************************************* //
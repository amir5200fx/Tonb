#include <Pstream.hxx>

#include <PstreamReduceOps.hxx>
#include <tnbDebug.hxx>
#include <dictionary.hxx>
#include <OSspecific.hxx>
#include <IOstreams.hxx>

#include <mpi.h>

#include <cstring>
#include <cstdlib>
#include <csignal>

#if defined(WM_SP)
#   define MPI_SCALAR MPI_FLOAT
#elif defined(WM_DP)
#   define MPI_SCALAR MPI_DOUBLE
#elif defined(WM_LDP)
#   define MPI_SCALAR MPI_LONG_DOUBLE
#endif


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::Pstream, 0);

template<>
const char* tnbLib::NamedEnum<tnbLib::Pstream::commsTypes, 3>::names[] =
{
	"blocking",
	"scheduled",
	"nonBlocking"
};

const tnbLib::NamedEnum<tnbLib::Pstream::commsTypes, 3>
tnbLib::Pstream::commsTypeNames;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::Pstream::setParRun()
{
	parRun_ = true;

	Pout.prefix() = '[' + name(myProcNo()) + "] ";
	Perr.prefix() = '[' + name(myProcNo()) + "] ";
}


void tnbLib::Pstream::calcLinearComm(const label nProcs)
{
	linearCommunication_.setSize(nProcs);

	// Master
	labelList belowIDs(nProcs - 1);
	forAll(belowIDs, i)
	{
		belowIDs[i] = i + 1;
	}

	linearCommunication_[0] = commsStruct
	(
		nProcs,
		0,
		-1,
		belowIDs,
		labelList(0)
	);

	// Slaves. Have no below processors, only communicate up to master
	for (label procID = 1; procID < nProcs; procID++)
	{
		linearCommunication_[procID] = commsStruct
		(
			nProcs,
			procID,
			0,
			labelList(0),
			labelList(0)
		);
	}
}


// Append my children (and my children children etc.) to allReceives.
void tnbLib::Pstream::collectReceives
(
	const label procID,
	const List<dynamicLabelList >& receives,
	dynamicLabelList& allReceives
)
{
	const dynamicLabelList& myChildren = receives[procID];

	forAll(myChildren, childI)
	{
		allReceives.append(myChildren[childI]);
		collectReceives(myChildren[childI], receives, allReceives);
	}
}


// Tree like schedule. For 8 procs:
// (level 0)
//      0 receives from 1
//      2 receives from 3
//      4 receives from 5
//      6 receives from 7
// (level 1)
//      0 receives from 2
//      4 receives from 6
// (level 2)
//      0 receives from 4
//
// The sends/receives for all levels are collected per processor (one send per
// processor; multiple receives possible) creating a table:
//
// So per processor:
// proc     receives from   sends to
// ----     -------------   --------
//  0       1,2,4           -
//  1       -               0
//  2       3               0
//  3       -               2
//  4       5               0
//  5       -               4
//  6       7               4
//  7       -               6
void tnbLib::Pstream::calcTreeComm(label nProcs)
{
	label nLevels = 1;
	while ((1 << nLevels) < nProcs)
	{
		nLevels++;
	}

	List<dynamicLabelList > receives(nProcs);
	labelList sends(nProcs, -1);

	// Info<< "Using " << nLevels << " communication levels" << endl;

	label offset = 2;
	label childOffset = offset / 2;

	for (label level = 0; level < nLevels; level++)
	{
		label receiveID = 0;
		while (receiveID < nProcs)
		{
			// Determine processor that sends and we receive from
			label sendID = receiveID + childOffset;

			if (sendID < nProcs)
			{
				receives[receiveID].append(sendID);
				sends[sendID] = receiveID;
			}

			receiveID += offset;
		}

		offset <<= 1;
		childOffset <<= 1;
	}

	// For all processors find the processors it receives data from
	// (and the processors they receive data from etc.)
	List<dynamicLabelList > allReceives(nProcs);
	for (label procID = 0; procID < nProcs; procID++)
	{
		collectReceives(procID, receives, allReceives[procID]);
	}


	treeCommunication_.setSize(nProcs);

	for (label procID = 0; procID < nProcs; procID++)
	{
		treeCommunication_[procID] = commsStruct
		(
			nProcs,
			procID,
			sends[procID],
			receives[procID].shrink(),
			allReceives[procID].shrink()
		);
	}
}


// Callback from Pstream::init() : initialize linear and tree communication
// schedules now that nProcs is known.
void tnbLib::Pstream::initCommunicationSchedule()
{
	calcLinearComm(nProcs());
	calcTreeComm(nProcs());
}


// NOTE:
// valid parallel options vary between implementations, but flag common ones.
// if they are not removed by MPI_Init(), the subsequent argument processing
// will notice that they are wrong
void tnbLib::Pstream::addValidParOptions(HashTable<string>& validParOptions)
{
	validParOptions.insert("np", "");
	validParOptions.insert("p4pg", "PI file");
	validParOptions.insert("p4wd", "directory");
	validParOptions.insert("p4amslave", "");
	validParOptions.insert("p4yourname", "hostname");
	validParOptions.insert("GAMMANP", "number of instances");
	validParOptions.insert("machinefile", "machine file");
}


bool tnbLib::Pstream::init(int& argc, char**& argv)
{
	MPI_Init(&argc, &argv);

	int numprocs;
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myProcNo_);

	if (numprocs <= 1)
	{
		FatalErrorIn("Pstream::init(int& argc, char**& argv)")
			<< "bool Pstream::init(int& argc, char**& argv) : "
			"attempt to run parallel on 1 processor"
			<< tnbLib::abort(FatalError);
	}

	procIDs_.setSize(numprocs);

	forAll(procIDs_, procNo)
	{
		procIDs_[procNo] = procNo;
	}

	setParRun();

#   ifndef SGIMPI
	string bufferSizeName = getEnv("MPI_BUFFER_SIZE");

	if (bufferSizeName.size())
	{
		int bufferSize = atoi(bufferSizeName.c_str());

		if (bufferSize)
		{
			MPI_Buffer_attach(new char[bufferSize], bufferSize);
		}
	}
	else
	{
		FatalErrorIn("Pstream::init(int& argc, char**& argv)")
			<< "Pstream::init(int& argc, char**& argv) : "
			<< "environment variable MPI_BUFFER_SIZE not defined"
			<< tnbLib::abort(FatalError);
	}
#   endif

	int processorNameLen;
	char processorName[MPI_MAX_PROCESSOR_NAME];

	MPI_Get_processor_name(processorName, &processorNameLen);

	//signal(SIGABRT, stop);

	// Now that nprocs is known construct communication tables.
	initCommunicationSchedule();

	return true;
}


void tnbLib::Pstream::exit(int errnum)
{
#   ifndef SGIMPI
	int size;
	char* buff;
	MPI_Buffer_detach(&buff, &size);
	delete[] buff;
#   endif

	if (errnum == 0)
	{
		MPI_Finalize();
		::exit(errnum);
	}
	else
	{
		MPI_Abort(MPI_COMM_WORLD, errnum);
	}
}


void tnbLib::Pstream::abort()
{
	MPI_Abort(MPI_COMM_WORLD, 1);
}


void tnbLib::reduce(scalar& Value, const sumOp<scalar>& bop)
{
	if (!Pstream::parRun())
	{
		return;
	}

	if (Pstream::nProcs() <= Pstream::nProcsSimpleSum())
	{
		if (Pstream::master())
		{
			for
				(
					int slave = Pstream::firstSlave();
					slave <= Pstream::lastSlave();
					slave++
					)
			{
				scalar value;

				if
					(
						MPI_Recv
						(
							&value,
							1,
							MPI_SCALAR,
							Pstream::procID(slave),
							Pstream::msgType(),
							MPI_COMM_WORLD,
							MPI_STATUS_IGNORE
						)
						)
				{
					FatalErrorIn
					(
						"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
					) << "MPI_Recv failed"
						<< tnbLib::abort(FatalError);
				}

				Value = bop(Value, value);
			}
		}
		else
		{
			if
				(
					MPI_Send
					(
						&Value,
						1,
						MPI_SCALAR,
						Pstream::procID(Pstream::masterNo()),
						Pstream::msgType(),
						MPI_COMM_WORLD
					)
					)
			{
				FatalErrorIn
				(
					"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
				) << "MPI_Send failed"
					<< tnbLib::abort(FatalError);
			}
		}


		if (Pstream::master())
		{
			for
				(
					int slave = Pstream::firstSlave();
					slave <= Pstream::lastSlave();
					slave++
					)
			{
				if
					(
						MPI_Send
						(
							&Value,
							1,
							MPI_SCALAR,
							Pstream::procID(slave),
							Pstream::msgType(),
							MPI_COMM_WORLD
						)
						)
				{
					FatalErrorIn
					(
						"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
					) << "MPI_Send failed"
						<< tnbLib::abort(FatalError);
				}
			}
		}
		else
		{
			if
				(
					MPI_Recv
					(
						&Value,
						1,
						MPI_SCALAR,
						Pstream::procID(Pstream::masterNo()),
						Pstream::msgType(),
						MPI_COMM_WORLD,
						MPI_STATUS_IGNORE
					)
					)
			{
				FatalErrorIn
				(
					"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
				) << "MPI_Recv failed"
					<< tnbLib::abort(FatalError);
			}
		}
	}
	else
	{
		scalar sum;
		MPI_Allreduce(&Value, &sum, 1, MPI_SCALAR, MPI_SUM, MPI_COMM_WORLD);
		Value = sum;

		/*
		int myProcNo = Pstream::myProcNo();
		int nProcs = Pstream::nProcs();

		//
		// receive from children
		//
		int level = 1;
		int thisLevelOffset = 2;
		int childLevelOffset = thisLevelOffset/2;
		int childProcId = 0;

		while
		(
			(childLevelOffset < nProcs)
		 && (myProcNo % thisLevelOffset) == 0
		)
		{
			childProcId = myProcNo + childLevelOffset;

			scalar value;

			if (childProcId < nProcs)
			{
				if
				(
					MPI_Recv
					(
						&value,
						1,
						MPI_SCALAR,
						Pstream::procID(childProcId),
						Pstream::msgType(),
						MPI_COMM_WORLD,
						MPI_STATUS_IGNORE
					)
				)
				{
					FatalErrorIn
					(
						"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
					)   << "MPI_Recv failed"
						<< tnbLib::abort(FatalError);
				}

				Value = bop(Value, value);
			}

			level++;
			thisLevelOffset <<= 1;
			childLevelOffset = thisLevelOffset/2;
		}

		//
		// send and receive from parent
		//
		if (!Pstream::master())
		{
			int parentId = myProcNo - (myProcNo % thisLevelOffset);

			if
			(
				MPI_Send
				(
					&Value,
					1,
					MPI_SCALAR,
					Pstream::procID(parentId),
					Pstream::msgType(),
					MPI_COMM_WORLD
				)
			)
			{
				FatalErrorIn
				(
					"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
				)   << "MPI_Send failed"
					<< tnbLib::abort(FatalError);
			}

			if
			(
				MPI_Recv
				(
					&Value,
					1,
					MPI_SCALAR,
					Pstream::procID(parentId),
					Pstream::msgType(),
					MPI_COMM_WORLD,
					MPI_STATUS_IGNORE
				)
			)
			{
				FatalErrorIn
				(
					"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
				)   << "MPI_Recv failed"
					<< tnbLib::abort(FatalError);
			}
		}


		//
		// distribute to my children
		//
		level--;
		thisLevelOffset >>= 1;
		childLevelOffset = thisLevelOffset/2;

		while (level > 0)
		{
			childProcId = myProcNo + childLevelOffset;

			if (childProcId < nProcs)
			{
				if
				(
					MPI_Send
					(
						&Value,
						1,
						MPI_SCALAR,
						Pstream::procID(childProcId),
						Pstream::msgType(),
						MPI_COMM_WORLD
					)
				)
				{
					FatalErrorIn
					(
						"reduce(scalar& Value, const sumOp<scalar>& sumOp)"
					)   << "MPI_Send failed"
						<< tnbLib::abort(FatalError);
				}
			}

			level--;
			thisLevelOffset >>= 1;
			childLevelOffset = thisLevelOffset/2;
		}
		*/
	}
}


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

// Initialise my process number to 0 (the master)
int tnbLib::Pstream::myProcNo_(0);


// By default this is not a parallel run
bool tnbLib::Pstream::parRun_(false);


// List of process IDs
tnbLib::List<int> tnbLib::Pstream::procIDs_(1, 0);


// Standard transfer message type
const int tnbLib::Pstream::msgType_(1);


// Linear communication schedule
tnbLib::List<tnbLib::Pstream::commsStruct> tnbLib::Pstream::linearCommunication_(0);


// Multi level communication schedule
tnbLib::List<tnbLib::Pstream::commsStruct> tnbLib::Pstream::treeCommunication_(0);


// Should compact transfer be used in which floats replace doubles
// reducing the bandwidth requirement at the expense of some loss
// in accuracy
const tnbLib::debug::optimisationSwitch
tnbLib::Pstream::floatTransfer
(
	"floatTransfer",
	0
);


// Number of processors at which the reduce algorithm changes from linear to
// tree
const tnbLib::debug::optimisationSwitch
tnbLib::Pstream::nProcsSimpleSum
(
	"nProcsSimpleSum",
	16
);


tnbLib::debug::optimisationSwitch
tnbLib::Pstream::defaultCommsType
(
	"commsType",
	//     "nonBlocking",
	//     "scheduled",
	"blocking",
	"blocking, nonBlocking, scheduled"
);


// ************************************************************************* //
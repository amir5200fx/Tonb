#include <OPstream.hxx>

#include <PstreamReduceOps.hxx>
#include <PstreamGlobals.hxx>

#include <mpi.h>

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::OPstream::~OPstream()
{
	if
		(
			!write
			(
				commsType_,
				toProcNo_,
				buf_.begin(),
				bufPosition_
			)
			)
	{
		FatalErrorIn("OPstream::~OPstream()")
			<< "MPI_Bsend cannot send outgoing message"
			<< tnbLib::abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::OPstream::write
(
	const commsTypes commsType,
	const int toProcNo,
	const char* buf,
	const std::streamsize bufSize
)
{
	bool transferFailed = true;

	if (commsType == blocking)
	{
		transferFailed = MPI_Bsend
		(
			const_cast<char*>(buf),
			bufSize,
			MPI_PACKED,
			procID(toProcNo),
			msgType(),
			MPI_COMM_WORLD
		);
	}
	else if (commsType == scheduled)
	{
		transferFailed = MPI_Send
		(
			const_cast<char*>(buf),
			bufSize,
			MPI_PACKED,
			procID(toProcNo),
			msgType(),
			MPI_COMM_WORLD
		);
	}
	else if (commsType == nonBlocking)
	{
		MPI_Request request;

		transferFailed = MPI_Isend
		(
			const_cast<char*>(buf),
			bufSize,
			MPI_PACKED,
			procID(toProcNo),
			msgType(),
			MPI_COMM_WORLD,
			&request
		);

		PstreamGlobals::OPstream_outstandingRequests_.append(request);
	}
	else
	{
		FatalErrorIn
		(
			"OPstream::write"
			"(const int fromProcNo, char* buf, std::streamsize bufSize)"
		) << "Unsupported communications type " << commsType
			<< tnbLib::abort(FatalError);
	}

	return !transferFailed;
}


void tnbLib::OPstream::waitRequests()
{
	if (PstreamGlobals::OPstream_outstandingRequests_.size())
	{
		if
			(
				MPI_Waitall
				(
					PstreamGlobals::OPstream_outstandingRequests_.size(),
					PstreamGlobals::OPstream_outstandingRequests_.begin(),
					MPI_STATUSES_IGNORE
				)
				)
		{
			FatalErrorIn
			(
				"OPstream::waitRequests()"
			) << "MPI_Waitall returned with error" << tnbLib::endl;
		}

		PstreamGlobals::OPstream_outstandingRequests_.clear();
	}
}


bool tnbLib::OPstream::finishedRequest(const label i)
{
	if (i >= PstreamGlobals::OPstream_outstandingRequests_.size())
	{
		FatalErrorIn
		(
			"OPstream::finishedRequest(const label)"
		) << "There are "
			<< PstreamGlobals::OPstream_outstandingRequests_.size()
			<< " outstanding send requests and you are asking for i=" << i
			<< nl
			<< "Maybe you are mixing blocking/non-blocking comms?"
			<< tnbLib::abort(FatalError);
	}

	int flag;
	MPI_Test
	(
		&PstreamGlobals::OPstream_outstandingRequests_[i],
		&flag,
		MPI_STATUS_IGNORE
	);

	return flag != 0;
}


// ************************************************************************* //
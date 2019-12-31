#include <IPstream.hxx>

#include <PstreamGlobals.hxx>

#include <mpi.h>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

tnbLib::IPstream::IPstream
(
	const commsTypes commsType,
	const int fromProcNo,
	const label bufSize,
	streamFormat format,
	versionNumber version
)
	:
	Pstream(commsType, bufSize),
	Istream(format, version),
	fromProcNo_(fromProcNo),
	messageSize_(0)
{
	setOpened();
	setGood();

	MPI_Status status;

	// If the buffer size is not specified, probe the incomming message
	// and set it
	if (!bufSize)
	{
		MPI_Probe(procID(fromProcNo_), msgType(), MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_BYTE, &messageSize_);

		buf_.setSize(messageSize_);
	}

	messageSize_ = read(commsType, fromProcNo_, buf_.begin(), buf_.size());

	if (!messageSize_)
	{
		FatalErrorIn
		(
			"IPstream::IPstream(const int fromProcNo, "
			"const label bufSize, streamFormat format, versionNumber version)"
		) << "read failed"
			<< tnbLib::abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::IPstream::read
(
	const commsTypes commsType,
	const int fromProcNo,
	char* buf,
	const std::streamsize bufSize
)
{
	if (commsType == blocking || commsType == scheduled)
	{
		MPI_Status status;

		if
			(
				MPI_Recv
				(
					buf,
					(int)bufSize,
					MPI_PACKED,
					procID(fromProcNo),
					msgType(),
					MPI_COMM_WORLD,
					&status
				)
				)
		{
			FatalErrorIn
			(
				"IPstream::read"
				"(const int fromProcNo, char* buf, std::streamsize bufSize)"
			) << "MPI_Recv cannot receive incomming message"
				<< tnbLib::abort(FatalError);

			return 0;
		}


		// Check size of message read

		label messageSize;
		MPI_Get_count(&status, MPI_BYTE, &messageSize);

		if (messageSize > bufSize)
		{
			FatalErrorIn
			(
				"IPstream::read"
				"(const int fromProcNo, char* buf, std::streamsize bufSize)"
			) << "buffer (" << label(bufSize)
				<< ") not large enough for incomming message ("
				<< messageSize << ')'
				<< tnbLib::abort(FatalError);
		}

		return messageSize;
	}
	else if (commsType == nonBlocking)
	{
		MPI_Request request;

		if
			(
				MPI_Irecv
				(
					buf,
					(int)bufSize,
					MPI_PACKED,
					procID(fromProcNo),
					msgType(),
					MPI_COMM_WORLD,
					&request
				)
				)
		{
			FatalErrorIn
			(
				"IPstream::read"
				"(const int fromProcNo, char* buf, std::streamsize bufSize)"
			) << "MPI_Recv cannot start non-blocking receive"
				<< tnbLib::abort(FatalError);

			return 0;
		}

		PstreamGlobals::IPstream_outstandingRequests_.append(request);

		return 1;
	}
	else
	{
		FatalErrorIn
		(
			"IPstream::read"
			"(const int fromProcNo, char* buf, std::streamsize bufSize)"
		) << "Unsupported communications type " << commsType
			<< tnbLib::abort(FatalError);

		return 0;
	}
}


void tnbLib::IPstream::waitRequests()
{
	if (PstreamGlobals::IPstream_outstandingRequests_.size())
	{
		if
			(
				MPI_Waitall
				(
					PstreamGlobals::IPstream_outstandingRequests_.size(),
					PstreamGlobals::IPstream_outstandingRequests_.begin(),
					MPI_STATUSES_IGNORE
				)
				)
		{
			FatalErrorIn
			(
				"IPstream::waitRequests()"
			) << "MPI_Waitall returned with error" << endl;
		}

		PstreamGlobals::IPstream_outstandingRequests_.clear();
	}
}


bool tnbLib::IPstream::finishedRequest(const label i)
{
	if (i >= PstreamGlobals::IPstream_outstandingRequests_.size())
	{
		FatalErrorIn
		(
			"IPstream::finishedRequest(const label)"
		) << "There are "
			<< PstreamGlobals::IPstream_outstandingRequests_.size()
			<< " outstanding send requests and you are asking for i=" << i
			<< nl
			<< "Maybe you are mixing blocking/non-blocking comms?"
			<< tnbLib::abort(FatalError);
	}

	int flag;
	MPI_Test
	(
		&PstreamGlobals::IPstream_outstandingRequests_[i],
		&flag,
		MPI_STATUS_IGNORE
	);

	return flag != 0;
}


// ************************************************************************* //
#include <PstreamGlobals.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	// Outstanding non-blocking operations.
	//! @cond fileScope
	DynamicList<MPI_Request> PstreamGlobals::IPstream_outstandingRequests_;
	DynamicList<MPI_Request> PstreamGlobals::OPstream_outstandingRequests_;
	//! @endcond

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
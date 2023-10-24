#include "Socket.hxx"

#include "SockAddr.hxx"
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Socket::Socket(const std::shared_ptr<SockAddr>& theAddr)
	: theAddr_(theAddr)
{
	const auto& addr = theAddr->Address();
	theDescriptor_ = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (theDescriptor_ == INVALID_SOCKET)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "socket failed with error: " + std::to_string(WSAGetLastError()) << endl
			<< abort(FatalError);
	}
}

#include "Socket.hxx"

#include "SockAddr.hxx"
#include "ServError.hxx"

unsigned short tnbLib::Socket::verbose = 0;

tnbLib::Socket::Socket(const std::shared_ptr<SockAddr>& theAddr)
	: theAddr_(theAddr)
{
	const auto& addr = theAddr->Address();
	theDescriptor_ = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (theDescriptor_ == INVALID_SOCKET)
	{
		throw ServError("socket failed with error: " + std::to_string(WSAGetLastError()));
	}
	if (verbose)
	{
		std::cout << "socket() is OK!" << std::endl;
	}
}

tnbLib::Socket::Socket(SOCKET theSocket)
	: theDescriptor_(theSocket)
{
}

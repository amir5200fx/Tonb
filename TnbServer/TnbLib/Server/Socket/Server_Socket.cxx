#include <Server_Socket.hxx>

#include <Server_SockAddr.hxx>
#include <Server_Error.hxx>

#include <iostream>

unsigned short tnbLib::Server_Socket::verbose = 0;

tnbLib::Server_Socket::Server_Socket(const std::shared_ptr<Server_SockAddr>& theAddr)
	: theAddr_(theAddr)
{
	const auto& addr = theAddr->Address();
	theDescriptor_ = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (theDescriptor_ == INVALID_SOCKET)
	{
		throw Server_Error("socket failed with error: " + std::to_string(WSAGetLastError()));
	}
	if (verbose)
	{
		std::cout << "socket() is OK!" << std::endl;
	}
}

tnbLib::Server_Socket::Server_Socket(SOCKET theSocket)
	: theDescriptor_(theSocket)
{}

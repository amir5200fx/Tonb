#include <Server_SockAddr_TCP.hxx>

#include <Server_Error.hxx>

#include <tchar.h>
#include <WS2tcpip.h>

tnbLib::Server_SockAddr_TCP::Server_SockAddr_TCP(int thePort, const std::string& theAddr)
{
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	// Resolve the server address and port
	const int iResult = getaddrinfo(NULL, std::to_string(thePort).c_str(), &hints, &theAddress_);
	if (iResult != 0)
	{
		throw Server_Error("getaddrinfo failed with error: " + std::to_string(iResult));
	}
}

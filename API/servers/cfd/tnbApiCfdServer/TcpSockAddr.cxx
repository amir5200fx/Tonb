#include "TcpSockAddr.hxx"

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <tchar.h>
#include <WS2tcpip.h>


tnbLib::TcpSockAddr::TcpSockAddr(int thePort, const std::string& theAddr)
{
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	int iResult = getaddrinfo(NULL, std::to_string(thePort).c_str(), &hints, &theAddress_);
	if (iResult != 0)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "getaddrinfo failed with error: " + std::to_string(iResult) << endl
			<< abort(FatalError);
	}
}

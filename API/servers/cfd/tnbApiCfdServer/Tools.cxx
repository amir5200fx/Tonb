#include "Tools.hxx"

#include "SockAddr.hxx"
#include "Socket.hxx"
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Tools::Bind(const std::shared_ptr<Socket>& theSocket)
{
	addrinfo* addr;// = theSocket->Address()->Address();
	const int result = bind(theSocket->Descriptor(), addr->ai_addr, static_cast<int>(addr->ai_addrlen));
	if (result == SOCKET_ERROR)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "bind failed with error: " + std::to_string(WSAGetLastError()) << endl
			<< abort(FatalError);
	}
}

void tnbLib::Tools::Listen(const std::shared_ptr<Socket>& theSocket)
{
	const int result = listen(theSocket->Descriptor(), SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "listen failed with error: " + std::to_string(WSAGetLastError()) << endl
			<< abort(FatalError);
	}
}

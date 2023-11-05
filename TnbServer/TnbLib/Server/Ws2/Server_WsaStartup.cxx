#include <Server_WsaStartup.hxx>

#include <Server_Error.hxx>

#ifdef max
#undef max
#endif // max

#ifdef min
#undef min
#endif // min

#include <iostream>
#include <tchar.h>
#include <winsock2.h>
#include <WS2tcpip.h>

unsigned short tnbLib::Server_WsaStartup::verbose(0);

tnbLib::Server_WsaStartup::Server_WsaStartup()
{
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		throw Server_Error("The Winsock dll not found!");
	}
	else
	{
		if (verbose)
		{
			std::cout << "The winsock dll found!" << std::endl;
			std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
		}
	}
}

tnbLib::Server_WsaStartup::~Server_WsaStartup()
{
	WSACleanup();
}
#include "WsaStartup.hxx"

#include <word.hxx>

#include <iostream>
#include <tchar.h>
#include <winsock2.h>
#include <WS2tcpip.h>

unsigned short tnbLib::WsaStartup::verbose(0);

tnbLib::WsaStartup::WsaStartup()
{
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		if (verbose)
		{
			std::cout << "The Winsock dll not found!" << std::endl;
		}
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

#pragma once
#ifndef _Server_WsaStartup_Header
#define _Server_WsaStartup_Header

#include <Server_Module.hxx>
#include <WinSock2.h>

namespace tnbLib
{

	class Server_WsaStartup
	{

		/*Private Data*/

		WSADATA theData_;

	public:

		static TnbServer_EXPORT unsigned short verbose;

		// default constructor

		TnbServer_EXPORT Server_WsaStartup();

		// Public functions and operators

		TnbServer_EXPORT ~Server_WsaStartup();

		const auto& Data() const { return theData_; }
		const auto& Status() const { return theData_.szSystemStatus; }
		
	};
}

#endif
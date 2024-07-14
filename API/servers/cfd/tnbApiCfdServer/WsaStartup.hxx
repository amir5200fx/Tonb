#pragma once
#ifndef _WsaStartup_Header
#define _WsaStartup_Header

#include <WinSock2.h>

namespace tnbLib
{

	class WsaStartup
	{

		/*Private Data*/

		WSADATA theData_;

	public:

		static unsigned short verbose;

		// default constructor

		WsaStartup();

		// constructors

		~WsaStartup();

		// Public functions and operators

		const auto& Data() const { return theData_; }
		const auto& Status() const { return theData_.szSystemStatus; }

	};
}

#endif
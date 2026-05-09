#pragma once
#ifndef _Server_SockAddr_TCP_Header
#define _Server_SockAddr_TCP_Header

#include <Server_SockAddr.hxx>

namespace tnbLib
{

	class Server_SockAddr_TCP
		: public Server_SockAddr
	{

		/*Private Data*/

	public:

		// constructors

		TnbServer_EXPORT explicit Server_SockAddr_TCP(int thePort = DEFAULT_PORT, const std::string & = THIS_PC);

		// Public functions and operators
		
	};
}

#endif
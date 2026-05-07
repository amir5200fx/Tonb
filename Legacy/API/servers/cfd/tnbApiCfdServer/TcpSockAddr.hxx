#pragma once
#ifndef _TcpSockAddr_Header
#define _TcpSockAddr_Header

#include "SockAddr.hxx"

namespace tnbLib
{

	class TcpSockAddr
		: public SockAddr
	{

		/*Private Data*/

	public:

		

		// constructors

		explicit TcpSockAddr(int thePort = DEFAULT_PORT, const std::string& = THIS_PC);

		// Public functions and operators

	};
}

#endif
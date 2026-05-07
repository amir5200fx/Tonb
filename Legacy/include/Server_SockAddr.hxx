#pragma once
#ifndef _Server_SockAddr_Header
#define _Server_SockAddr_Header

#include <Server_Module.hxx>
#include <Server_Ws2.hxx>

#include <string>

namespace tnbLib
{

	class Server_SockAddr
	{

		/*Private Data*/

	protected:

		addrinfo* theAddress_ = nullptr;

		Server_SockAddr() = default;

	public:

		static TnbServer_EXPORT const std::string THIS_PC;
		static TnbServer_EXPORT const int DEFAULT_PORT;

		// default constructor

		TnbServer_EXPORT ~Server_SockAddr();

		// Public functions and operators

		auto Address() const { return theAddress_; }
		
	};
}

#endif
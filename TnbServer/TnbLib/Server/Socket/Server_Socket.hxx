#pragma once
#ifndef _Server_Socket_Header
#define _Server_Socket_Header

#include <Server_Ws2.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Server_SockAddr;

	class Server_Socket
	{

	private:

		/*Private Data*/

		std::shared_ptr<Server_SockAddr> theAddr_;

		SOCKET theDescriptor_;

	public:

		static unsigned short verbose;

		Server_Socket(const std::shared_ptr<Server_SockAddr>&);
		Server_Socket(SOCKET theSocket);

		// Public functions and operators

		auto Descriptor() const { return theDescriptor_; }
		const auto& Address() const { return theAddr_; }

		void SetDescriptor(SOCKET theDescriptor) { theDescriptor_ = theDescriptor; }
		
	};
	
}

#endif
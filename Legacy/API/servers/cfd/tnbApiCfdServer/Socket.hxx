#pragma once
#ifndef _Socket_Header
#define _Socket_Header

#include "Ws2.hxx"

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SockAddr;

	class Socket
	{

	private:

		/*Private Data*/

		std::shared_ptr<SockAddr> theAddr_;

		SOCKET theDescriptor_;

	public:

		static unsigned short verbose;

		Socket(const std::shared_ptr<SockAddr>&);
		Socket(SOCKET theSocket);

		// Public functions and operators

		auto Descriptor() const { return theDescriptor_; }
		const auto& Address() const { return theAddr_; }

		void SetDescriptor(SOCKET theDescriptor) { theDescriptor_ = theDescriptor; }

	};

}

#endif

#pragma once
#ifndef _SockAddr_Header
#define _SockAddr_Header

#include "Ws2.hxx"

#include <memory>
#include <string>

namespace tnbLib
{

	class SockAddr
	{

	public:


	protected:

		/*Private Data*/

		addrinfo* theAddress_ = NULL;

	protected:

		SockAddr();

	public:

		~SockAddr();

		static const std::string THIS_PC;
		static const int DEFAULT_PORT;

		// Public functions and operators

		const auto& Address() const { return theAddress_; }

	};
}

#endif

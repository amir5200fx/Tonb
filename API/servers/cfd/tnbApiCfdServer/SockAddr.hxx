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

		/*Private Data*/

	protected:

		addrinfo* theAddress_ = NULL;

	protected:

		SockAddr();

	public:

		static const std::string THIS_PC;
		static const int DEFAULT_PORT;

		// default constructor

		

		~SockAddr();

		

		// Public functions and operators

		const auto& Address() const { return theAddress_; }

	};
}

#endif

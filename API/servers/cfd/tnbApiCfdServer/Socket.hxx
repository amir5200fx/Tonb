#pragma once
#ifndef _Socket_Header
#define _Socket_Header

#include <WinSock2.h>

namespace tnbLib
{

	class Socket
	{

		/*Private Data*/

		SOCKET theDescriptor_;

	protected:

		// default constructor

		Socket()
			: theDescriptor_(INVALID_SOCKET)
		{}

		// constructors

	public:

		// Public functions and operators

		auto Descriptor() const { return theDescriptor_; }
		bool IsValid() const;
		bool IsInvalid() const;

		void SetDescriptor(SOCKET theDescriptor) { theDescriptor_ = theDescriptor; }

	};
}

#endif

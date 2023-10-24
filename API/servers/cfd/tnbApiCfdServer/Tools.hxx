#pragma once
#ifndef _Tools_Header
#define _Tools_Header

#include <memory>

namespace tnbLib
{

	class Socket;

	class Tools
	{

	public:

		static void Bind(const std::shared_ptr<Socket>&);
		static void Listen(const std::shared_ptr<Socket>&);

	};
}

#endif

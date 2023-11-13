#pragma once
#ifndef _Server_Error_Header
#define _Server_Error_Header

#include <string>

namespace tnbLib
{

	class Server_Error
		: public std::exception
	{

		/*Private Data*/

		std::string theMessage_;

	public:

		explicit Server_Error(std::string msg)
			: theMessage_(std::move(msg))
		{}

		const char* what() const override { return theMessage_.c_str(); }
		
	};
}

#endif
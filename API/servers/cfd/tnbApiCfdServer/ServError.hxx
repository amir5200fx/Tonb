#pragma once
#ifndef _ServError_Header
#define _ServError_Header

#include <iostream>
#include <string>

namespace tnbLib
{

	class ServError
		: public std::exception
	{

		std::string theMessage_;

	public:

		explicit ServError(const std::string& msg)
			: theMessage_(msg)
		{}

		const char* what() const override { return theMessage_.c_str(); }

	};
}

#endif
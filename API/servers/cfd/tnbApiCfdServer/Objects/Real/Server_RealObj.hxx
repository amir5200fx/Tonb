#pragma once
#ifndef _Server_RealObj_Header
#define _Server_RealObj_Header

#include "../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_RealObj
		: public Server_Object
	{

	public:

		static const std::string commandName;

		// default constructor

		Server_RealObj()
		= default;

		// Public functions and operators

		void Construct(const std::string&) override;

	};
}

#endif

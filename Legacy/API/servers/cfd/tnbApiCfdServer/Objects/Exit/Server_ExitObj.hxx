#pragma once
#ifndef _Server_ExitObj_Header
#define _Server_ExitObj_Header

#include "../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_ExitObj
		: public Server_Object
	{

	public:

		static const std::string commandName;

		// default constructor

		Server_ExitObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;

	};
}

#endif
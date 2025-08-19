#pragma once
#ifndef _Server_IntObj_Header
#define _Server_IntObj_Header

#include "../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_IntObj
		: public Server_Object
	{

	public:

		static const std::string commandName;

		// default constructor

		Server_IntObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;

	};
}

#endif
#pragma once
#ifndef _Server_PntObj_Header
#define _Server_PntObj_Header

#include "../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_PntObj
		: public Server_Object
	{

	public:

		struct Params
		{
			static const std::string x;
			static const std::string y;
		};

		static const std::string commandName;

		// default constructor

		Server_PntObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;

	};
}

#endif
#pragma once
#ifndef _Server_DirObj_Header
#define _Server_DirObj_Header

#include "../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_DirObj
		: public Server_Object
	{

	public:

		struct Params
		{
			static const std::string u;
			static const std::string v;
		};

		static const std::string commandName;

		// default constructor

		Server_DirObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;

	};
}

#endif
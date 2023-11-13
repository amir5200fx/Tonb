#pragma once
#ifndef _Server_VecObj_Header
#define _Server_VecObj_Header

#include "../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_VecObj
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

		Server_VecObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;

	};
}

#endif
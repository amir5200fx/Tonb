#pragma once
#ifndef _Server_AxisObj_Header
#define _Server_AxisObj_Header

#include "../Object/Server_Object.hxx"

namespace tnbLib
{

	class Server_AxisObj
		: public Server_Object
	{

	public:

		struct Params
		{
			static const std::string centre;
			static const std::string dir;
		};

		static const std::string commandName;

		// default constructor

		Server_AxisObj()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;

	};
}

#endif
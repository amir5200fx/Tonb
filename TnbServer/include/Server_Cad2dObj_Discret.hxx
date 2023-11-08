#pragma once
#ifndef _Server_Cad2dObj_Discret_Header
#define _Server_Cad2dObj_Discret_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_Discret
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string object_type;
			static const std::string info;
			static const std::string object;
		};

		static const std::string command_name;

		Server_Cad2dObj_Discret() = default;

		void Construct(const std::string& theValue) override;

	};
}


#endif
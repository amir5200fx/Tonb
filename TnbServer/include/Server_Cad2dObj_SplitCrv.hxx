#pragma once
#ifndef _Server_Cad2dObj_SplitCrv_Header
#define _Server_Cad2dObj_SplitCrv_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_SplitCrv
		: public Server_Object
	{

		struct Params
		{
			static const std::string curve;
			static const std::string u;
		};

		static const std::string command_name;

		Server_Cad2dObj_SplitCrv() = default;

		void Construct(const std::string& theValue) override;
		void MakeEmpty() override;

	};
}

#endif
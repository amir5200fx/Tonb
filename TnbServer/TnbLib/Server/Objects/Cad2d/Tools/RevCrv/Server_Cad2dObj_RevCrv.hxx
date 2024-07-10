#pragma once
#ifndef _Server_Cad2dObj_RevCrv_Header
#define _Server_Cad2dObj_RevCrv_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_RevCrv
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string name;
			static const std::string curve;
		};

		static const std::string command_name;

		Server_Cad2dObj_RevCrv() = default;

		void Construct(const std::string& theValue) override;
		void MakeEmpty() override;
	};
}

#endif
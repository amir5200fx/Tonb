#pragma once
#ifndef _Server_Cad2dObj_CalcCrvLength_Info_Header
#define _Server_Cad2dObj_CalcCrvLength_Info_Header

#include <Server_Cad2dObj_CalcCrvLength.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_CalcCrvLength_Info
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string integ;
			static const std::string max_nb_subs;
			static const std::string ignore_non_conv;
			static const std::string shut_up_warnings;
			static const std::string verbose;
		};

		static const std::string command_name;

		Server_Cad2dObj_CalcCrvLength_Info() = default;

		void Construct(const std::string& theValue) override;
		void MakeEmpty() override;

	};
}

#endif
#pragma once
#ifndef _Server_Cad2dObj_CalcPntOnCurve_Header
#define _Server_Cad2dObj_CalcPntOnCurve_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_CalcPntOnCurve
		: public Server_Object
	{

	public:
		struct Params
		{
			static const std::string curve;
			static const std::string u;
		};

		static const std::string command_name;

		Server_Cad2dObj_CalcPntOnCurve() = default;

		void Construct(const std::string& theValue) override;


	};
}

#endif

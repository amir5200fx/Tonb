#pragma once
#ifndef _Server_Cad2dObj_Boolean_Subtract_F1_Header
#define _Server_Cad2dObj_Boolean_Subtract_F1_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_Boolean_Subtract_F1
		: public Server_Object
	{

		/*Private Data*/

	public:
		struct Params
		{
			static const std::string tol;
			static const std::string area;
			static const std::string target;
			static const std::string name;
		};

		static const std::string command_name;

		Server_Cad2dObj_Boolean_Subtract_F1() = default;

		void Construct(const std::string& theValue) override;
		void MakeEmpty() override;

	};
}

#endif
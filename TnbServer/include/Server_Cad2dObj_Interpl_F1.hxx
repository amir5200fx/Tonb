#pragma once
#ifndef _Server_Cad2dObj_Interpl_F1_Header
#define _Server_Cad2dObj_Interpl_F1_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_Interpl_F1
		: public Server_Object
	{

		/*Private Data*/

	public:

		struct Params
		{
			static const std::string pnt_list;
			static const std::string periodic;
			static const std::string tol;
			static const std::string name;
		};

		static TnbServer_EXPORT const std::string command_name;

		Server_Cad2dObj_Interpl_F1() = default;

		void Construct(const std::string& theValue) override;

	};
}

#endif
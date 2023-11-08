#pragma once
#ifndef _Server_Cad2dObj_Circle_F1_Header
#define _Server_Cad2dObj_Circle_F1_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Cad2dObj_Circle_F1
		: public Server_Object
	{

		/*Private Data*/

	public:
		struct Params
		{
			static const std::string axis;
			static const std::string radius;
			static const std::string name;
		};

		static TnbServer_EXPORT  const std::string command_name;

		// default constructor

		Server_Cad2dObj_Circle_F1() = default;

		// Public functions and operators

		TnbServer_EXPORT void Construct(const std::string& theValue) override;
		TnbServer_EXPORT void MakeEmpty() override;
		
	};
}

#endif
#pragma once
#ifndef _Server_Mesh2dObj_Header
#define _Server_Mesh2dObj_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Mesh2dObj_RefValues
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string base_size;
			static const std::string area;
		};

		Server_Mesh2dObj_RefValues() = default;

		static const std::string command_name;

		Server_Mesh2dObj_RefValues() = default;

		void Construct(const std::string& theValue) override;
	};


}

#endif
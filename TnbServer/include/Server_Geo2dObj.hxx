#pragma once
#ifndef _Server_Geo2dObj_Header
#define _Server_Geo2dObj_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_Geo2dObj_SizeMap_Uniform
		: public Server_Object
	{
	public:
		struct Params
		{
			static const std::string bnd_box;
			static const std::string size;
		};

		static const std::string command_name;

		Server_Geo2dObj_SizeMap_Uniform() = default;

		void Construct(const std::string& theValue) override;
	};
}

#endif
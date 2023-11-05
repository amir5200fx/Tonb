#pragma once
#ifndef _Server_GeoObj_Axis2d_Header
#define _Server_GeoObj_Axis2d_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_GeoObj_Axis2d
		: public Server_Object
	{

	public:

		struct Params
		{
			static const std::string centre;
			static const std::string dir;
		};

		static TnbServer_EXPORT const std::string command_name;

		// default constructor

		Server_GeoObj_Axis2d() = default;

		// Public functions and operators

		TnbServer_EXPORT void Construct(const std::string&) override;
		
	};
}

#endif
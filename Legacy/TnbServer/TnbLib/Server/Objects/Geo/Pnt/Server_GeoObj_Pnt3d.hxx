#pragma once
#ifndef _Server_GeoObj_Pnt3d_Header
#define _Server_GeoObj_Pnt3d_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_GeoObj_Pnt3d
		: public Server_Object
	{

	public:

		struct Params
		{
			static const std::string x;
			static const std::string y;
			static const std::string z;
		};

		static TnbServer_EXPORT const std::string command_name;

		// default constructor

		Server_GeoObj_Pnt3d()
			= default;

		// Public functions and operators

		TnbServer_EXPORT void Construct(const std::string&) override;

	};
}

#endif

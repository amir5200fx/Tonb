#pragma once
#ifndef _Server_GeoObj_Pnt2d_F1_Header
#define _Server_GeoObj_Pnt2d_F1_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_GeoObj_Pnt2d_F1
		: public Server_Object
	{

	public:

		struct Params
		{
			static const std::string x;
			static const std::string y;
		};

		static TnbServer_EXPORT const std::string command_name;

		// default constructor

		Server_GeoObj_Pnt2d_F1()
			= default;

		// Public functions and operators

		TnbServer_EXPORT void Construct(const std::string&) override;

	};
}

#endif
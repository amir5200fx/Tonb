#pragma once
#ifndef _Server_GeoObj_Pnt2d_Header
#define _Server_GeoObj_Pnt2d_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_GeoObj_Pnt2d_SetX
		: public Server_Object
	{
	public:

		struct Params
		{
			static const std::string point;
			static const std::string value;
		};

		static const std::string command_name;

		Server_GeoObj_Pnt2d_SetX() = default;

		void Construct(const std::string& theValue) override;
		
	};

	class Server_GeoObj_Pnt2d_SetY
		: public Server_Object
	{
	public:

		struct Params
		{
			static const std::string point;
			static const std::string value;
		};

		static const std::string command_name;

		Server_GeoObj_Pnt2d_SetY() = default;

		void Construct(const std::string& theValue) override;

	};

	defineTnbServerObject(Server_GeoObj_Pnt2d_F2);

	class Server_GeoObj_Pnt2d_Trsf
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(pnt);
		};
		constructTnbServerObject(Server_GeoObj_Pnt2d_Trsf);
	};
}

#endif
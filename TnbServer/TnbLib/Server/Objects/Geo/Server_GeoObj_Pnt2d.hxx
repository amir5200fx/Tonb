#pragma once
#ifndef _Server_GeoObj_Pnt2d_Header
#define _Server_GeoObj_Pnt2d_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_GeoObj_Pnt2d
		: public Server_Object
	{

	public:

		struct Params
		{
			static const std::string x;
			static const std::string y;
		};

		static const std::string command_name;

		// default constructor

		Server_GeoObj_Pnt2d()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;

	};
}

#endif
#pragma once
#ifndef _Server_GeoObj_Dir3d_Header
#define _Server_GeoObj_Dir3d_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_GeoObj_Dir3d
		: public Server_Object
	{

	public:

		struct Params
		{
			static const std::string u;
			static const std::string v;
			static const std::string w;
		};

		static const std::string command_name;

		// default constructor

		Server_GeoObj_Dir3d()
			= default;

		// Public functions and operators

		void Construct(const std::string&) override;

	};
}

#endif
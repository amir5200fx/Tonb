#pragma once
#ifndef _Server_GeoObj_Vec2d_F1_Header
#define _Server_GeoObj_Vec2d_F1_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_GeoObj_Vec2d_F1
		: public Server_Object
	{

	public:

		struct Params
		{
			static const std::string u;
			static const std::string v;
		};

		static TnbServer_EXPORT const std::string command_name;

		// default constructor

		Server_GeoObj_Vec2d_F1()
			= default;

		// Public functions and operators

		TnbServer_EXPORT void Construct(const std::string&) override;

	};

	class Server_GeoObj_Vec2d_DotProduct
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(u0);
			defineTnbServerParam(u1);
		};
		constructTnbServerObject(Server_GeoObj_Vec2d_DotProduct);
	};

	class Server_GeoObj_Vec2d_CrossProduct
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(u0);
			defineTnbServerParam(u1);
		};
		constructTnbServerObject(Server_GeoObj_Vec2d_CrossProduct);
	};

	defineTnbServerObject(Server_GeoObj_Vec2d_Cmpts);
}

#endif
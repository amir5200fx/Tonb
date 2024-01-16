#pragma once
#ifndef _Server_GeoObj_Ray2d_Header
#define _Server_GeoObj_Ray2d_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_GeoObj_Ray2d
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(pnt);
			defineTnbServerParam(vec);
		};

		constructTnbServerObject(Server_GeoObj_Ray2d);
	};

	class Server_GeoObj_Ray2d_Intersect
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(ray0);
			defineTnbServerParam(ray1);
		};

		constructTnbServerObject(Server_GeoObj_Ray2d_Intersect);
	};
}

#endif
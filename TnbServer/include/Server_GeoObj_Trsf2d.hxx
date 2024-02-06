#pragma once
#ifndef _Server_GeoObj_Trsf2d_Header
#define _Server_GeoObj_Trsf2d_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	defineTnbServerObject(Server_GeoObj_Trsf2d);

	class Server_GeoObj_Trsf2d_Mirror_By_Axis
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(axis);
		};
		constructTnbServerObject(Server_GeoObj_Trsf2d_Mirror_By_Axis);
	};

	class Server_GeoObj_Trsf2d_Mirror_By_Pnt
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(pnt);
		};
		constructTnbServerObject(Server_GeoObj_Trsf2d_Mirror_By_Pnt);
	};

	class Server_GeoObj_Trsf2d_Rotation
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(pnt);
			defineTnbServerParam(angle);
		};
		constructTnbServerObject(Server_GeoObj_Trsf2d_Rotation);
	};

	class Server_GeoObj_Trsf2d_Scale
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(pnt);
			defineTnbServerParam(scale);
		};
		constructTnbServerObject(Server_GeoObj_Trsf2d_Scale);
	};

	class Server_GeoObj_Trsf2d_TrnsFromS1ToS2
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(axis1);
			defineTnbServerParam(axis2);
		};
		constructTnbServerObject(Server_GeoObj_Trsf2d_TrnsFromS1ToS2);
	};

	class Server_GeoObj_Trsf2d_TransfTo
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(axis);
		};
		constructTnbServerObject(Server_GeoObj_Trsf2d_TransfTo);
	};

	class Server_GeoObj_Trsf2d_Translation
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(pnt1);
			defineTnbServerParam(pnt2);
		};
		constructTnbServerObject(Server_GeoObj_Trsf2d_Translation);
	};

	class Server_GeoObj_Trsf2d_Values
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(trsf);
			defineTnbServerParam(a11);
			defineTnbServerParam(a12);
			defineTnbServerParam(a13);
			defineTnbServerParam(a21);
			defineTnbServerParam(a22);
			defineTnbServerParam(a23);
		};
		constructTnbServerObject(Server_GeoObj_Trsf2d_Values);
	};
}

#endif
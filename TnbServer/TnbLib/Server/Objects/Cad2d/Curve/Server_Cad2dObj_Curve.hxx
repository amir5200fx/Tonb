#pragma once
#ifndef _Server_Cad2dObj_Curve_Header
#define _Server_Cad2dObj_Curve_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	defineTnbServerObject(Server_Cad2dObj_Curve_ExportToPlt);

	class Server_Cad2dObj_Curve_Trim
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(curve);
			defineTnbServerParam(u0);
			defineTnbServerParam(u1);
			defineTnbServerParam(name);
		};

		constructTnbServerObject(Server_Cad2dObj_Curve_Trim);
	};

	class Server_Cad2dObj_Curve_SetName
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(curve);
			defineTnbServerParam(name);
		};

		constructTnbServerObject(Server_Cad2dObj_Curve_SetName);
	};

	defineTnbServerObject(Server_Cad2dObj_Curve_GetIdent);

	class Server_Cad2dObj_Curve_CalcTangt
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(curve);
			defineTnbServerParam(u);
		};

		constructTnbServerObject(Server_Cad2dObj_Curve_CalcTangt);
	};

	class Server_Cad2dObj_Nurbs
		: public Server_Object
	{
	public:
		struct Params
		{
			defineTnbServerParam(pnts);
			defineTnbServerParam(weights);
			defineTnbServerParam(knots);
			defineTnbServerParam(deg);
			defineTnbServerParam(name);
			defineTnbServerParam(periodic);
		};

		constructTnbServerObject(Server_Cad2dObj_Nurbs);
	};
}

#endif

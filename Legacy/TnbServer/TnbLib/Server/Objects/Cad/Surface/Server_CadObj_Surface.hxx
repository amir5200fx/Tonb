#pragma once
#ifndef _Server_CadObj_Surface_Header
#define _Server_CadObj_Surface_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	class Server_CadObj_ExtrudeSurface
		: public Server_Object
	{
	public:
		constructTnbServerObject(Server_CadObj_ExtrudeSurface);
	};
}

#endif
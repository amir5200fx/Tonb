#pragma once
#ifndef _Server_FoamObj_Header
#define _Server_FoamObj_Header

#include <Server_Object.hxx>

namespace tnbLib
{

	defineTnbServerObject(Server_FoamObj_LoadInitCs);

	defineTnbServerObject(Server_FoamObj_LoadBcs);

	defineTnbServerObject(Server_FoamObj_WriteInitCs);

	defineTnbServerObject(Server_FoamObj_WriteBcs);
}

#endif

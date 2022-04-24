#pragma once
#ifndef _Cad_gSingularZone_Header
#define _Cad_gSingularZone_Header

#include <Cad_SingularZone.hxx>
#include <Cad_gSingularZoneFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Cad_gSingularZone::CreatePaired3d(const GModel_Surface&) const;


}

#endif // !_Cad_gSingularZone_Header

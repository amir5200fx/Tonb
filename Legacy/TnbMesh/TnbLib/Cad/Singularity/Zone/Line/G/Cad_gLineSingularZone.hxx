#pragma once
#ifndef _Cad_gLineSingularZone_Header
#define _Cad_gLineSingularZone_Header

#include <Cad_LineSingularZone.hxx>
#include <Cad_gLineSingularZoneFwd.hxx>

namespace tnbLib
{

	template<>
	void Cad_gLineSingularZone::ProjectBoundariesToHorizons(const GModel_Surface&);
}

#endif // !_Cad_gLineSingularZone_Header

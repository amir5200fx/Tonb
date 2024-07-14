#pragma once
#ifndef _Entity3d_Hexahedralization_Header
#define _Entity3d_Hexahedralization_Header

#include <Entity3d_HexahedralizationFwd.hxx>
#include <Entity_StaticData.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{
	template <>
	TnbGeo_EXPORT void Entity3d_Hexahedralization::ExportToPlt(OFstream& File) const;

}

#endif
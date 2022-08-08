#pragma once
#ifndef _Entity3d_Tetrahedralization_Header
#define _Entity3d_Tetrahedralization_Header

#include <Pnt3d.hxx>
#include <Entity_Connectivity.hxx>
#include <Entity_StaticData.hxx>
#include <Entity3d_TetrahedralizationFwd.hxx>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT void Entity3d_Tetrahedralization::ExportToPlt(OFstream& File) const;
}

#endif // !_Entity3d_Tetrahedralization_Header

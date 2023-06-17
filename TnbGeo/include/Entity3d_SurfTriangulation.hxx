#pragma once
#ifndef _Entity3d_SurfTriangulation_Header
#define _Entity3d_SurfTriangulation_Header

#include <Entity3d_SurfTriangulationFwd.hxx>
#include <Entity3d_SPnt.hxx>
#include <Entity_StaticData.hxx>

#include <vector>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT void Entity3d_SurfTriangulation::ExportToPlt(OFstream& File) const;

	TnbGeo_EXPORT std::vector<Pnt3d> RetrieveCoords(const std::vector<Entity3d_SPnt>&);
	TnbGeo_EXPORT std::vector<Pnt2d> RetrieveParaCoords(const std::vector<Entity3d_SPnt>&);
}

#endif // !_Entity3d_SurfTriangulation_Header

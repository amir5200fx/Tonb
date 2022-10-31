#pragma once
#ifndef _Entity3d_Triangulation_Header
#define _Entity3d_Triangulation_Header

#include <Pnt3d.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity_StaticData.hxx>

namespace tnbLib
{

	typedef Entity_StaticData<Pnt3d, connectivity::triple>
		Entity3d_Triangulation;

	template<>
	TnbGeo_EXPORT void Entity3d_Triangulation::ExportToPlt(OFstream& File) const;
}

#endif // !_Entity3d_Triangulation_Header

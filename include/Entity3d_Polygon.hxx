#pragma once
#ifndef _Entity3d_Polygon_Header
#define _Entity3d_Polygon_Header

#include <Pnt3d.hxx>
#include <Entity_Polygon.hxx>

namespace tnbLib
{

	typedef Entity_Polygon<Pnt3d> Entity3d_Polygon;

	template<>
	const Pnt3d& Entity3d_Polygon::Coord(const Standard_Integer) const;

	template<>
	Pnt3d& Entity3d_Polygon::Coord(const Standard_Integer);

	template<>
	TnbGeo_EXPORT void Entity3d_Polygon::ExportToPlt(std::fstream& File) const;

	template<>
	TnbGeo_EXPORT void Entity3d_Polygon::ExportToPlt(OFstream& File) const;
}

#include <Entity3d_PolygonI.hxx>

#endif // !_Entity3d_Polygon_Header

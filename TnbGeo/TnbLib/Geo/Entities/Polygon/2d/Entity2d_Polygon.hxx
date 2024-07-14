#pragma once
#ifndef _Entity2d_Polygon_Header
#define _Entity2d_Polygon_Header

#include <Pnt2d.hxx>
#include <Entity_Polygon.hxx>

namespace tnbLib
{

	typedef Entity_Polygon<Pnt2d> Entity2d_Polygon;

	template<>
	inline const Pnt2d& Entity2d_Polygon::Coord(const Standard_Integer theIndex) const;

	template<>
	inline Pnt2d& Entity2d_Polygon::Coord(const Standard_Integer theIndex);

	template<>
	TnbGeo_EXPORT void Entity2d_Polygon::ExportToPlt(OFstream& File) const;
	template <>
	TnbGeo_EXPORT void Entity2d_Polygon::ExportToPlt(std::stringstream&) const;
	template<>
	TnbGeo_EXPORT void Entity2d_Polygon::ExportToVtk(OFstream&) const;
	template<>
	TnbGeo_EXPORT void Entity2d_Polygon::ExportToVtk(std::stringstream&) const;

}

#include <Entity2d_PolygonI.hxx>

#endif // !_Entity2d_Polygon_Header

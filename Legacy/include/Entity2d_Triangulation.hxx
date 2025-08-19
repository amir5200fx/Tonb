#pragma once
#ifndef _Entity2d_Triangulation_Header
#define _Entity2d_Triangulation_Header

#include <Pnt2d.hxx>
#include <Entity_Connectivity.hxx>
#include <Entity_StaticData.hxx>

namespace tnbLib
{

	typedef Entity_StaticData<Pnt2d, connectivity::triple>
		Entity2d_Triangulation;

	template<>
	TnbGeo_EXPORT void Entity2d_Triangulation::ExportToPlt(OFstream& File) const;
	template <>
	TnbGeo_EXPORT void Entity2d_Triangulation::StreamToPlt(std::stringstream& theStream) const;
	template<>
	TnbGeo_EXPORT void Entity2d_Triangulation::ExportToVtk(OFstream&) const;
	template <>
	TnbGeo_EXPORT void Entity2d_Triangulation::ExportToVtk(std::stringstream& theStream) const;
	template<>
	TnbGeo_EXPORT void Entity2d_Triangulation::ExportToVtk(std::fstream&) const;

}

#endif // !_Entity2d_Triangulation_Header

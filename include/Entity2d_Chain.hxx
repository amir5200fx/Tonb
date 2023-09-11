#pragma once
#ifndef _Entity2d_Chain_Header
#define _Entity2d_Chain_Header

#include <Pnt2d.hxx>
#include <Entity_Connectivity.hxx>
#include <Entity_StaticData.hxx>
#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{

	typedef Entity_StaticData<Pnt2d, connectivity::dual> Entity2d_Chain;

	template<>
	TnbGeo_EXPORT void Entity2d_Chain::CalcBoundingBox();

	template<>
	TnbGeo_EXPORT std::shared_ptr<Entity2d_Chain> Entity2d_Chain::Merged
	(
		const Standard_Real theRes,
		const Standard_Real theRadius
	) const;

	template<>
	TnbGeo_EXPORT void Entity2d_Chain::Merging
	(
		const Standard_Boolean HandleDegeneracy,
		const Standard_Real Resolution,
		const Standard_Real Radius
	);

	template<>
	TnbGeo_EXPORT void Entity2d_Chain::ExportToPlt(std::fstream& File) const;

	template<>
	TnbGeo_EXPORT void Entity2d_Chain::ExportToPlt(OFstream& File) const;
	template<>
	TnbGeo_EXPORT void Entity2d_Chain::ExportToVtk(OFstream&) const;
}

#endif // !_Entity2d_Chain_Header

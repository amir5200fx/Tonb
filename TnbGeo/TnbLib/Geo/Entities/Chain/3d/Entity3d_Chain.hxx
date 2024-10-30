#pragma once
#ifndef _Entity3d_Chain_Header
#define _Entity3d_Chain_Header

#include <Entity3d_ChainFwd.hxx>
#include <Entity_Connectivity.hxx>
#include <Pnt3d.hxx>
#include <Entity_StaticData.hxx>
#include <Entity3d_BoxFwd.hxx>

namespace tnbLib
{
	template<>
	TnbGeo_EXPORT void Entity3d_Chain::CalcBoundingBox();

	template<>
	TnbGeo_EXPORT std::shared_ptr<Entity3d_Chain> Entity3d_Chain::Merged
	(
		const Standard_Real theRes,
		const Standard_Real theRadius
	) const;

	template<>
	TnbGeo_EXPORT void Entity3d_Chain::Merging
	(
		const Standard_Boolean HandleDegeneracy,
		const Standard_Real Resolution,
		const Standard_Real Radius
	);

	template<>
	TnbGeo_EXPORT void Entity3d_Chain::ExportToPlt(OFstream& File) const;
	template<>
	TnbGeo_EXPORT void Entity3d_Chain::ExportToVtk(std::fstream& file) const;
}

#endif // !_Entity3d_Chain_Header

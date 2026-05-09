#pragma once
#ifndef _Geo2d_CompressMesh_Composite_Header
#define _Geo2d_CompressMesh_Composite_Header

#include <Geo2d_CompressMesh_CompositeFwd.hxx>
#include <Geo_CompressMesh.hxx>
#include <Entity2d_CmpMesh.hxx>

namespace tnbLib
{
	template<>
	TnbGeo_EXPORT std::vector<Standard_Integer> Geo2d_CompressMesh_Composite::get_components(const std::shared_ptr<Entity2d_CmpConnect>&);

	template<>
	TnbGeo_EXPORT std::shared_ptr<Entity2d_CmpConnect> Geo2d_CompressMesh_Composite::update_matrix(const std::shared_ptr<Entity2d_CmpConnect>&, const std::map<Standard_Integer, Standard_Integer>&);
}
#endif

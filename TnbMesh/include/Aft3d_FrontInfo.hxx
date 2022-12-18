#pragma once
#ifndef _Aft3d_FrontInfo_Header
#define _Aft3d_FrontInfo_Header

#include <Aft3d_FrontInfoTemplate.hxx>
#include <Aft_FrontTraits.hxx>
#include <Aft3d_FrontInfoAdaptor.hxx>
#include <Aft3d_Element.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_Node.hxx>
#include <Aft3d_FrontInfoFwd.hxx>
#include <Geo3d_MetricPrcsrFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft3d_FrontInfo::CalcGeometries<Geo3d_MetricPrcsr>
		(
			const std::shared_ptr<Geo3d_MetricPrcsr>& theSizeMap,
			const std::shared_ptr<Aft3d_Facet>&
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft3d_FrontInfo::CalcGeometries<Geo3d_MetricPrcsr>
		(
			const std::shared_ptr<Geo3d_MetricPrcsr>& theSizeMap,
			const std::shared_ptr<Aft3d_Edge>&
			);

}

#endif // !_Aft3d_FrontInfo_Header

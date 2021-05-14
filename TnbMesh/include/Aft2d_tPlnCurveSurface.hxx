#pragma once
#ifndef _Aft2d_tPlnCurveSurface_Header
#define _Aft2d_tPlnCurveSurface_Header

#include <Mesh_Module.hxx>
#include <TModel_ParaCurve.hxx>
#include <Mesh_PlnCurve.hxx>
//#include <Geo2d_SizeFunction.hxx>
//#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>
#include <Aft2d_tSegmentEdgeFwd.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>
		Aft2d_tPlnCurveSurface::TopoMesh<Aft2d_tSegmentEdge>
		(
			const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Aft2d_tPlnCurveSurface_Header

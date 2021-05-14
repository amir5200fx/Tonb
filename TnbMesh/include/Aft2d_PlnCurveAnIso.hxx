#pragma once
#ifndef _Aft2d_PlnCurveAnIso_Header
#define _Aft2d_PlnCurveAnIso_Header

#include <Mesh_PlnCurve.hxx>
#include <Pln_Curve.hxx>
#include <Aft2d_PlnCurveAnIsoFwd.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Aft2d_SegmentEdgeAnIsoFwd.hxx>

namespace tnbLib
{


	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>
		Aft2d_PlnCurveAnIso::TopoMesh<Aft2d_SegmentEdgeAnIso>
		(
			const std::shared_ptr<Aft2d_PlnCurveAnIso>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Aft2d_PlnCurveAnIso_Header

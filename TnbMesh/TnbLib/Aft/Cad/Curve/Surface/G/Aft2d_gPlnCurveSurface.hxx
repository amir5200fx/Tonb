#pragma once
#ifndef _Aft2d_gPlnCurveSurface_Header
#define _Aft2d_gPlnCurveSurface_Header

#include <Mesh_Module.hxx>
#include <GModel_ParaCurve.hxx>
#include <Mesh_PlnCurve.hxx>
//#include <Geo2d_SizeFunction.hxx>
//#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_gSegmentEdgeFwd.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Handle(Geom2d_Curve) Aft2d_gPlnCurveSurface::Geometry() const;

	template<>
	TnbMesh_EXPORT Standard_Real Aft2d_gPlnCurveSurface::FirstParameter() const;

	template<>
	TnbMesh_EXPORT Standard_Real Aft2d_gPlnCurveSurface::LastParameter() const;

	template<>
	TnbMesh_EXPORT Pnt2d Aft2d_gPlnCurveSurface::Value(const Standard_Real) const;

	template<>
	TnbMesh_EXPORT void Aft2d_gPlnCurveSurface::Reverse();

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPlnCurveSurface::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPlnCurveSurface::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>
		Aft2d_gPlnCurveSurface::TopoMesh<Aft2d_gSegmentEdge>
		(
			const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Aft2d_gPlnCurveSurface_Header

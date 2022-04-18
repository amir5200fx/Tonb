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
	TnbMesh_EXPORT Handle(Geom2d_Curve) Aft2d_tPlnCurveSurface::Geometry() const;

	template<>
	TnbMesh_EXPORT Standard_Real Aft2d_tPlnCurveSurface::FirstParameter() const;

	template<>
	TnbMesh_EXPORT Standard_Real Aft2d_tPlnCurveSurface::LastParameter() const;

	template<>
	TnbMesh_EXPORT Pnt2d Aft2d_tPlnCurveSurface::Value(const Standard_Real) const;

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tPlnCurveSurface::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tPlnCurveSurface::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);

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

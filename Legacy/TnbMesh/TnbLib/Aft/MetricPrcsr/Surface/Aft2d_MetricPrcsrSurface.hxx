#pragma once
#ifndef _Aft2d_MetricPrcsrSurface_Header
#define _Aft2d_MetricPrcsrSurface_Header

#include <Aft_MetricPrcsr.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Entity2d_Box Aft2d_MetricPrcsrSurface::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Entity2d_Metric1& theMetric,
		const Pnt2d& theCentre
	) const;

	template<>
	TnbMesh_EXPORT Entity2d_Box Aft2d_MetricPrcsrSurface::CalcSearchRegion
	(
		const Standard_Real theRaius,
		const Pnt2d& theCentre,
		const Aft2d_EdgeSurface& theFront
	) const;

	template<>
	TnbMesh_EXPORT Entity2d_Box Aft2d_MetricPrcsrSurface::CalcSearchRegion
	(
		const Standard_Real theRaius,
		const Aft2d_EdgeSurface& theFront
	) const;

	template<>
	TnbMesh_EXPORT Entity2d_Box Aft2d_MetricPrcsrSurface::CalcEffectiveFront
	(
		const Standard_Real theRadius,
		const Pnt2d& theCentre,
		const Aft2d_EdgeSurface& theFront
	) const;
}

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_MetricPrcsrSurface::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_MetricPrcsrSurface::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Aft2d_MetricPrcsrSurface);

#endif // !_Aft2d_MetricPrcsrSurface_Header
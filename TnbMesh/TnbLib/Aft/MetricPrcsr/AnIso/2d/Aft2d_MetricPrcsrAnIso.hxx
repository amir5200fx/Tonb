#pragma once
#ifndef _Aft2d_MetricPrcsrAnIso_Header
#define _Aft2d_MetricPrcsrAnIso_Header

#include <Aft_MetricPrcsr.hxx>
#include <Aft2d_EdgeAnIso.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Aft2d_MetricPrcsrAnIsoFwd.hxx>

namespace tnbLib
{

	template<>
	Entity2d_Box Aft2d_MetricPrcsrAnIso::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Entity2d_Metric1& theMetric,
		const Pnt2d& theCentre
	) const;

	template<>
	Entity2d_Box Aft2d_MetricPrcsrAnIso::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Pnt2d& theCentre,
		const Aft2d_EdgeAnIso& theFront
	) const;

	template<>
	Entity2d_Box Aft2d_MetricPrcsrAnIso::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Aft2d_EdgeAnIso& theFront
	) const;

	template<>
	Entity2d_Box Aft2d_MetricPrcsrAnIso::CalcEffectiveFront
	(
		const Standard_Real theRadius,
		const Pnt2d& theCentre,
		const Aft2d_EdgeAnIso& theFront
	) const;
}

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_MetricPrcsrAnIso::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_MetricPrcsrAnIso::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

}

#endif // !_Aft2d_MetricPrcsrAnIso_Header
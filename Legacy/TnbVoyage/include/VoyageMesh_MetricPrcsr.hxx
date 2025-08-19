#pragma once
#ifndef _VoyageMesh_MetricPrcsr_Header
#define _VoyageMesh_MetricPrcsr_Header

#include <VoyageMesh_MetricPrcsrFwd.hxx>
#include <VoyageMesh_Edge.hxx>
#include <VoyageMesh_Traits.hxx>
#include <Voyage_Module.hxx>
#include <Aft_MetricPrcsr.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>

namespace tnbLib
{

	template<>
	TnbVoyage_EXPORT Entity2d_Box 
		VoyageMesh_MetricPrcsr::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Entity2d_Metric1& theMetric,
		const Pnt2d& theCoord
	) const;

	template<>
	TnbVoyage_EXPORT Entity2d_Box 
		VoyageMesh_MetricPrcsr::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const Pnt2d& theCentre, 
		const VoyageMesh_Edge& theFront
	) const;

	template<>
	TnbVoyage_EXPORT Entity2d_Box 
		VoyageMesh_MetricPrcsr::CalcSearchRegion
	(
		const Standard_Real theRadius,
		const VoyageMesh_Edge& theFront
	) const;

	template<>
	TnbVoyage_EXPORT Entity2d_Box 
		VoyageMesh_MetricPrcsr::CalcEffectiveFront
	(
		const Standard_Real theRadius,
		const Pnt2d& theCentre, 
		const VoyageMesh_Edge& theFront
	) const;
}

#endif // !_VoyageMesh_MetricPrcsr_Header

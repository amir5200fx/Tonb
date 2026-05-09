#pragma once
#ifndef _Geo2d_MetricPrcsrAnIso_Header
#define _Geo2d_MetricPrcsrAnIso_Header

#include <Geo_MetricPrcsr.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Entity2d_Metric1.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT Standard_Real 
		Geo2d_MetricPrcsrAnIso::CalcDistance
		(
			const Pnt2d& theP0, 
			const Pnt2d& theP1
		) const;

	template<>
	TnbMesh_EXPORT Standard_Real 
		Geo2d_MetricPrcsrAnIso::CalcUnitDistance
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		) const;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo2d_MetricPrcsrAnIso);

#endif // !_Geo2d_MetricPrcsrAnIso_Header
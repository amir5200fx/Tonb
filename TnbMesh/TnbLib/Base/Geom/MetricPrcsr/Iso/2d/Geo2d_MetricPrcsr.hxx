#pragma once
#ifndef _Geo2d_MetricPrcsr_Header
#define _Geo2d_MetricPrcsr_Header

#include <Geo_MetricPrcsr.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricPrcsrFwd.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT Standard_Real 
		Geo2d_MetricPrcsr::CalcUnitDistance
		(
			const Pnt2d& theP0, 
			const Pnt2d& theP1
		) const;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo2d_MetricPrcsr);

#endif // !_Geo2d_MetricPrcsr_Header